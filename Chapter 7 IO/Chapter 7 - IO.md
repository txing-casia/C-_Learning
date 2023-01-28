## Chapter 7 深入IO

### IOStream概述

- IOStream采用流式I/O而非记录I/O，但可以在此基础上引入结构信息

- 所处理的两个主要问题
  - 表示形式的变化：使用格式化/解析在数据的内部表示与字符序列之间转换
  - 与外部设备的通信：针对不同的外部设备（终端、文件、内存）引入不同的处理逻辑
  
- 所涉及到的操作（输出流序列）
  - 格式化/解析
  - 缓存
  - 编码转换
  - 传输
  
- 采用模板来封装字符特性，采用继承来封装设备特性
  - 常用的类型实际上是类模板实例化的结果
  
    ```c++
    #include <fstream>
    std::ifstream x;
    ```

### 输入与输出

- 输入与输出分为格式化和非格式化两类

- 非格式化I/O：不涉及数据表示行驶的变化

  - 常用输入函数：`get / read / getline / gcount`
  - 常用输出函数：`put / write`

- 格式化I/O：使用移位操作符来进行输入（>>）与输出（<<）

  - c++通过操作符重载以支持内建数据类型的格式化I/O
  - 可以通过重载操作符以支持自定义类型的格式化I/O

- 格式控制

  - 可以接收位掩码类型（showpos）、字符类型（fill）与取值相对随意（width）的格式化参数

    - ```c++
      std::cout.setf(std::ios_base::showpos); // 输出如果是正数，自动加正号
      std::cout<< x <<std::endl;
      std::cout.width(10); // 输出10个字符，不足10个的，前面用空格替代.
      std::cout.fill('.'); // 用'.'替代上一条语句中设定的空格
      ```

  - 注意width方法的特殊性：触发后被重置

- 操作符

  - 简化格式化参数的设置
  - 触发实际的插入与提取操作

- 提取会放松对格式的限制`cin<<x;`

- 提取C风格字符串时要小心内存越界`setw(10)避免内存越界`

- ```c++
  #include <iomanip>
  cout<< showpos << setw(10) << setfill('.') << x;
  ```

- `cout<< showpos << x;`

### 文件与内存操作

- 文件操作

  - basic_ifstream / basic_ofstream / basic_fstream

    ```c++
    #include <iostream>
    #include <fstream>
    int main()
    {
    	std::ofstream outFile("my_file"); // 输出流 
    	outFile << "Hello\n"
    }
    ```

    ```c++
    #include <iostream>
    #include <fstream>
    int main()
    {
    	std::ifstream inFile("my_file"); // 输入流 
    	std::string x;
    	inFile >> x;
    	std::cout << x << '\n';
    }
    ```

  - 文件流可以处于打开/关闭两种状态，处于打开状态时无法再次打开，只有打开时才能I/O

    ```
    .is_open()
    .open()
    .close()
    ```

- 文件流的打开模式

  - ```
    in    打开以供读取
    out   打开以供写入
    ate   表示起始位置位于文件末尾
    app   附加文件，即总是项文件尾写入
    trunc 截断文件，即删除文件中的内容
    binary  二进制模式
    ```

  - 每种文件流都有缺省的打开方式

  - 注意ate和app的异同

  - binary能静止系统特定的转换

  - 避免意义不明确的流使用方式（如ifstream+out） 

- 合法的打开方式组合
  
  ```c++
  in    只读打开
  out | trunc    如果文件存在，将长度截断为0；否则建立文件以供写入
  out    如果文件存在，将长度截断为0；否则建立文件以供写入
  out | app    附加；打开或建立文本文件，仅供文件末尾写入
  in | out    打开文本文件供更新使用（支持读写）
  in | out | trunc    如果文件存在i，将长度截断为0；否则建立文件供更新使用
  ```
  
- 内存流：basic_istringstream/basic_ostringstream/basic_stringstream
  
  ```c++
  #include <iostream>
  #include <sstream>
  int main()
  {
  	std::ostringstream obj1;
  	obj1 << 1234;
      auto res = obj1.str();
      std::out<< res << std::endl;
  }
  ```
  
  ```c++
  #include <iostream>
  #include <sstream>
  int main()
  {
  	std::ostringstream obj1;
  	obj1 << 1234;
      auto res = obj1.str();
      
  	std::istringstream obj2(res);
  	int x;
      obj2 >> x;
      std::out<< x << std::endl;
  }
  ```
  
- 也会受打开模式影响（in/out/ate/app）
  
- 使用str()方法获取底层所对应的字符串
  
  - 小心避免使用str().c_str()的形式获取C风格字符串
  
- 基于字符串流的字符串拼接优化操作
  
  ```c++
  std::ostringstream obj;
  obj << "Hello";
  obj << " world";
  obj << "Hello";
  obj << " world";
  std::cout << obj.str() << std::endl;
  ```
### 流的状态

- iostate
  - failbit / badbit / eofbit / goodbit
- 检测流的状态
  - good() / fail() / bad() / eof() 方法
  - 转换为bool值（参考cppreference）
- 注意区分fail与eof
  - 可能会被同时设置，但二者含义不同
  - 转换为bool值时不会考虑eof
- 通常来说，只要流处于某种错误状态时，插入/提取操作就不会生效

- 复位流状态
  - clear：设置流的状态为具体的值（缺省为goodbit）
  - setState：将某个状态附加到现有的流状态上
- 捕获流异常：exceptions方法



  

  

  

  

































