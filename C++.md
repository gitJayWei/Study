# https://www.doubao.com/thread/wd12665878ef8403f

## 面向过程部分

### 一. 预处理指令

#### #define

##### 1. 无参数宏

~~~cpp
#define 宏名 替换文本
~~~

- 仅做文本替换，不会检查；
- 作用域到文件末，或到#undef；

##### 2. 带参数宏

~~~cpp
#define ADD(a, b) ((a) + (b))

int main() {
    int a = 5, b = 3;
    int m = ADD(a, b); // 8
}
~~~

- 别称 宏函数，仅做文本替换，不会检查；

- 定义时用括号包裹

  ~~~cpp
  #define BAD_SQUARE(x) x*x
  int n = 4;
  int val = BAD_SQUARE(n+1); // 展开为 n+1*n+1 = n + (1*n) + 1 
  ~~~

##### 3. 取消宏定义

~~~cpp
#undef 宏名
~~~

##### 4. 现代做法

- 现代C++更推荐用 inline / const / enum / constexpr 替代宏；

#### #include

~~~cpp
#include <iostream>  // 系统头文件
#include "myheader.h" // 用户自定义文件
~~~

- 避免头文件的重复包含

  ~~~cpp
  // myheader.h
  #ifndef MYHEADER_H
  #define MYHEADER_H
  
  // header content
  
  #endif
  ~~~

  或现代做法

  ~~~cpp
  #pragma once
  ~~~

#### #if

##### 1.#ifdef`/`#ifndef`/`#endif

~~~cpp
#ifdef 宏名
    // 若已定义宏名，编译此处代码
#endif

#ifndef 宏名
    // 若未定义宏名，编译此处代码
#endif
~~~

##### 2. #if`/`#elif`/`#else

~~~cpp
#if 表达式1
    // 若表达式1为真，编译此处代码
#elif 表达式2
    // 若表达式1为假 且 表达式2为真，编译此处代码
#else
    // 都不为真，编译此处代码
#endif

// 注：必须是编译期确定的常量表达式
~~~

- defined(宏名) 可用于检测宏名是否定义

  ~~~cpp
  #if defined(DEBUG)
      std::cout << "Debugging...\n";
  #endif
  ~~~

#### #pragma

| 用法                               | 说明                                      |
| ---------------------------------- | ----------------------------------------- |
| #pragma once                       | 防止头文件被重复包含                      |
| #pragma pack(n)                    | 设置结构体成员的对齐方式（按 n 字节对齐） |
| #pragma warning                    | 控制编译器警告（如 MSVC）                 |
| #pragma message("text")            | 在编译输出中打印消息                      |
| #pragma region / #pragma endregion | 在 VS 中折叠代码区域                      |



### 二. 基本数据类型

#### 内置类型与字面量

##### 1. 内置类型

##### 2. 常量

##### 3. 字面量

##### 4. 枚举

#### 变量特性

##### 1. 变量声明

##### 2. 初始化

##### 3. 作用域

##### 4. 生命周期

#### 类型别名

##### 1. 基本类型别名定义

##### 2. 复杂类型（指针、数组）的别名简化

#### 类型转换

##### 1. 隐式

##### 2. 显式

##### 3. static_cast



### 三. 运算符与表达式

#### 运算符类型

##### 1. 算术

##### 2. 逻辑

##### 3. 关系

##### 4. 位运算

#### 运算优先级与结合性

#### 表达式求值与副作用



### 四. 控制流

#### 分支语句

if-else switch-case

#### 循环语句

for while do-while

#### 跳转语句

break continue goto



### 五. 函数

#### 函数基础

##### 1. 声明与定义

##### 2. 参数传递

#### 函数特性

##### 1. 重载

##### 2. 默认参数

##### 3. 内联函数

#### 特殊函数

##### 1. 递归函数

##### 2. 函数指针



### 六. 数组与指针

#### 数组类型

##### 1. 静态数组

##### 2. 动态数组

#### 指针特性

##### 1. 指针

##### 2. 指针算术

##### 3. const指针

#### 数组与指针

##### 1. 数组名退化



### 七. 引用



### 八. 内存管理



### 九. 字符串

#### C风格字符串

#### C++ string



### 十. 结构体与联合体

#### 结构体

##### 1. 定义与声明

##### 2. 成员访问

##### 3. 结构体数组与指针

#### 联合体

##### 1. 定义与特性

##### 2. 使用场景

#### 







## 面向对象部分

### 一. 类与对象基础

#### 类与对象

##### 1. 类的定义

- 类是用户自定义的数据类型，包括属性(成员变量)与行为(成员函数)；

~~~cpp
class Buffer {
private:
    char* data;  // 8 Byte (64位系统)
    size_t size; // 8 Byte 
public:
    void alloc(size_t s);
};
~~~

