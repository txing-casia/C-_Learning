## Chapter 2 从指针到引用

- int x= 10; 10有类型，x也有类型
- 类型表述了4种信息：
  - 存储所需的空间大小；sizeof(x)
  - 取值空间；超过限制可能溢出，例如赋值上界+1，则变为最小值；std::numeric_limits
  - 对齐信息；cash读取便利， alignof
  - 该类型可以执行的操作
- int包含4个字符（byte），一个字符8比特（bit）
- 类型描述：
  - 基本类型：C++语言中所支持的类型
    - 字符类型（char, wchar_t, char16_t,char32_t）
    - 整数类型
      - 带符号整数：short, int, long, long long
      - 无符号整数：unsigned  + 带符号整数类型
      - 浮点类型：float, double, long double
    - viod
  - 复杂类型：由基本类型组合、变种所产生的类型，可能是标准库引入，或自定义类型 

- 复杂类型：由基本类型组合、变种所产生的的类型，可以是标准库引入或自定义类型

- `unsigned = unsigned int`

- 字符-用单引号`'c'`

- 字符串-用双引号`"Call"`

- true, false全是小写！

- 字面值后加后缀改变类型：

  - 1.3（double），1.3f（float）
  - 2（int），2ULL（unsigned long long）
  - 可以自定义后缀改变字面值类型

- 定义一个变量：`int x`

- 声明一个变量：`extern int x`，x来自外部

- 缺省初始化，变量为随机值

- 初始化方式：

  - `int x=10;`
  - `int x(10);`
  - `int x{10};`

- 隐式类型转换：

  - 赋值中的转换 `int x=1.3`
  - bool和整数类型的转换

- 其他可能的隐式转换：

  - if中的转换
  - 比较大小时的转换（无符号整数与整数比大小，会都转换为无符号整数）

  

- 指针：`int* p=&x;`,`int* p=nullptr;`

- 特点：
  - 可指向不同的对象
  - 具有相同的尺寸（地址长度一致）
  - `&` 取地址操作符
  - `*` 解引用操作符 （访问指针中的值对应的地址，并获取相应值）
  
- 指针存放的是变量地址的开始位置，具体读取多长，取决于指针类型int or char

- 初始化：
  - 直接初始化：`int* p=&x;`
  - 拷贝初始化：`int* p(&x);`
  
- 指针不赋值，其存储内容为随机值，全局指针不赋值存储值为0

- 函数的重载，通过传入不同参数执行不同的重名函数

- 关于nullptr：
  - 类型为nullptr_t，表示空指针
  - 类似于C中的NULL，但更安全
  
- 空指针可转换为False，非空指针可转换为True

- void* 指针
  - 没有记录对象尺寸信息，可保存任意地址
  - 支持判等操作
  
- 指针的问题：

  - 指针可以为空
  - 指针地址
  - 解决方案：引用

- ```
  int* ptr=&x;//*表示声明指针
  *ptr//表示获取x的值
  ```

- ```
  &x;//获取x的地址
  int& ref=x;//要声明一个引用，ref是x的别名，两者可以交换使用
  ```

- 引用

  - int& ref = val;
  - 是对象的别名，不能绑定字面值
  - 构造时绑定对象，在其生命周期内不能绑定其它对象（赋值操作会改变对象内容）
  -  不存在空引用，但可能存在非法引用——总的来说比指针安全
  - 属于编译期概念，在底层还是通过指针实现

- 指针的引用

  - 指针是对象，因此可以定义引用
  - `int* p=&val; int* & ref=p;`
  - 类型信息从右向左解析

- 常量不可修改，防止非法操作，优化程序逻辑

- ```c++
  const 出现在*右边：指针本身不能改变
  const 出现在*左边：指针指向的值不能改变
  
  int* const ptr = &x;//指针指向地址不可更改
  // ptr = &y; 不可行
  
  const int* ptr = &x;//指针指向地址中的值不可更改
  // *ptr = 3; 不可行
  ```

- 顶层常量和常量指针：

  - ```c++
    // const int* --x--> int*
    const int x = 3;
    int* ptr = &x;//报错
    
    // int* ----> const int*
    int x = 3;
    const int* ptr = &x;//正确
    
    // const int* ----> const int*
    const int x = 3;
    const int* ptr = &x;//正确
    ```

- 常量引用：

  - const int&
  - 可读不可写
  - 主要用于函数形参
  - 可以绑定字面值

- 常量表达式（从C++11开始）

  - 编译期常量使用constexpr声明`constexpr int y = 3`
  - 编译器可以利用其进行优化
  - 常量表达式指针：constexpr位于*左侧，但表示指针是常量表达式`constexpr const int* ptr = nullptr;`

### 类型别名与类型的自动推导

- 可为类型引入别名，从而引入特殊的含义或便于使用

- 两种引入类型别名方式：
  - `typedef int MyInt;`
  - `using MyInt = int;`（从c++11开始）
  
- 使用using引入类型别名更友好
  - typedef char MyCharArr[4];
  - using MyCharArr = char[4];
  
- 类型别名与指针、引用的关系

  - 应将指针类型别名视为一个整体，在此基础上引入常量表示指针为常量的类型
  - 不能通过类型别名构造引用的引用

- 类型的自动推导

  - auto关键字可以根据赋值类型自动推导变量类型

  - auto会发生类型退化

  - const auto/constexpr auto 推导出的是常量/常量表达式类型

  - auto& 推导出引用类型，避免类型退化

  - decltype(exp) 返回exp表达式的类型（左值加引用）

    - ```C++
      int x = 3;
      int* ptr = &x;
      //decltype(*ptr)的类型为 int&
      ```

    - ```C++
      int x = 3;
      int* ptr = &x;
      
      decltype(x) --> int // x为变量名，推导出变量类型
      decltype(*ptr) --> int& // *ptr不是变量名，推导出类型的引用
      
      decltype(3.5) --> double //3.5是右值
      decltype(*ptr) --> int& //*ptr是左值
      decltype(ptr) --> int* //ptr是变量名称
      //右值返回原类型，左值返回类型加引用
      ```

      

  - decltype(val) 返回val的类型，不会产生退化

  - auto&虽然也不退化，但会产生引用，decltype(val) 不退化，不加引用，更方便；

  - **decltype(exp)，如果exp是表达式，左值加引用；如果是名称（val）返回val类型；**

  - decltype(auto) C++14开始使用，不退化，于decltype(auto) x = 3.5+15l 等效于decltype(3.5 + 15l) x = 3.5+15l 

  - concept auto C++20开始支持，表示一系列类型，可以限制推导的过程

  - ```C++
    std::integral auto y = 3.5;//语句无法执行，因为整数相关的类型都无法表示3.5
    std::integral auto y = 3.5;//正确
    ```

    

  - 

  

 









