#include <cstddef>
template <class T>
class MyVector
{
private:
    T *data;
    size_t capacity;
    size_t size;
    void expand(size_t newCapacity);

public:
    class iterator;
    MyVector() : data(nullptr), capacity(0), size(0) {}
    MyVector(int theCapacity) : data(new T[theCapacity]), capacity(theCapacity), size(0) {}
    ~MyVector() { delete[] data }
    void push_back(const T &value);
    void pop_back();
    iterator insert(iterator pos, const T &value);
    iterator erase(iterator pos);
    void clear() { size = 0; }
    bool empty() const { return size == 0; }
    T &operator[](size_t index) { return data[index]; }
    size_t size() const { return size; }
    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data + size); }
};

template <class T>
class MyVector<T>::iterator
{
private:
    T *ptr;

public:
    iterator(T *p = nullptr) : ptr(p) {}
    iterator operator++(int)
    {
        iterator temp = *this;
        ptr++;
        return temp;
    }
    T &operator*() { return *ptr; }
    bool operator==(const iterator &other) const { return (this->ptr == other.ptr); }
    iterator operator+(size_t n) const { return iterator(ptr + n); }
};

template <class T>
void MyVector<T>::push_back(const T &value)
{
    if (size >= capacity)
        expand(capacity == 0 ? 1 : capacity * 2);
    data[size++] = value;
}

template <class T>
void MyVector<T>::pop_back()
{
    if (size > 0)
        size--;
}

template <class T>
MyVector<T>::iterator MyVector<T>::insert(MyVector<T>::iterator pos, const T &value)
{
    if (pos.ptr < data || pos.ptr > data + size)
        return end();

    size_t index = pos.ptr - data;
    if (size >= capacity)
        expand(capacity == 0 ? 1 : capacity * 2);

    for (size_t i = size; i > index; i--)
        data[i] = data[i - 1];

    data[index] = value;
    return iterator(data + index);
}

template <class T>
MyVector<T>::iterator MyVector<T>::erase(MyVector<T>::iterator pos)
{
    if (pos.ptr < data || pos.ptr > data + size)
        return end();

    size_t index = pos.ptr - data;
    for (size_t i = index; i < size - 1; i++)
        data[i] = data[i + 1];
    size--;
    return iterator(data + index);
}

template <class T>
void MyVector<T>::expand(size_t newCapacity)
{
    T *newData = new T[newCapacity];
    for (size_t i = 0; i < size; ++i)
        newData[i] = data[i];
    delete[] data;
    data = newData;
    capacity = newCapacity;
}