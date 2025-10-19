/*
 * FileName:         FLinkedList.hpp
 * Author:           Jay Wei<jaywei0610@gmail.com>
 * Date:             2025/10/19
 * 带有头结点和尾指针的单链表
 */

#pragma once

namespace my_stl
{
    template <class T>
    class Node; // 前向声明

    // <----------------FLinkedList类定义------------------>
    template <class T>
    class FLinkedList
    {
    public:
        FLinkedList();
        ~FLinkedList();
        [[nodiscard]] bool isEmpty() const { return len == 0; }
        [[nodiscard]] int Length() const { return len; }
        bool Find(int i, T &x) const;
        T &operator[](int i);
        int Search(const T &x) const;
        bool Insert(int i, const T &x);
        void Push_Back(const T &x) { Insert(len, x); }
        bool Delete(int i);
        void Reverse();
        void ClearList();

    private:
        Node<T> *head;
        Node<T> *tail;
        int len;
    };

    // <------------------Node类定义-------------------->
    template <class T>
    class Node
    {
        friend class FLinkedList<T>;

    public:
        Node() = default;
        explicit Node(const T &_data, Node<T> *_next = nullptr) : data(_data), next(_next) {}

    private:
        T data;
        Node<T> *next;
    };

    // <----------------FLinkedList构造函数------------------>
    template <class T>
    FLinkedList<T>::FLinkedList()
    {
        head = new Node<T>;
        tail = head;
        len = 0;
    }

    // <----------------FLinkedList析构函数------------------>
    template <class T>
    FLinkedList<T>::~FLinkedList()
    {
        ClearList(); // 借助ClearList删掉除头节点外的所有节点
        delete head;
    }

    // <----------------Find成员函数------------------>
    template <class T>
    bool FLinkedList<T>::Find(int i, T &x) const
    {
        if (i < 0 || i >= len)
            return false;

        Node<T> *p = head->next; // 此时p指向第0个节点

        // 每次循环开始前，p指向第j个节点
        // j = i时循环结束，p指向第i个节点
        for (int j = 0; j < i; j++)
            p = p->next;

        x = p->data;
        return true;
    }

    // <----------------operator[]重载------------------>
    template <class T>
    T &FLinkedList<T>::operator[](int i)
    {
        if (i < 0 || i >= len)
            throw std::out_of_range("Index out of range");

        Node<T> *p = head->next; // 此时p指向第0个节点

        // 每次循环开始前，p指向第j个节点
        // j = i时循环结束，p指向第i个节点
        for (int j = 0; j < i; j++)
            p = p->next;

        return p->data;
    }

    // <----------------Search成员函数------------------>
    template <class T>
    int FLinkedList<T>::Search(const T &x) const
    {
        Node<T> *p = head->next; // 此时p指向第0个节点

        // 每次循环开始前，p指向第i个节点
        for (int i = 0; i < len; i++)
        {
            if (p->data == x)
                return i;
            p = p->next;
        }
        return -1;
    }

    // <----------------Insert成员函数------------------>
    template <class T>
    bool FLinkedList<T>::Insert(int i, const T &x)
    {
        if (i < 0 || i > len) // i可以取len，插入到链表尾部
            return false;

        // 因为要找到插入位置前一个节点，所以p指向头节点而不是第0个节点
        Node<T> *p = head;

        // 每次循环开始前，p指向第j-1个节点
        // j = i时循环结束，p指向第i-1个节点
        for (int j = 0; j < i; j++)
            p = p->next;

        // 让newNode指向p的下一个节点，即第i个节点
        auto newNode = new Node<T>(x, p->next);

        p->next = newNode; // 让p指向newNode

        if (i == len)       // 如果插入到链表尾部
            tail = newNode; // 更新尾指针

        len++;
        return true;
    }

    // <----------------Delete成员函数------------------>
    template <class T>
    bool FLinkedList<T>::Delete(int i)
    {
        if (i < 0 || i >= len)
            return false;

        // 因为要找到删除位置前一个节点，所以p指向头节点而不是第0个节点
        Node<T> *p = head;

        // 每次循环开始前，p指向第j-1个节点
        // j = i时循环结束，p指向第i-1个节点
        for (int j = 0; j < i; j++)
            p = p->next;

        // 因为要改变第i-1个节点的next指向，先让q维护第i个节点
        Node<T> *q = p->next;

        p->next = q->next; // 让p指向第i+1个节点

        if (i == len - 1) // 如果删除的是最后一个节点
            tail = p;     // 更新尾指针

        delete q;
        len--;
        return true;
    }

    // <----------------Reverse成员函数------------------>
    template <class T>
    void FLinkedList<T>::Reverse()
    {
        // 如果链表为空或只有一个节点，则无需反转
        if (len <= 1)
            return;
        /*
         * 翻转的思路是将每个节点的next指针指向前一个节点
         * 由于单链表无法访问前一个节点，所以需要一个指针prev来保存前一个节点
         * 更改当前节点的next指针后会丢失下一个节点，所以需要next指针来保存下一个节点
         */

        Node<T> *oldhead = head;
        // 定义三个指针，分别指向当前节点、前一个节点和后一个节点
        Node<T> *prev = nullptr;
        Node<T> *curr = head->next;
        Node<T> *next = nullptr;

        // 遍历链表，直到当前节点为空
        while (curr != nullptr)
        {
            next = curr->next; // 保存下一个节点
            curr->next = prev; // 将当前节点的next指向前一个节点
            prev = curr;       // 前一个节点后移
            curr = next;       // 当前节点后移
        }

        // 最后将头指针指向反转后的最后一个节点
        head->next = prev;
        tail = oldhead->next; // 更新尾指针
    }

    // <----------------ClearList成员函数------------------>
    template <class T>
    void FLinkedList<T>::ClearList()
    {
        Node<T> *curr = head->next;
        while (curr)
        {
            // next指针不断后移，借助curr指针删除节点
            Node<T> *next = curr->next;
            delete curr;
            curr = next;
        }
        head->next = nullptr;
        tail = head;
        len = 0;
    }
} // namespace my_stl