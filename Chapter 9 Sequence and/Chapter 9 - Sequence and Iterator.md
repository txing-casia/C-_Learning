## Chapter 9 序列与关联容器

### 容器概述

- 容器：一种特殊的类型，其对象可以防止其它类型的对象（元素）
  - 需要支持的操作：对象的添加、删除、索引、遍历

  - 有多种算法可以实现容器，每种方法各有利弊
  
- 容器的分类
  - 序列容器：其中的对象有序排列，使用整数值进行索引

  - 关联容器：其中的对象顺序并不重要，使用键进行索引
  
  - 适配器：调整原有容器的行为，使得其对外展现出新的类型、接口或返回新的元素
  
  - 生成器：构造元素序列
  
- 迭代器：用于指定容器中的一段去接，以执行遍历、删除等操作
  - 获取迭代器：`(c)begin/(c)end`；（加c表示迭代器不可写入，只读）`(c)rbegin/(c)rend`（反向迭代器，rbegin对应end前一个位置，rend对应begin前一个）
  - 迭代器分类：分成5类（category），不同的类别支持的操作集合不同

### 序列容器

- C++标准库中提供了多种序列容器模板

  - array：元素个数固定的序列容器
  - vector：元素连续存储的序列容器
  - forward_list/list：基于链表/双向链表的容器
  - deque：vector与list的折衷
  - basic_string：提供了对字符串专门的支持

- 需要使用元素类型来实例化容器模板，从而构造可以保存具体类型的容器

- 不同的容器所提供的接口大致相同，但根据容器性质的差异，其内部实现与复杂度不同

- 对于复杂度过高的操作，提供相对较难使用的接口或者不提供相应的接口

- **array容器模板**：具有固定长度的容器，其内部维护了一个内建数组，与内建数组相比提供了赋值操作

  ```c++
  #include <array>
  std::array<int, 3> a;
  std::array<int, 3> b = a;
  ```

  - 提供的接口：
    - 构造
    - 成员类型：value_type等
    - 元素访问：[], at, front, back, data
    - 容量相关（平凡实现）：empty, size, max_size
    - 填充与交换：fill, swap
    - 比较操作：<=>
    - 迭代器

- **vector容器模板**：元素可变

- 提供的接口

  - 与array很类似，但有特殊性
  - 容量相关接口：capacity / reserve / shrink_to_fit
  - 附加元素接口：push_back / emplace_back
  - 元素插入接口：insert / emplace
  - 元素删除接口：pop_back / erase

- 注意

  - vector不提供push_front / pop_front，可以使用insert / erase 模拟，但效率不高
  - swap效率较高
  - 写操作可能会导致迭代器失效（旧vector装满了导致重新开辟内存，删除旧内存地址）

- **list容器模板**：双向链表

- 与vector相比，list

  - 插入、删除成本较低，但随机访问成本较高
  - 提供了pop_front / splice 等接口
  - 写操作通常不会改变迭代器的有效性

- forward_list 容器模板：单向链表

  - 目标：一个成本较低的线性表实现
  - 其迭代器只支持递增操作，因此无rbegin / rend
  - 不支持size
  - 不支持pop_back / push_back
  - XXX_after操作

- 
