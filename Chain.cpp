// 单链表的实现
#include <iostream>

class Chain; // 前置声明
class Node   // 节点类
{
    friend class Chain; // 友元

private:
    int data;   // 数据域
    Node *next; // 指针域
};
class Chain // 链表类
{
public:
    Chain();                               // 构造函数
    ~Chain();                              // 析构函数
    bool isEmpty() { return length == 0; } // 判断是否为空
    int Length() { return length; }        // 返回长度
    bool Find(int i, int &x);              // 将第i个元素赋值给x
    int Search(const int &x);              // 查找元素x的位置
    bool Insert(int i, const int &x);      // 在第i个位置插入元素x
    void Push_back(const int &x);          // 在末尾插入元素x
    bool Delete(int i);                    // 删除第i个元素
    void Reverse();                        // 反转链表
    void ClearList();                      // 清空链表
    void output(std::ostream &out) const;
    friend std::ostream &operator<<(std::ostream &out, const Chain &x);

    Node *head; // 头指针
    int length; // 长度
};

Chain::Chain()
{
    head = new Node;   // 在堆区开辟头节点
    head->next = NULL; // 初始化头结点的指针域
    length = 0;        // 初始化长度
}

Chain::~Chain()
{
    ClearList(); // 清空链表
    delete head; // 释放头节点
}

bool Chain::Find(int i, int &x)
{
    if (i < 0 || i > length - 1)
        return false;
    Node *p = head->next; // p指向第0个节点
    for (int j = 0; j < i; j++)
        p = p->next; // 循环结束后p指向第i个节点
    x = p->data;
    return true;
}

int Chain::Search(const int &x)
{
    Node *p = head->next; // p指向第0个节点
    for (int i = 0; p != NULL; i++)
    {
        if (p->data == x) // 每次循环p都指向第i个节点
            return i;
        p = p->next;
    }
    return -1;
}

bool Chain::Insert(int i, const int &x)
{
    if (i < 0 || i > length) // 这里i可以等于length是因为可以在末尾插入元素
        return false;
    Node *p = head; // p指向头节点
    for (int j = 0; j < i; j++)
        p = p->next;       // 循环结束后p指向第i-1个节点
    Node *temp = new Node; // 在堆区开辟新节点
    temp->data = x;        // 将新节点的数据域赋值为x
    temp->next = p->next;  // 将新节点的指针域指向原来的第i个节点
    p->next = temp;        // 将第i-1个节点的指针域指向新节点
    length++;              // 长度加1
    return true;
}

void Chain::Push_back(const int &x)
{
    Node *p = head;
    while (p->next != nullptr)
        p = p->next; // p指向最后一个节点
    Node *temp = new Node;
    temp->data = x;
    temp->next = nullptr;
    p->next = temp;
    length++;
}

bool Chain::Delete(int i)
{
    if (i < 0 || i > length - 1)
        return false;
    Node *p = head; // p指向头节点
    for (int j = 0; j < i; j++)
        p = p->next;      // 循环结束后p指向第i-1个节点
    Node *temp = p->next; // q指向第i个节点
    p->next = temp->next; // 将第i-1个节点的指针域指向原来的第i+1个节点
    delete temp;          // 释放第i个节点
    length--;             // 长度减1
    return true;
}

void Chain::Reverse()
{
    Node *prev = nullptr;
    Node *current = head->next;
    Node *next;
    while (current != nullptr)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head->next = prev;
}

void Chain::ClearList()
{
    Node *p = head->next; // p指向第0个节点
    while (p != NULL)
    {
        // 头结点指针域的指向不断后移，借助p不断删除未被头节点指向的节点
        head->next = p->next;
        delete p;
        p = head->next;
    }
    length = 0;
    // 此时head->next为野指针，虽然没有使用，但是最好置空
    head->next = nullptr;
}

void Chain::output(std::ostream &out) const
{
    Node *p = head->next;
    while (p != NULL)
    {
        out << p->data << " ";
        p = p->next;
    }
}

std::ostream &operator<<(std::ostream &out, const Chain &x)
{
    x.output(out);
    return out;
}