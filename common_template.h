#ifndef COMMON_TEMPLATE_H
#define COMMON_TEMPLATE_H

template<typename T>
void CommonSwap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

#endif // COMMON_TEMPLATE_H