- sizeof(Buffer) = 16，不包含成员函数；

##### 2. 对象的创建与销毁

~~~cpp
Buffer buf; // 栈上分配内存
Buffer* p = new Buffer; // 堆上分配内存

// 栈对象会在作用域结束时自动回收(调整栈指针)
// 堆对象需手动delete释放
delete p;
~~~

#### 访问控制

##### 1. public与private

- 封装的基础 ，用于区分外部接口与内部实现；

  ~~~cpp
  class BankAccount {
  private:
      double balance;  // 内部数据，不暴露
  public:
      // 通过public接口访问private数据，而非直接暴露成员变量
      double getBalance() const { return balance; }
  };
  ~~~

##### 2. protected

- 仅能被基类自身和子类的成员函数访问，，而private成员子类也无法访问；

#### 特殊函数

##### 1. 构造函数

- 初始化：如果构造函数有初始化列表，则按照列表进行初始化；没有则执行成员的默认构造函数(默认初始化)；
  - 初始化顺序与成员变量的声明顺序一致，而不是初始化列表的顺序；
  - **构造函数体内的语句执行于初始化之后**；
  - 所以 const成员变量；引用成员变量；无默认构造的类成员；必须使用初始化列表；

~~~cpp
class Test {
    int a;
    int b;
public:
    Test() : b(2), a(b) {} // a会被初始化为未定义值
};
~~~

~~~cpp
Test(int val1, int val2) {
    a = val1;
    b = val2
    // 实际上在赋值之前a,b已经被初始化
    // 所以如果a,b是自定义类型而且没有默认构造，这种写法就会报错
}
~~~

- 如果没有任何构造函数，编译器会生成一个默认的；

  只要写了任何构造函数，编译器不会再生成默认的；

  ~~~cpp
  class Point {
  private:
      int x, y;
  public:
      // 手动定义了带参构造函数，默认构造函数不再生成
      Point(int x_, int y_) : x(x_), y(y_) {}
  };
  
  int main() {
      Point p;  // 编译报错：没有合适的默认构造函数
      return 0;
  }
  ~~~

  解决：C++11可显式声明 Point() = default; 来保留默认构造；

- 关键字explicit：阻止隐式类型转换：

  ~~~cpp
  class String {
  public:
      // 单参数构造函数：const char* → String
      String(const char* str) { /* 实现 */ }
  
      // 禁止隐式转换的版本
      // explicit String(const char* str) { /* 实现 */ }
  };
  
  void func(String s) { /* ... */ }
  
  int main() {
      func("hello");  // 若构造函数未加explicit，会隐式转换为String("hello")
                      // 若加了explicit，编译报错（需显式调用：func(String("hello"))）
      return 0;
  }
  ~~~

  建议：所有单参数构造函数都添加explicit关键字；

##### 2. 析构函数

- 析构函数会先执行函数体内语句，再销毁成员变量，所以需要在析构函数体内释放对象持有的资源；

- 而对象本身的内存：栈对象会在作用域结束自动回收，堆对象需手动释放；

~~~cpp
#include <iostream>

class Simple {
private:
    int* data;
public:
    Simple() { data = new int(100); }
    // 构造函数“申请的资源”不在对象本身内存中
    ~Simple() { delete data; }
    // 析构函数只释放了“持有的资源”
};

int main() {
    {
   		Simple obj1;  // 栈对象
    } // 作用域结束，自动调用析构函数
    // 析构成功后，回收栈对象本身内存(调整栈指针)
    
    Simple* obj2 = new Simple;  // 堆对象
    delete obj2;  // 手动delete
    // delete实际为两步
    // 1，调用析构函数obj2->~Simple()
    // 2，释放堆对象本身内存(指针obj2)
    
    return 0;
}
~~~

- 虚析构函数：多态的必要条件；

  - 

##### 3. 拷贝构造函数

~~~cpp
class Simple {
private:
    int* data;
public:
    Simple() { data = new int(100); }
    
    // 拷贝构造函数
    Simple(const Simple& other) {
        data = new int(*(other.data)); // 深拷贝：创建新的int并复制值
    }
    
    // 拷贝赋值运算符
    Simple& operator=(const Simple& other) {
        if (this != &other) { // 自赋值检查
            delete data;          // 释放原有资源
            data = new int(*(other.data)); // 深拷贝新资源
            // 当然，也可以*data = *(other.data);直接赋值
        }
        return *this;
    }
    
    ~Simple() { delete data; }
};
~~~

- 生成规则：
  - 默认生成：类中无自定义拷贝构造函数，编译器会生成默认的；
  - 不会生成：类中有引用成员或const成员，编译器不会生成默认的，必须自定义；
  - 抑制生成：一旦自定义了拷贝构造函数，编译器将不会再生成默认构造函数；
