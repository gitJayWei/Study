/*******************************************************************************
* FileName:         FLinkedList.hpp
* Author:           冯桥
* Student Number:   3017216006
* Date:             2021/03/23 22:47:53
* Version:          v1.0
* Description:      Data Structure Experiment #2.1
*                   请补全FLinkedList类。FLinkedList即单链表，指Forward Linked List。
                    因为单链表只能正向遍历（无法快速求前驱），因此称之为Forward。
*******************************************************************************/
#ifndef FLinkedList_H
#define FLinkedList_H
#include <iostream>
using namespace std;
template <class T>
class FLinkedList
{
public:
    struct Node
    {
        T value;
        Node *next;
        // 这是Node结构体的构造函数，方便你下面调用。
        Node() {}
        Node(T _value, Node *_next) : value(_value), next(_next) {}
    };

    // 头结点
    /**
        记得复习：为什么需要头结点？带头结点的好处是什么？
    */
    Node *head;

    // 尾指针
    /**
        一般都是向表尾添加元素。因此这里额外维护一个尾指针。
        PPT里有提到过尾插法和尾指针哦！后面 void append(T& data) 会用到。
    */
    Node *last;

    // 链表长度
    /**
        一般会顺手维护一个链表长度，这样求元素个数就很方便。
    */
    int len;

    /**
        构造函数，构建一个 FLinkedList。
        @name FLinkedList();
        ---------------------------------------------------
        为了防止同学们不知道该干什么，助教决定把它实现了。
        但是记得复习：创建一个链表时需要做什么？
    */
    FLinkedList()
    {
        // 创建链表要做的就是把头结点安排好
        len = 0;
        head = new Node(0, NULL);
        last = head;
    }

    /**
        析构函数
        @name ~FLinkedList();
        -------------------------------------------------------
        记得把所有结点都释放哦，小心内存泄漏。
    */
    ~FLinkedList()
    {
        Node *tmp;
        Node *now = head;
        for (int i = 0; i < len; i++)
        {
            tmp = now->next;
            delete now;
            now = tmp;
        }
    }

    /**
        询问FLinkedList现有元素的个数
        @name length();
        @return int 当前FLinkedList包含元素的个数
    */
    int length()
    {
        return len;
    }

    /**
        获取location位置的元素（从0开始标号)
        @name at(int);
        @param  location 需要查询元素的位置
        @return int FLinkedList在location位置的元素
    */
    T at(int location)
    {
        if (location < 0 || location >= len)
        {
            throw out_of_range("Invalid location");
        }

        Node *current = head->next;
        for (int i = 0; i < location; ++i)
        {
            current = current->next;
        }
        return current->value;
    }

    /**
        插入元素
        @name insert(T&, int);
        @param  data        需要插入的元素
                location    插入元素的位置
        @return bool    true 插入成功，false插入失败
        ----------------------------------------------------------
        插入失败是指location不对的情况
    */
    bool insert(const T &data, int location)
    {
        if (location < 0 || location > len)
            return false;

        Node *prev = head;
        for (int i = 0; i < location; ++i)
            prev = prev->next;

        Node *newNode = new Node(data, prev->next);
        prev->next = newNode;

        if (location == len)
            last = newNode;

        len++;
        return true;
    }

    /**
        删除位于location的元素
        @name erase(int);
        @param  location 需要删除元素的位置
        @return bool    true 删除成功，false删除失败
        ----------------------------------------------------------
        删除失败是指location不对的情况
    */
    bool erase(int location)
    {
        if (location < 0 || location >= len)
        {
            return false;
        }

        Node *prev = head;
        for (int i = 0; i < location; ++i)
        {
            prev = prev->next;
        }

        Node *toDelete = prev->next;
        prev->next = toDelete->next;

        if (toDelete == last)
        {
            last = prev;
        }

        delete toDelete;
        len--;
        return true;
    }

    /**
        将链表进行翻转操作。
        @name converse();
        ---------------------------------------------------------
        例如， FLinkedList开始为 1 2 3 4 5，
        则翻转后为  5 4 3 2 1
    */
    void converse()
    {
        if (len <= 1)
            return;

        Node *prev = nullptr;
        Node *current = head->next;
        Node *next = nullptr;

        last = current;

        while (current != nullptr)
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        head->next = prev;
    }

    /**
        将data插入到链表表尾。
        @name append(T&);
        @param data 要插入的元素。
    */
    void append(const T &data)
    {
        Node *newNode = new Node(data, nullptr);
        last->next = newNode;
        last = newNode;
        len++;
    }

    /**
        将append_list拼接到当前链表后，拼接后append_list将为空链表
        @name append(FLinkedList&);
        @param  append_list 被拼接的链表。
    */
    void append(FLinkedList &append_list)
    {
        if (append_list.len == 0)
            return;

        last->next = append_list.head->next;
        last = append_list.last;
        len += append_list.len;

        append_list.head->next = nullptr;
        append_list.last = append_list.head;
        append_list.len = 0;
    }

    /**
        将链表元素顺序输出。
        @name print();
        ---------------------------------------------------------
        本函数在测试中不会被调用，仅为方便大家调试。
    */
    void print()
    {
        Node *now = head;
        for (int i = 0; i < len; i++)
        {
            now = now->next;
            cout << now->value << endl;
        }
    }
};
#endif