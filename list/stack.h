#pragma once
#include "com_def.h"

template <typename T>
class Stack
{
private:
    int m_iTop = -1;
    int m_iMax = MAX_SIZE;
    T* m_pArr = nullptr;
public:
    Stack(int max_size = MAX_SIZE);
    ~Stack();
    int Pop(T& data);
    int Push(const T& data);
    bool IsFull() const;
    int Size() const;
};


template<typename T>
Stack<T>::Stack(int max_size)
    : m_iMax(max_size)
{
    m_pArr = new T[m_iMax];
    assert(m_pArr);
}

template<typename T>
Stack<T>::~Stack()
{
    if (m_pArr)
    {
        delete [] m_pArr;
        m_pArr = nullptr;
    }
}

template<typename T>
int Stack<T>::Pop(T &data)
{
    if (m_iTop < 0)
        return ERR_STACK_EMPTY;
    data = m_pArr[m_iTop--];
    return 0;
}

template<typename T>
int Stack<T>::Push(const T &data)
{
    if (IsFull())
        return ERR_STACK_FULL;
    m_pArr[++m_iTop] = data;
    return 0;
}

template<typename T>
bool Stack<T>::IsFull() const
{
    std::cout << "size: " << m_iTop << ", max: " << m_iMax << std::endl;
    return m_iTop >= m_iMax - 1;
}

template<typename T>
int Stack<T>::Size() const
{
    return m_iTop + 1;
}