- 调用时机：
  - 初始化新对象：用一个已存在的对象初始化另一个新对象；
  - 值传递传参：对象作为函数参数，以值传递的方式传入函数体；
  - 值方式返回：对象作为函数返回值，以值返回的方式从函数返回；
- 浅拷贝与“三法则”：
  - 编译器提供的默认拷贝构造函数是浅拷贝(按位拷贝)，仅复制成员变量的值，不会复制指向的资源；
  - 如果一个类需要管理动态资源（如堆内存），浅拷贝会导致多个对象共享同一资源，引发重复释放等；
  - 因此，如果类中需要自定义以下任何一个函数，通常意味着也需要自定义另外两个，这被称为“三法则”：
    - 拷贝构造函数；
    - 赋值运算符重载 (`operator=`)；
    - 析构函数；

#### this指针与const成员函数

##### 1. this 指针

- 所有`非静态成员函数`都隐含一个this指针参数(指向调用对象)

  | 成员函数类型    | 是否有this指针 | this指针的类型        | 能否修改对象     |
  | --------------- | -------------- | --------------------- | ---------------- |
  | 非静态，非const | 有             | MyClass * const       | 能               |
  | 非静态，const   | 有             | const MyClass * const | 不能             |
  | 静态            | 无             | 无                    | 无法访问实例对象 |

  ~~~cpp
  class MyClass {
  private:
      size_t size; 
  public:
      void alloc(size_t s);
  };
  MyClass cla;
  cla.alloc(s);
  
  // alloc函数会被编译器处理为
  void MyClass::alloc(MyClass* this, size_t s);
  // 调用alloc函数实际为
  alloc(&cla, s); // this = &cla;
  ~~~

- 用途：

  - 区分成员变量与局部变量(或参数)

    ~~~cpp
    class Person {
    private:
        int age;
    public:
        Person(int age) {this->age = age;} // 不用this，成员变量age会被参数age屏蔽
    };
    ~~~

  - 成员函数返回对象本身(实现链式调用)

    ~~~cpp
    class MyString {
    private:
        std::string data;
    public:
        MyString& append(const std::string& str) {
            data += str;
            return *this; // 返回调用对象本身的引用
        }
    };
    
    MyString str;
    str.append("abc").append("efg");
    ~~~

  - 在成员函数中传递对象自身

    ~~~cpp
    void ExternalFunc(const Person& p);
    class Person {
        // ...
        void registerSelf() {
        	ExternalFunc(*this);
        }
    }
    ~~~

- 生命周期：this指针只在成员函数被调用时存在，它是一个函数调用时产生，函数返回时销毁的局部变量(或参数)；

##### 2. const成员函数

- const成员函数无法修改任何非mutable的成员变量，this指针类型为const MyClass * const；

- const对象只能调用const成员函数，非const对象都可以调用(**this指针能从非const转换为const，反过来不行**)；

- 由于const限定符会被视为函数签名的一部分，因此可用于重载；

  - 调用优先级：const对象只能调用const成员函数，非const对象**优先**调用非const成员函数；(**this指针能从非const转换为const，反过来不行**)；

  ~~~cpp
  class Demo
  {
  public:
      void func() { cout << "non-const" << endl; }
      void func() const { cout << "const" << endl; }
  };
  
  int main()
  {
      Demo d;
      d.func(); // non-const
      
      const Demo d2;
      d2.func(); // const
  
      return 0;
  }
  ~~~

- mutable关键字：如果成员变量被声明为mutable类型，那么const成员函数也可以修改；



### 二. 封装与抽象

#### 数据隐藏，接口设计

#### 类的组合（has-a关系）



### 三. 继承与派生（三，四同时进行）

#### 继承基础

##### 1. 基本概念定义

- 基类 Base Class；派生类 DERived Class；

~~~cpp
class Base {
    /* 基类定义 */
};

class Derived : public Base { // public继承
	/* 子类定义 */  
};
~~~

##### 2. 继承方式与访问权限

- 三种继承方式：public、protected和private；

- 访问权限表：

  | 继承方式  | 基类中权限                   | 派生类中权限                     |
  | --------- | ---------------------------- | -------------------------------- |
  | public    | public / protected / private | public / protected / 不可访问    |
  | protected | public / protected / private | protected / protected / 不可访问 |
  | private   | public / protected / private | private / private / 不可访问     |

  - 无论继承方式，派生类都无法访问基类的private成员；
  - **友元关系不继承**：基类的友元不是派生类的友元；

- using声明可改变访问权限；

~~~cpp
class Base {
public:
	void func() {}   
};

class Derived : private Base { // private继承
public:
    using Base::func; // 将func()访问权限提升为public
};

void test()
{
    Derived d;
	d.func(); // 合法
}
~~~

#### 构造与析构

