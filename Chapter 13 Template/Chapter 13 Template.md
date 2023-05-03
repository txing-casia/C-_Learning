## Chapter 13 模板

### 函数模板

- 使用template关键字引入模板：

  ```c++
  template<typrname T> 
  void fun(T)
  {
  }
  ```

  - 函数模板的声明与定义、
  - typename关键字可以替换为class，含义相同
  - 函数模板中包含了两对参数：函数形参/实参；模板形参/实参

- 函数模板的显式实例化：`fun<int>(3)`

  - 实例化会使得编译器产生相应的函数（函数模板并非函数，不能调用）
  - 编译器的两阶段处理
    - 模板语法检查
    - 模板实例化

  - 模板必须在实例化时可见——翻译单元的一处定义原则
  - 注意与内联函数的异同

- 函数模板的重载

- 模板实参的类型推导（模板函数隐式实例化时使用`fun<int>(3)`变为 `fun(3)`）

  - 如果函数模板在实例化时没有显式指定模板实参，那么系统会尝试进行推导

  - 推导是基于函数实参（表达式）确定模板实参的过程，其基本原则与auto类型推导类似

    - 函数形参是左值引用/指针：

      - 忽略表达式类型中的引用
      - 将表达式类型与函数形参模式匹配以确定模板实参

    - 函数形参是万能引用

      ```c++
      template <typename T>
      void fun(T&& input){ //万能引用
      }
      ```

      - 如果实参表达式是右值，那么模板形参被推导为去掉引用的基本类型
      - 如果实参表达式为左值，那么模板形参被推导为左值引用，触发引用折叠

    - 函数形参不包括引用

      - 忽略表达式类型中的引用
      - 忽略顶层const
      - 数组、函数转换成相应的指针类型

- 模板实参并非总是能够推导得到

  - 如果模板形参与函数形参无关，则无法推导
  - 即使相关，也不一定能进行推导，推导成功也可能存在因歧义而无法使用

- 在无法推导时，编译器会选择使用缺省模板实参

  ```c++
  template <typename T = int> //缺省值为int
  ```

  - 可以为任意位置的模板形参指定缺省模板实参——注意与函数缺省实参的区别

  ```c++
  template <typename T1,typename Res = double, template T2>
  Res fun(T1 x,T2 y){}
  ```

- 显式指定部分模板实参

  ```c++
  template <typename T1,typename Res = double, template T2>
  Res fun(T1 x,T2 y){}
  
  fun<int,int>(3,5);
  ```

  - 显式指定的模板实参必须从最左边开始，依次指定
  - 模板形参的声明顺序会影响调用的灵活性

- 函数模板自动推导时会遇到的几种情况

  - 函数形参无法匹配——SFINAE（替换失败并非错误）
  - 模板与非模板同时匹配，匹配等级相同，此时选择非模板的版本
  - 多个模板同时匹配，此时采用偏序关系确定选择“最特殊”的版本（选择能匹配范围更小的）

- 函数模板的实例化控制

  - 显式实例化定义：`template void fun<int>(int)` / 'template void fin(int)'
  - 显式实例化声明：`extern template void fun<int>(int)` / `extern template void fun(int)`
  - 注意一处定义原则
  - 注意实例化过程中的模板形参推导

- 函数模板的（完全）特化：`template<> void f<int>(int)` / `template<> coid f(int)`  （为一些模板参数提供相对特殊的实现逻辑）

  - 并不引入新的（同名）名称，只是为某个模板针对特定模板实参提供优化算法
  - 注意与重载的区别
  - 注意特化过程中的模板形参推导
  
- 避免使用函数模板的特化

  - 不参与重载解析，会产生反直觉的效果
  - 通常可以用重载代替
  - 一些不便于重载的情况：无法建立模板形参与函数形参的管理那

    - 引入“假”函数形参
    - 通过类模板特化解决
    - 使用`if constexpr`解决

