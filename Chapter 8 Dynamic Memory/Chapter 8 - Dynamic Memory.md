## Chapter 8 动态内存管理

### 动态内存基础

- 栈内存 和 堆内存
  - 栈内存特点：更好的局部性，对象自动销毁

    - ```c++
      int y = 2;
      ```
  
  - 堆内存特点：运行期动态扩展，需要显式释放
  
    - ```c++
      int* y = new int(2);
      //......
      delete y;
      ```
  
- 在c++中通常使用new和delete构造、销毁对象

- 对象的构造分为两步：分配内存与在所分配的内存上构造对象；对象的销毁与之类似

- new的几种形式
  - 构造单一对象/对象数组

  - nothrow new，`int* y = new {std::nothrow} int[5]{};//内存分配失败不抛出异常，输出空指针`

  - placement new，

    - ```c++
      char ch[sizeof(int)];
      int* y = new (ch) int(4);
      ```
  
  - new auto，`int* y = new auto(3);`
  
- new与对象对齐

-  delete 的常见用法

  - 销毁单一对象/对象数组

    - ```c++
      int* ptr = new int[5];
      delete[] ptr;
      ```

  - placement delete

- 使用new与delete的注意事项

  - 根据分配的是单一对象还是数组，采用相应的方式销毁
  - delete nullptr
  - 不能delete一个非new返回的内存
  - 同一块内存不能delete多次

- 调整系统自身的new/delete行为

  - 不要轻易使用
































