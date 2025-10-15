## 预备知识

### 1. 程序性能分析

### 2. 渐进记法

### 3. 性能测试









网课：https://www.bilibili.com/video/BV1b7411N798?t=5.4&p=41

## 数据结构

- 数据结构(data structure)是 对数据元素及其之间逻辑关系的抽象描述；
- 学习数据结构时，需要关注三部分：
  - 理解某种数据结构的定义(数据元素的逻辑关联方式和整体的逻辑特征)；
  - 用编程语言具体实现以理解原理；
  - 使用STL C++的各种工程级容器解决实际问题；

### 1. 线性表

#### 1.1. 定义

- 线性表(Linear List)：
  - 由 n 个具有相同数据类型的元素组成的有限序列；
  - 逻辑结构：元素之间存在一对一的线性关系(前驱 -> 后继)；元素按顺序排列，形成唯一的 “线性” 逻辑结构，无分支；

#### 1.2. 实现

##### 1.2.1. 基于数组的线性表

- 又称采用顺序存储结构的线性表；特点为静态储存分配，存储地址连续，事先确定容量

- 模板类 MyVector.hpp

  ~~~cpp
  /*
   * Briefly emulates the std::vector container from the C++ STL.
   * Author: JayWei <JayWei0610@gmail.com>
   * Version: 1.0.5
   * Created: 2024-02-15
   * Last Modified: 2025-07-04
   */
  
  #include <cstddef> // size_t
  #pragma once
  
  namespace my_stl
  {
      template <class T>
      class MyVector
      {
      public:
          class iterator;                                      // 迭代器类
          MyVector() : data(nullptr), capacity(0), _size(0) {} // 默认构造函数
          MyVector(int theCapacity)                            // 含参构造函数
          {
              data = new T[theCapacity];
              capacity = theCapacity;
              _size = 0;
          }
          ~MyVector() { delete[] data; }                      // 析构函数
          void push_back(const T &value);                     // 尾插法
          void pop_back();                                    // 尾删法
          iterator insert(iterator pos, const T &value);      // 任意位置插入
          iterator erase(iterator pos);                       // 任意位置删除
          void clear() { _size = 0; }                         // 清空
          bool empty() const { return _size == 0; }           // 判断是否为空
          T &operator[](size_t index) { return data[index]; } // 重载下标运算符
          size_t size() const { return _size; }               // 返回大小
          iterator begin() { return iterator(data); }         // 首元素迭代器
          iterator end() { return iterator(data + _size); }   // 尾后迭代器
  
      private:
          T *data;                         // 数组指针
          size_t capacity;                 // 容量
          size_t _size;                    // 大小
          void expand(size_t newCapacity); // 扩容函数
      };
  
      // 迭代器类
      template <class T>
      class MyVector<T>::iterator
      {
          friend class MyVector<T>; // 友元，不然erase和insert里面无法访问ptr
  
      public:
          iterator(T *p = nullptr) : ptr(p) {} // 构造函数
          iterator operator++(int)             // 重载后缀++
          {
              iterator temp = *this;
              ptr++;
              return temp;
          }
          // 重载解引用，==，+，!=运算符
          T &operator*() { return *ptr; }
          bool operator==(const iterator &other) const { return (this->ptr == other.ptr); }
          iterator operator+(size_t n) const { return iterator(ptr + n); }
          bool operator!=(const iterator &other) const { return ptr != other.ptr; } 
  
      private:
          T *ptr; // 指向MyVector里的元素
      };
  
      // 尾插法
      template <class T>
      void MyVector<T>::push_back(const T &value)
      {
          if (_size >= capacity)
              expand(capacity == 0 ? 1 : capacity * 2); // 是否扩容
          data[_size++] = value;                        // 插值
      }
  
      // 尾删法
      template <class T>
      void MyVector<T>::pop_back()
      {
          if (_size > 0)
              _size--; // 逻辑删除
      }
  
      // 任意位置插入
      template <class T>
      typename MyVector<T>::iterator MyVector<T>::insert(MyVector<T>::iterator pos, const T &value)
      {
          if (pos.ptr < data || pos.ptr > data + _size) // 判断迭代器位置是否合法
              return end();
  
          size_t index = pos.ptr - data; // 计算索引(指针减)
          if (_size >= capacity)
              expand(capacity == 0 ? 1 : capacity * 2); // 是否扩容
  
          for (size_t i = _size; i > index; i--)
              data[i] = data[i - 1]; // 将index及后面的元素依次后移
  
          data[index] = value;           // 插值
          _size++;                       // 别忘了大小+1
          return iterator(data + index); // 返回插入位置的迭代器
      }
  
      // 任意位置删除
      template <class T>
      typename MyVector<T>::iterator MyVector<T>::erase(MyVector<T>::iterator pos)
      {
          if (pos.ptr < data || pos.ptr > data + _size) // 判断迭代器位置是否合法
              return end();
  
          size_t index = pos.ptr - data; // 计算索引
          for (size_t i = index; i < _size - 1; i++)
              data[i] = data[i + 1];     // 将index后面的元素依次前移
          _size--;                       // 别忘了大小-1
          return iterator(data + index); // 返回删除位置的迭代器(删除元素后一个元素)
      }
  
      // 扩容
      template <class T>
      void MyVector<T>::expand(size_t newCapacity)
      {
          // 不用更新begin和end迭代器
          // 每次调用begin()和end()都是返回的iterator(data)和iterator(data + _size)
          T *newData = new T[newCapacity];
          for (size_t i = 0; i < _size; ++i)
              newData[i] = data[i];
          delete[] data;
          data = newData;
          capacity = newCapacity;
      }
  }
  ~~~