##### 1. 构造

- 派生类的构造函数的初始化列表必须带有基类构造函数，只是如果基类有默认构造，编译器会自动插入；

  - 原因是之前提到过的：构造函数体内的语句发生于初始化之后

  ~~~cpp
  class Base {
  private:
      int a;
  public:
      Base(int x) : a(x) {} // 无默认构造
  };
  
  class Derived : public Base {
  private:
      int b;
  public:
      Derived(int val) : Base(val), b(val) {}
  };
  ~~~

  - 执行顺序：基类构造 -> 构造派生类成员(声明顺序)  -> 派生类构造函数体内语句；

##### 2. 析构

- 析构顺序与构造顺序完全相反：派生类析构函数体内语句 -> 析构派生类成员(声明的逆序) -> 基类析构

- 基类析构函数的虚函数特性：
  - 

#### 隐藏与覆盖

##### 1. 成员函数隐藏

（派生类隐藏基类同名成员函数）

（使用作用域运算符访问被隐藏成员）

##### 2. 虚函数覆盖

（虚函数与动态多态性（覆盖））

##### 3. override与final

（override和final关键字（C++11））

（重载、隐藏与覆盖的对比）

#### 菱形继承与虚继承

##### 1. 多继承问题

（多继承中的菱形继承问题）

##### 2. 虚继承概念

（虚继承与虚基类概念）

（虚继承的构造函数调用规则）

##### 3. 解决方案

（虚继承解决二义性原理）

（虚继承的内存布局影响）





### 四 . 多态

#### 虚函数与纯虚函数

#### 动态绑定（运行时多台）与静态绑定

#### 抽象类与接口

#### 虚析构函数

### 五. 运算符重载

#### 成员函数重载与非成员函数重载

#### 常见运算符重载

#### 赋值运算符重载与深浅拷贝

### 六. 特殊类与机制

#### 友元（友元函数，友元类）

#### 静态成员（静态变量，静态函数）

#### 嵌套类与局部类







## 泛型编程部分

### 一. 模板

#### 函数模板

##### 1. 语法与定义

- ~~~cpp
  template<typename T, int N>
  T func(T (&arr)[N]) { /* 实现 */ }
  ~~~

  - 类型参数：typename / class；
  - 非类型参数：编译期确定的常量表达式；

##### 2. 模板实例化

- 三种方式：隐式实例化，显式实例化，显式特化；
- 注意：
  - 显示实例化只能在全局或命名空间作用域；
  - 函数模板在显式特化时必须指定全部类型参数(非类型参数可不指定)，类模板没有此限制(可部分特化)；

~~~cpp
template double func<double, 5>(double (&arr)[5]); // 显式实例化

// 显式特化
// 显式指定类型参数T为MyData而非类型参数N仍保留为模板参数
template<int N> 
MyData func<MyData, N>(MyData (&arr)[N])
{ /* 针对MyData的实现 */ }

void test() 
{
	int arr1[] = {1, 2, 3, 4, 5};
    func(arr1); // 隐式实例化，自动生成func<int, 5>实例
    
    double arr2[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    func(arr2); // 直接调用已实例化的func<double, 5>
}
~~~

##### 3. 模板的重载

~~~cpp
void Swap(int &a, int &b) { /* 实现 */ }
    
template<typename T>
void Swap(T &a, T &b) { /* 实现 */ }

template<typename T>
void Swap(T &a, T &b, int n) { /* 实现 */ } 
~~~

##### 4. 调用优先级

- 对同一个函数名，可以同时存在：普通函数，模板函数，显式特化模板函数及它们的重载；
- 函数被调用时，普通函数 > 显式特化 > 模板函数(编译器自动实例化)；



#### 类模板

类模板定义与实例化

类模板的成员函数（体外定义语法）

类模板的继承（模板类作为基类 / 派生类）

类模板的特化（显式特化、部分特化





### 二. 模板进阶

#### 模板参数推导规则

#### 可变参数模板（C++11 及以上）

#### 模板元编程基础（编译期计算）

#### 类型萃取（type traits）

https://chat.deepseek.com/share/rxm70la27akondfr9v



### 三. 标准模板库STL







## 高级特性部分

### 内存管理

- 动态内存（new/delete、new []/delete []）
- 智能指针（unique_ptr、shared_ptr、weak_ptr，C++11 及以上）
- 内存泄漏与避免

### 异常处理

- try-catch 块、throw 表达式
- 异常规格说明（noexcept）
- 标准异常类

### 命名空间

- 命名空间定义与使用（namespace）
- 命名空间别名、匿名命名空间
- 作用域解析运算符（::）

### 现代C++特性

- 自动类型推导（auto、decltype）
- 范围 for 循环
- 移动语义与右值引用（C++11 及以上）
- constexpr（编译期常量与函数） 