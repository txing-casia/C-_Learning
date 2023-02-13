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

### 智能指针

- 使用new与delete的问题：内存所有权不清晰，容易产生不销毁，多销毁的情况

- C++的解决方案：智能指针

  - `auto_ptr`（c++17删除）
  - `shared_ptr`/`uniuqe_ptr`/`weak_ptr`

- shared_ptr——基于引用计数的共享内存解决方案

  - 基本用法

    - ```
      #include <memory>
      std::shared_ptr<int> x(new int(3)); // 等价于 int* x = new int(3);
      ```

  - reset() /get() 方法

    - get()返回T*
    
- 指定内存回收逻辑
  
- std::make_shared
  
- 对对象数组的支持（C++17支持shared_ptr<T[]>；C++20支持make_shared分配数组）
  
- 注意：shared_ptr管理的对象不要调用delete销毁

- unique_ptr——独占内存的解决方案

  - 基本用法

    - ```c++
      std::unique_ptr<int> x(new int(3)); 
      std::unique_ptr<int> y = std::move(x); // y夺走x地址的所有权
      ```

  - unique_ptr 不支持复制，但可以移动

  - 为unique_ptr指定内存回收逻辑

- weak_ptr——防止循环引入而引入的智能指针

  - 基于shared_ptr构造
  - lock() 方法

