##### 1.2.2. 基于链表的线性表

- 又称采用链式存储结构的线性表，简称为链表；根据指针的连接方式，链表分为：单链表，双链表和循环链表；

###### 1.2.2.1. 单向链表

###### 1.2.2.2. 双向链表

- 模板类MyList.hpp

  ~~~cpp
  /*
   *Briefly emulates the std::list container from the C++ STL.
   * Author: JayWei <JayWei0610@gmail.com>
   * Version: 0.0.0
   * Created: 2025-07-04
   * Last Modified: 2025-07-04
   */
  
  #include <cstddef> // size_t
  #pragma once
  
  namespace my_stl
  {
      template <class T>
      class MyList
      {
      };
  }
  ~~~

###### 1.2.2.3. 循环链表

#### 1.3. 应用

##### 1.3.1. STL C++的线性表

###### 1.3.1.1. std::vector容器

- 基于数组的线性表；
- 常用方法：

1. vector 构造函数：

   ~~~cpp
   vector<T> v; // 采用模版类实现，默认构造函数
   vector<T> v(T* v1.begin(), T* v1.end()); // 将v1[begin(), end())区间中的元素拷贝给本身
   vector<T> v(int n, T elem); // 将n个elem拷贝给本身
   vector<T> v(const vector<T> v1); // 拷贝构造函数
   
   // 对于第二种构造方式给出一个特殊的例子：
   int array[5] = {1, 2, 3, 4, 5};
   vector<int> v(array, array + sizeof(array) / sizeof(int));
   // 可见vector容器的迭代器本质上是指针
   ~~~

1. vector 赋值操作：

   ~~~cpp
   assign(beg, end); // 将[beg, end)区间中的数据拷贝复制给本身
   assign(n, elem); // 将n个elem拷贝给本身
   vector& operator=(const vector& vec); // 重载赋值操作符
   swap(vec); //将vec与本身的元素互换
   
   // 巧用swap来收缩空间
   vector<int>(v).swap(v);
   // vector<int>(v): 利用拷贝构造函数初始化匿名对象
   // swap(v): 交换的本质其实只是互换指向内存的指针
   // 匿名对象指针指向的内存会由系统自动释放
   ~~~

1. vector 大小操作：

   ~~~cpp
   int size(); // 返回容器中的元素个数
   bool empty(); // 判断容器是否为空
   
   void resize(int num); 
   // 重新指定容器的长度为num，若容器变长，则以默认值填充新位置。
   // 若容器变短，则末尾超出容器长度的元素被删除
   void resize(int num, T elem); 
   // 重新指定容器的长度为num，若容器变长，则以elem填充新位置。
   // 若容器变短，则末尾超出容器长度的元素被删除
   
   int capacity(); // 返回容器的容量
   void reserve(int len); 
   // 容器预留len个元素长度，预留位置不初始化，元素不可访问
   ~~~