```c++
// 使用if constexpr
#include <iostream>
#include <type_traits>

template <typename Res, typename T>
Res fun(T x)
{
	if constexpr(std::is_same_v<Res, int>)
    {
        std::cout << "1\n";
    }
    else
    {
        std::cout << "2\n";
    }
    return Res{};
}

int main()
{
    int x;
    fun<int>(&x);
}

```

```c++
// 使用假参数
#include <iostream>
#include <type_traits>

template <typename Res, typename T>
Res fun(T x, const Res&)
{
    std::cout << "2\n";
    return Res{};
}

template <typename T>
Res fun(T x, const int&)
{
    std::cout << "1\n";
    return int{};
}
    

int main()
{
    int x;
    fun<int>(&x, float{});
}
```

- （C++20）函数模板的简化形式：使用auto定义模板参数类型
  - 优势：书写简洁
  - 劣势：在函数内部需要间接获取参数类型信息


```c++
void fun(auto x)
{
}

int main()
{
    int x;
    fun(x);
}
```

### 类模板与成员函数模板

- 使用template关键字引入模板：`template<typename T> class B{...};`
  - 类模板的声明与定义——翻译单元的一处定义原则
  - 成员函数只有在调用时才会被实例化
  - 类内类模板名称的简写（`B{}==B<int>{}`）
  - 类模板成员函数的定义（类内、类外）

```c++
#include <iostream>
template <typename T>
class B
{
public:
    void fun(T input)
    {
        std::cout << input << std::endl;
    }
};
int main()
{
    B<int> x;
}
```

- 成员函数模板

  - 类的成员函数模板

  ```c++
  #include <iostream>
  
  class B
  {
  public:
      template <typename T>
      void fun(T input)
      {
          std::cout << input << std::endl;
      }
  };
  
  B x;
  x.fun<int>();
  ```

  - 类模板的成员函数模板

  ```c++
  #include <iostream>
  template <typename T>
  class B
  {
  public:
      template <typename T1>
      void fun()
      {
      }
  };
  B<int> x;
  x.fun<int>(); 
  ```

  ```c++
  #include <iostream>
  template <typename T>
  class B
  {
  public:
      template <typename T1>
      void fun();  // 在类外定义
  };
  
  template <typename T>
  template <typename T1>
  void B<T>::fun()
  {
      
  }
  
  B<int> x;
  x.fun<int>(); 
  ```

- 友元函数（模板）

  - 可以声明一个函数模板为某个类（模板）的友元
  - C++11支持声明模板参数为友元

```c++
#include <iostream>
template <typename T>
class B
{
    friend auto operator + (B input1,B input2)
    {
        B res;
        res.x = input1.x + input2.x;
        return res;
    }
};

int main()
{
    B<int> val1;
    B<int> val2;
    B<int> res = val1 + val2;
}
```

- 类模板的实例化
  - 与函数实例化很像
  - 可以实例化整个类，或者类中的某个成员函数
- 类模板的（完全）特化 / 部分特化（偏特化）
  - 特化版本与基础版本可以拥有完全不同大的实现

```c++
#include <iostream>
template <typename T>
class B
{
    void fun()
    {
        std::cout<< "1\n";
    }
};
template <>  // 类模板的特化
struct B<int>
{
    void fun2()  // 名称可以不同
    {
        std::cout<<"2\n";
    }
};
int main()
{
    B<int> x;
    x.fun2();
}
```

```c++
#include <iostream>
template <typename T, template T1>
class B
{
    void fun()
    {
        std::cout<< "1\n";
    }
};
template <typename T1>  // 类模板的部分特化
struct B<int, T1>
{
    void fun2()  // 名称可以不同
    {
        std::cout<<"2\n";
    }
};
int main()
{
    B<int,double> x;
    x.fun2();
}
```

- 类模板的实参推导（从C++17开始）
  - 基于构造函数的实参推导
  - 用户自定义的推导指引
  - 注意：引入实参推导并不意味着降低了类型限制！
  - C++17之前的解决方案：引入辅助模板函数
