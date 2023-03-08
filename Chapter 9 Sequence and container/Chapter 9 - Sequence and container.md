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

- **forward_list 容器模板**：单向链表

  - 目标：一个成本较低的线性表实现
  - 其迭代器只支持递增操作，因此无rbegin / rend
  - 不支持size
  - 不支持pop_back / push_back
  - XXX_after操作

- **deque容器模板**：vector与list的折衷
  
  - push_back / push_front速度较快
  - 在序列中间插入、删除速度较慢
  
- **basic_string容器模板**：实现了字符串相关的接口
  
  - 使用char实例化出std::string
  - 提供了如find、substr等字符串特有的接口
  - 提供了数值与字符串转换的接口
  - 针对短字符串的优化（short string optimization: SSO）
  
- 使用键进行索引
  - set/map/multiset/multmap
  - unordered_set / unordered_map / unordered_multiset / unordered_multimap
  
- set / map / multiset /multimap 底层使用红黑树实现

- unordered_xxx底层使用hash实现

### 关联容器

- **set** 

  - 通常来说，元素需要支持使用 < 比较大小
  - 或者采用自定义的比较函数来引入大小关系
  - 插入元素：insert / emplace / emplace_hint
  - 删除元素：erase
  - 访问元素：find / contains
  - 修改元素：extract

- 注意：set迭代器所指向的对象是const的，不能通过其修改元素

- **map**

  - 树中的每个节点是一个std::pair
  - 键（pair.first）需要支持使用<比较大小
  - 或者采用自定义的比较函数来引入大小关系
  - 访问元素：find / contains / [] / at

  - 用法

    ```c++
    for (auto [k, v] : m){
    	cout << k << ' ' << v << endl;
    }
    ```

  - 插入

    ```c++
    std::map<int, bool> m;
    m.insert(std::pair<int, bool>(3, true)); // 插入
    auto ptr = m.find(3);
    cout << ptr->first << ' ' << ptr->second;
    m.erase(3); // 删除
    ```

  - 注意

    - map迭代器所指向的对象是std::pair，其键是const类型
    - []操作不能用于常量对象

- **multiset / multimap**

  - 与set  / map 类似，但允许重复的键

  - 元素访问

    - find返回首个查找到的元素
    - count返回元素个数
    - lower_bound / upper_bound / equal_range 返回查找到的区间

  - ```c++
    std::multiset<int> s{1,3,1};
    auto b = s.lower_bound(1);
    auto e = s.upper_bound(1);
    for (auto ptr = b; ptr != e; ++ptr){
    	std::cout << *ptr << std::endl;
    }
    ```

- **unordered_set / unordered_map / unordered_multiset / unordered_multimap**

  - 与set / map相比查找性能更好
  - 但插入操作一些情况下会慢
  - 其键需要支持两个操作
    - 转换为hash值
    - 判等

  - 除 == ，!= 外，不支持容器级的关系运算
    - 但==，!= 速度较慢

  - 自定义hash与判等函数


### 适配器和生成器

- 类型适配器，兼容不同类型的数据

  - basic_string_view（c++17）

    - 可以基于std::string，C字符串，迭代器构造

      ```c++
      // 字符串调用
      #inclide <string_view>
      void fun(const std::string& str){}
      void fun(std::string_view str)
      ```

    - 提供成本较低的操作接口 `std::string_view str`

    - 不可进行写操作

  - span（c++20）

    - 可基于C数组、array等构造

    - 可读写

      ```c++
      #include <span>
      #include <vector>
      void fun(std::span input){
      	for (auto P : input){
      		std::cout << p << ' ';
      	}
      	std::cout << endl;
      }
      
      int a[3] = {1,2,3};
      std::vector<int> s{1,2,3};
      fun(a);
      fun(s);
      ```

- 接口适配器

  - stack / queue / priority_queue
  - 对底层序列容器进行封装，对外展现栈、队列与优先级队列的接口
  - priority_queue 在使用时其内部包含的元素需要支持比较操作

- 数值适配器（C++20）：std::ranges::XXX_view, std::ranges::views::XXX, std::views::XXX

  - 可以将一个输入区间中的数值变换后输出

  - 数值适配器可以组合，引入复杂的数值适配逻辑

    ```c++
    #include <ranges>
    #include <vector>
    bool isEven(int i){
    	return i % 2 == 0;
    }
    std::vector<int> v{1,2,3,4,5};
    for (auto p : std::ranges::filter_view(v,isEven)){
    	std::cout<<p<<' '; // 过滤奇数，只会打印偶数
    }
    ```

- 生成器（C++20）

  - std::ranges::iota_view, std::ranges::views::iota, std::views::iota

  - 可以在运行期生成无限长或有限长的数值序列

    ```c++
    for (int i : std::views::iota(1) | std::views::take(9) // std::views::iota(1)生成无限长的序列，std::views::take(9)接收|之前的容器，只取前9个值
    	std::cout << i;
    ```

    

- 





