1. vector 数据存取操作：

   ~~~cpp
   T& at(int idx); // 返回索引idx所指的数据，如果idx越界，抛出out_of_range异常
   T& operator[](int idx); // 返回索引idx所指的数据，如果idx越界，运行直接报错
   
   T& front(); // 返回首元素的引用
   T& back(); // 返回尾元素的引用
   ~~~

1. vector 插入删除操作：

   ~~~cpp
   insert(const_iterator pos, T elem); // 在pos位置处插入元素elem
   insert(const_iterator pos, int n, T elem); // 在pos位置插入n个元素elem
   insert(pos, beg, end); // 将[beg, end)区间内的元素插到位置pos
   push_back(T elem); // 尾部插入元素elem
   pop_back(); // 删除最后一个元素
   
   erase(const_iterator start, const_iterator end); // 删除区间[start, end)内的元素
   erase(const_iterator pos); // 删除位置pos的元素
   
   clear(); // 删除容器中的所有元素
   ~~~

###### 1.3.1.2. std::list容器

- 基于双向循环链表的线性表；

- 常用方法：

1. list 构造函数

   ~~~cpp
   list<T> lstT; // 默认构造形式，list采用模版类实现
   list(beg, end); // 构造函数将[beg, end)区间内的元素拷贝给本身
   list(int n, T elem); // 构造函数将n个elem拷贝给本身
   list(const list& lst); // 拷贝构造函数
   ~~~

2. list 数据元素插入和删除操作

   ~~~cpp
   void push_back(T elem); // 在容器尾部加入一个元素
   void pop_back(); // 删除容器中最后一个元素
   
   void push_front(T elem); // 在容器开头插入一个元素
   void pop_front(); // 从容器开头移除第一个元素
   
   const_ iterator insert(iterator pos, elem); // 在pos位置插入elem元素的拷贝，返回新位置
   void insert(iterator pos, n, elem); // 在pos位置插入n个elem元素的拷贝，无返回值
   void insert(iterator pos, beg, end); // 在pos位置插入[beg, end)区间内的数据，无返回值
   
   void clear(); // 移除容器的所有数据
   
   erase(beg, end); // 删除[beg, end)区间内的所有数据，返回下一个数据的位置
   erase(pos); // 删除pos位置的数据，返回下一个数据的位置
   
   remove(elem); // 删除容器中所有与elem匹配的元素
   ~~~

2. list 大小操作

   ~~~cpp
   int size(); // 返回容器中元素的个数
   bool empty(); // 判断容器是否为空
   
   void resize(int num);
   // 重新制定容器的长度为num，若容器变长，则以默认值填充新位置；
   // 若容器变短，则末尾超出容器长度的元素被删除
   void resize(int num, T elem);
   // 重新制定容器的长度为num，若容器变长，则以elem填充新位置；
   // 若容器变短，则末尾超出容器长度的元素被删除
   ~~~

2. list 赋值操作

   ~~~cpp
   assign(beg, end); // 将[beg, end)区间中的数据拷贝赋值给本身
   assign(n, elem); // 将n个elem拷贝赋值给本身
   
   list& operator=(const list& lst); // 重载等号操作符
   
   swap(lst); // 将lst与本身的元素互换
   ~~~

2. list 数据的存取

   ~~~cpp
   T& front(); // 返回第一个元素
   T& back(); // 返回最后一个元素
   ~~~

2. list 反转排序

   ~~~cpp
   void reverse(); // 反转链表
   
   void sort(); // 默认list排序，规则为从小到大
   void sort(bool (*cmp)(T item1, T item2)); // 指定排序规则的list排序
   
   // 不能用sort(lst.begin(), lst.end())
   // 因为所有系统提供的某些算法（比如排序），其迭代器必须支持随机访问
   // 不支持随机访问的迭代器的容器，容器本身会对应提供相应的算法的接口
   ~~~

##### 1.3.2. 应用



### 2.数组和矩阵



### 3.栈 

#### 3.1. 定义

