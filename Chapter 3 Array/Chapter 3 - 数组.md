## Chapter 3 数组

### 数组

- 将一个或者多个相同类型的对象连在一起所形成的类型

- ```C++
  int a; // int 类型
  int b[10] //int[10] 类型
  ```

- 数组初始化方式：

  - 缺省初始化

    ```c++
    int b[3];
    ```

  - 聚合初始化

    ```C++
    int b[3] = {1,2,3};
    int b[3] = {1,2}; // 第三个元素默认为0
    int b[] = {1,2,3}; // int[3]
    ```

- 不能用auto声明数组类型

- 数组不能复制

- 元素个数必须是一个常量表达式（编译期可计算的值）

- 字符串数组的特殊性

  - ```c++
    char str[] = "Hello"; //简化初始化，长度为n+1，结尾是'\0'表示结束
    char str[] = {'H','e','l','l','o'};
    ```
  
- 指针数组 
  
  ````C++
  int* a[3];//数组a中有三个指针类型变量
  int (*a)[3]; // a是指针，解引用之后是个包含三个元素的数组，a的类型是int (*)[3]
  ````
  
- 数组的引用
  
  - ```C++
    int b[3];
    int (&a)[3]=b; //a的类型是int(&)[3]
    ```
  
- 不能声明引用的数组 `int& a[3]={x1,x2,x3};`(错误)
  
- 数组中元素访问
  
  - 数组对象是一个左值
  - 使用时转换为相应的指针类型
  - `x[y]->*((x)+(y))`地址位置
  
- 退化：`auto b = a; // b是int*`
  
- 数组到指针的隐式转换

  - 隐式转换丢失一部分类型信息（数组长度信息）
  - 可以通过声明来避免隐式转换
    - **编译**的时候单独看每个cpp正确性
    - **链接**的时候不涉及变量类型信息
  - 注意：不要使用extern指针来声明数组
    - unknown bounded array 声明可以，定义不行

- 获得数组头尾指针`int a[3]={1,2,3};`：

  - 头：`a`, `std::begin(a)`, `std::cbegin(a)`(//const int*)
  - 尾：`a + 3`, `&(a[3])`, `std::end(a)`, `std::cend(a)`(//const int*)

- 指针算数：

  - 增加、减少 (+1, -2)
  - 比较 (<,>,==,!=)
  - 求距离 (ptr_end  - ptr_begin)
  - 解引用 (*ptr, ptr[2])
  - 指针索引

-  求元素的个数：

  - `sizeof`方法，`sizeof(a)/sizeof(int)`//求数组长度
  - `std::size`方法
  - `(c)end-(c)begin`方法

- 元素遍历
  
  - 基于元素个数
  
  - 基于(c)begin/(c)end
  
  - 基于range-based for 循环
  
    - ```c++
      int a[4] = {2,3,5,7};
      for (int x : a)
      {
      	std::cout << x << std::endl;
      }
      ```
  
- 字符数组长度计算：
  
  - ```C++
    #include <cstring>
    char str[] = "Hello";
    cout << strlen(str) << endl; //strlen() = 5
    char str[] = {'H','e','l','l','o'};
    cout << strlen(str) << endl; //strlen() 不一定为 5
    char str[] = {'H','e','l','l','o','\0'};
    cout << strlen(str) << endl; //strlen() = 5
    ```
  
- 多维数组的理解：
  
- `int x[3][4][5]`：x数组包含3个元素，每个元素是二维数组，`int[4][5]`类型，其中每个元素是`int[5]`类型
  
- 初始化数组只能省略最高位的索引
  
- 数组的遍历：

```c++
int x2[3][4][5] = {1,2,3,4,5};
for (auto & p : x2){
	for (auto & q : p){
		for (auto r : q){
			cout<<r<<'\n';
		}
	}
}
```

- 指针与多维数组
  - 多维数组可以隐式转换为指针，但只有最高维会进行转换，其它维度信息保留；
  - 使用类型别名来简化多维数组指针的声明
  - 使用指针来遍历多维数组

### vector

- `include <vector>`
- `std::vector<int> x;`

- 与内建数组比，更侧重与易用性
  - 可复制、在运行期动态改变元素个数

- 构造与初始化

  - 聚合初始化
  - 其它初始化方式

- 其它方法

  - 获取元素个数，判断是否为空
  - 插入、删除元素
  - vector的比较


- `std:vector<int> x(3); // x中包含三个为0的int`

- `std:vector<int> x(3,1); // x中包含三个为1的int`

- `std::cout<<x.size(); // 元素个数`

- `std::cout<<x.empty(); // 元素是否为空`

- `x.push_back(2); // vector末尾添加元素2`

- `x.pop_back(); // 去除最后一个元素`

- ```c++
  std::vector<int> x1 = {1,2,3};
  std::vector<int> x2 = {1,3,2};
  std::cout<< (x1 == x2); //逐个比较每个元素的大小，返回一个bool值
  std::cout<< (x1 > x2); //逐个比较每个元素的大小，返回一个bool值
  ```
  
- vector元素的索引和遍历：

  - [] 和 at
  - (c)begin/(c)end函数 和 (c)begin/(c)end方法
  
- 

- 

- 

- 

- 

  

  

  

  

  

  

  

  

  

  
  
  











