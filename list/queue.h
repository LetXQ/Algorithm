#pragma once
#include "com_def.h"

template <typename T>
class Queue
{
private:
    int m_iFront = 0;
    int m_iRear = 0;
    int m_iMax = 0;
    int m_iSize = 0;
    T* m_pArr = nullptr;
public:
    Queue(int max_size = MAX_SIZE);
    ~Queue();

    int EnQueue(const T& data);
    int DeQueue(T& data);
    bool IsFull() const;
    int Size() const;
};


template<typename T>
Queue<T>::Queue(int max_size)
    : m_iMax(max_size)
{
    m_pArr = new T[m_iMax];
    assert(m_pArr);
}

template<typename T>
Queue<T>::~Queue()
{
    if (m_pArr)
    {
        delete [] m_pArr;
        m_pArr = nullptr;
    }
}

template<typename T>
int Queue<T>::EnQueue(const T &data)
{
    if (IsFull())
        return ERR_QUEUE_FULL;
    m_pArr[m_iRear] = data;
    m_iRear = (m_iRear + 1) % m_iMax;
    ++m_iSize;
    return 0;
}

template<typename T>
int Queue<T>::DeQueue(T &data)
{
    if (m_iSize <= 0)
        return ERR_QUEUE_EMPTY;
    data = m_pArr[m_iFront];
    m_iFront = (m_iFront + 1) %m_iMax;
    --m_iSize;
    return 0;
}

template<typename T>
bool Queue<T>::IsFull() const
{
    return m_iSize == m_iMax;
}

template<typename T>
int Queue<T>::Size() const
{
    return m_iSize;
}