- 栈( Stack )
  - 栈是一种特殊的线性表，其插入和删除只能在表的同一端进行(后进先出，LIFO)；
  - 栈的插入又称为入栈或压栈( push )；栈的删除又称为出栈或弹栈( pop )；
  - 能被操作的一端称为栈顶( top )，另一端称为栈底( bottom )；

#### 3.2. 实现

##### 3.2.1. 基于数组的栈

##### 3.2.2. 基于链表的栈

#### 3.3. 应用

##### 3.3.1. STL C++的栈

- 即 std::stack

- 常用方法：

1. stack 构造函数

   ~~~cpp
   stack<T> stkT; // 默认构造函数，stack采用模版类实现
   stack(const stack& stk); // 拷贝构造函数
   ~~~

1. stack 赋值操作

   ~~~cpp
   stack& operator=(const stack& stk); // 重载赋值操作符
   ~~~

1. stack 数据存取操作

   ~~~cpp
   void push(T elem); // 向栈顶添加元素
   void pop(); // 从栈顶移除第一个元素
   T& top(); // 返回栈顶元素
   ~~~

1. stack 大小操作

   ~~~cpp
   bool empty(); // 判断堆栈是否为空
   int size(); // 返回栈的大小
   ~~~

##### 3.3.2. 应用

###### 3.3.2.1. 括号匹配

- 问题：对一个字符串的左右括号进行匹配

- 策略：从左到右依次扫描一个字符串，发现左括号就压入栈，发现右括号就弹出一个左括号

  

### 4.队列 

#### 4.1. 定义

- 队列(queue):
  - 一种特殊的线性表，其插入和删除只能分别在表的两端进行(先进先出，FIFO)；
  - 插入元素的一端称为队尾(back/rear)；
  - 删除元素的一端称为队头(front)；(头出尾进)；

#### 4.2. 实现

##### 4.2.1. 基于数组的队列

##### 4.2.2. 基于链表的队列

#### 4.3. 应用

##### 4.3.1. STL C++的队列

- 即std::queue，基于std::deque实现的FIFO队列

- 常用方法：

1. queue 构造函数

   ~~~cpp
   queue<T> queT; // queue对象的默认构造函数形式，采用模版类实现
   queue(const queue& que); // 拷贝构造函数
   ~~~

1. queue 存取、插入和删除操作

   ~~~cpp
   void push(T elem); // 往队尾添加元素
   void pop(); // 从队头移除第一个元素
   T& back(); // 返回最后一个元素
   T& front(); // 返回第一个元素
   ~~~

1. queue 赋值操作

   ~~~cpp
   queue& operator=(const queue& que); // 重载赋值操作符
   ~~~

1. queue 大小操作

   ~~~cpp
   bool empty(); // 判断队列是否为空
   int size(); // 返回队列的大小
   ~~~

##### 4.3.2. 应用



### 5.跳表 ？



### 6.哈希表

#### 6.0. 哈希函数

- 哈希函数(Hush Function)，又称散列函数，用于将任意长度的数据映射为固定长度输出值；

  - 这个输出值称为哈希值(Hash Value)或散列值；

  - 哈希冲突：不同的输入值被映射为同一个哈希值；

#### 6.1. 定义

- 哈希表(Hash Table):
  - 数据对象：桶(Buckets)，用于存储键(Key)或键值对(Key, Value)；
  - 逻辑结构： 通过哈希函数将键映射为桶索引，直观上键就是索引；

#### 6.2. 实现 ?

- 哈希冲突的解决办法：
  - 链地址法：每个桶对应一个链表，冲突的键值对存储在同一链表中；
  - 开放寻址法：当冲突发生时，通过某种探测算法寻找下一个可用的桶；
  - 再散列法：当冲突过多导致负载因子(元素数量 / 桶数量)超过阈值时，扩大散列表容量，并重新计算所有键的桶索引；

#### 6.3. 应用 

##### 6.3.1. STL C++的哈希表

###### 6.3.1.1. std::unordered_set

- 无序存储唯一键；

- 常用方法：

  1.插入元素
  
  ~~~cpp
  mySet.insert(42);      // 插入单个元素
  mySet.emplace(100);    // 原位构造并插入
  
  // 批量插入
  mySet.insert({1, 2, 3});
  ~~~
  
