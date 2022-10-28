## Chapter 2 C++初探

- 函数返回类型void，返回可写return;

- main()函数可以没有return，其它非void函数需要；但main()函数一定会返回给系统一个int值，一般0表示成功运行，1表示出错；
- 注释：
  - 块注释 /**/
  - 行注释 //

- 头文件添加方式：
  - #include “xxx”：当前目录找文件
  - #include \<xxx\>：系统的路径找文件
- 头文件名字不加后缀
- 输入输出：
  - 输入：`std::cin >>`
  - 输出：`std::cout <<`
- 输出流：
  - cout：正常打印输出
  - cerr：输出错误信息，支持输出文件重定向
  - clog：输出日志，到缓冲区
- 输出流区别：
  - 1. 输出目标；cout和cerr的区别
    2. 是否立即刷新缓冲区域；cerr立即刷新，用于纠错；clog不及时刷新

- 缓冲区刷新：`std::flush`(刷新缓冲区) 和 `std::endl` (刷新并换行)

- namespace是命名空间
  - 不使用则默认是全局的命名空间
  - 访问命名空间的方式：
    - 域解析符`::` ，单条语句，最安全！
    - using 语句，函数内部
    - 空间别名，改名，减短代码长度
  - `std`是标准库中的命名空间
  - 名字空间与名称改编（name mangling）

- `#include <cstdio>`，可以使用c语言中的`printf`

- 输出：
  - printf(“hello, %d”, x); 输出直观
  - cout << “hello ”<< x <<endl; 自动匹配输出类型
  - C++ 20 格式化库（比较新的方式，不成熟）

- if 语句

```c++
if(x==y)
{
}
else
{
}
```

- while 语句

```c++
while(x)
{
}
```

- 结构体 `struct`

```c++
struct Point
{
	int x;
	int y;
};
Point a;
a.x=1;
a.y=2;
```





