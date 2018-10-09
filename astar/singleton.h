#ifndef SINGLETON_H
#define SINGLETON_H
#include <pthread.h>
#include <stdlib.h>

template<class T>
class Singleton
{
public:
    static T& Instance()
    {
        pthread_once(&m_ponce, &Singleton::Init);
        return *m_instance;
    }

private:
    static void Init()
    {
        m_instance = new T();
        atexit(Destroy);
    }

    static void Destroy()
    {
        if (m_instance)
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }

private:
    static T* volatile m_instance;
    static pthread_once_t m_ponce;
};

template<class T>
T* volatile Singleton<T>::m_instance = NULL;

template<class T>
pthread_once_t Singleton<T>::m_ponce = PTHREAD_ONCE_INIT;
#endif // SINGLETON_H