- 查找元素

  ~~~cpp
  // 使用 find() 方法查找（返回迭代器）
  // 不要直接解引用find，可能会返回end迭代器
  auto it = mySet.find(42);
  if (it != mySet.end()) 
      std::cout << "Found: " << *it << std::endl;
  else
      std::cout << "Not found" << std::endl;
  
  // 使用 count() 方法检查元素是否存在（返回 0 或 1）
  if (mySet.count(100) > 0)
      std::cout << "Element exists" << std::endl;
  ~~~

- 删除元素

  ~~~cpp
  mySet.erase(42);       // 删除指定元素
  mySet.erase(mySet.find(100));  // 通过迭代器删除
  mySet.clear();         // 清空所有元素
  ~~~

- 遍历元素

  ~~~cpp
  // 使用范围-based for 循环
  for (const auto& element : mySet) 
      std::cout << element << std::endl;
  // 使用迭代器
  for (auto it = mySet.begin(); it != mySet.end(); ++it) 
      std::cout << *it << std::endl;
  ~~~

- 可以自定义hash函数(传入的必须是类名)

  ~~~cpp
  class MyHash
  {
      // 重载函数调用符，不要忘了设置成public
  public:
      size_t operator()(const std::string &key) const
      {
          size_t hash = 0;
  		// ... 具体的哈希算法
          return hash;
      }
  };
  
  int main()
  {
      std::unordered_set<std::string, MyHash> set; // 使用自定义哈希函数
  }
  ~~~

###### 6.3.1.2. std::unordered_multiset



###### 6.3.1.3. std::unordered_map

- 注意事项：
  - unordered_map存储键值对，且键是唯一的
  - 对于自定义类型的键，必须提供自定义的哈希函数和 == 比较函数
  - 元素无特定顺序，根据键的哈希值分布在各个桶中
  - 采用链地址法处理哈希冲突(如果发生哈希冲突，需要比较键是否相等，这也是为什么需要提供自定义的 == 比较函数)

- 包含头文件

  ~~~cpp
  #include<unordered_map>
  ~~~

- 定义与初始化

  ~~~cpp
  // 创建空的 unordered_map，键为string类型，值为int类型
  std::unordered_map<std::string, int> myMap;
  
  // 可以使用初始化列表初始化
  std::unordered_map<std::string, int> myMap = {
      {"Alice", 25},
      {"Bob", 30},
      {"Charlie", 35}};
  ~~~

- 插入元素

  - unordered_map会自动使用std::hash或者自定义的哈希函数将键转化为桶索引

  ~~~cpp
  myMap.insert({"key1", value1}); // 使用 insert 方法插入
  myMap["key2"] = value2;         // 使用下标操作符插入或赋值
  myMap.emplace("key3", value3);  // 使用 emplace 方法
  ~~~

- 访问元素

  ~~~cpp
  int value = myMap["key1"];            // 使用下标操作符访问
  // 使用mapMap[Key]访问时，若Key存在，返回Key对应值的引用，Key不存在，则插入一个新的键值对并返回值的引用
  std::string value = myMap.at("key2"); // 使用 at() 方法访问（若键不存在，会抛出 out_of_range 异常）
  // 使用迭代器遍历
  for (const auto &pair : myMap)
  {
      std::cout << pair.first << ": " << pair.second << std::endl;
  }
  ~~~

- 查找元素

  ~~~cpp
  // 使用 find() 方法查找（返回迭代器）
  // it->first是键，it->second是值
  auto it = myMap.find("key1");
  if (it != myMap.end())
      std::cout << "Found: " << it->second << std::endl;
  else
      std::cout << "Not found" << std::endl;
  
  // 使用 count() 方法检查键是否存在（返回 0 或 1）
  if (myMap.count("key2") > 0)
      std::cout << "Key exists" << std::endl;
  ~~~

- 删除元素

  ~~~cpp
  myMap.erase("key1"); // 使用 erase() 方法删除指定键的元素
  
  // 使用迭代器删除元素
  auto it = myMap.find("key2");
  if (it != myMap.end())
      myMap.erase(it);
  
  myMap.clear(); // 清空所有元素
  ~~~

###### 6.3.1.4. std::unordered_multimap



##### 6.3.2. 应用





### 7.二叉树

P287

​	本章将研究两种基本的树：一般树（简单树）和二叉树。第12~15章将研究更多的大家熟悉的树—堆（heap)、左高树（leftist tree）、锦标赛树（tournament tree)、二叉搜索树（binary tree)、AVL树、红黑树（red-black tree)、伸展树(splay tree）和B树。第12~14章比较独立，可以按任意顺序阅读。而第15章只有在消化了第14章之后才能阅读。如果学完这几章之后，你还渴望学习另外一些树结构一配对堆（pairingheap)、区间堆（interval heap)、双端优先级队列的树结构（tree structures for double-ended priority queue)、字典树（tries，也称前缀树、单词查找树、键树入后缀树（suffixtree)，你可以从本书网站上得到相关的内容。

​	本章的应用部分有两个树的应用。第一个应用是关于在一个树形分布的网络中设置信号调节器。第二个应用是再讨论6.5.4节的在线等价类问题。这个问题在本章中又被称为合并/搜索问题。利用树来解决等价类问题要比6.5.4节的链表解决方案高效得多。
​	4种常用的二叉树遍历方法：前序遍历、中序遍历、后序遍历和层次遍历。

#### 7.0. 树( Tree )

- 逻辑结构特点：
  - 树有且仅有一个根节点作为入口；
  - 节点按层次组织，父节点与子节点形成明显的上下层关系；
  - 节点之间不存在环路，保证了树结构的有效性；
  - 树的子树本身也是树；
- 相关术语：
  - 根节点( Root Node )，父节点( Parent Node )，子节点( Child Node)，兄弟节点( Sibling Nodes )；
  - 边( Edge )：连接父节点和子节点；路径( Path )：连接两个节点的一系列边；
  - 层次( Level )：根节点为第 1 层，其子节点为第 2 层，依此类推；
  - 叶子节点( Leaf Node)：没有子节点的节点；
  - 度( Degree )：节点拥有子节点的数量；
  - 高度：
- 性质：
  - 

#### 7.1. 定义

##### 7.1.1. 二叉树( Binary Tree )

- 二叉树与树的区别在于：
  - 二叉树的每个节点拥有的子节点不超过两个；
  - 二叉树的子节点是有序的，有左右之分；
- 二叉树的特点：
  - 有n个节点的二叉树有n-1条边
  - 高度为h的二叉树最少有h个节点，最多有2^h^-1个节点
  - 有n个节点的二叉树高度最大为h，最小为h=⌈ log2(n+1) ⌉；

##### 7.1.2. 满二叉树

- 所有分支节点都存在左子树和右子树，且所有叶子节点都在同一层上 ；

##### 7.1.3. 完全二叉树

- 除最后一层外每一层节点数均达最大值，且最后一层节点全部集中在左侧的二叉树；

#### 7.2. 实现

#### 7.3. 应用



### 8. 优先级队列

#### 8.1. 定义

- 优先级队列(Priority Queue)：
  - 与普通队列(FIFO)不同，它的元素按照优先级排序，出队时总是返回优先级最高的元素，而不是按照入队顺序；

#### 8.2. 实现

##### 8.2.1. 基于线性表的优先级队列

##### 8.2.2. 基于堆的优先级队列

##### 8.2.3. 基于左高树的优先级队列

#### 8.3. 应用

### 9. 竞赛树  ？



### 10. 搜索树 ？

搜索树包含多种具体实现，主要分为两类：

- **无序搜索树**：如普通二叉搜索树（Binary Search Tree，BST）。

- 平衡搜索树

  ：通过特定规则避免树退化为链表，保证操作效率。例如：

  - **红黑树**（Red-Black Tree，C++ `std::map` 的底层实现）。
  - **AVL 树**（平衡因子限制为 ±1）。
  - **B 树**/**B + 树**（用于磁盘存储，多叉平衡树）。
  - **伸展树**（Splay Tree，通过伸展操作优化访问频率高的节点）。

### 11. 平衡搜索树 ？



### 12. 图 ？





## 算法 ？

### 1. 贪婪算法

### 2. 分而治之

### 3. 动态规划

### 4. 回溯法

### 5. 分支定界





