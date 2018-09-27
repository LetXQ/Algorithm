#pragma once
#include "com_def.h"
#include "../kmp.h"

class MyString
{
public:
    /*
     * 两个字符串比较，返回-1，0，1, 2
    */
    static int StrCompare(const char src[], const char dest[])
    {
        int s_len = strlen(src), d_len = strlen(dest);
        if (s_len > d_len)
            return 1;
        else if (s_len < d_len)
            return -1;
        else
        {
            int i = 0;
            while (i < s_len)
            {
                if (src[i] != dest[i])
                    return 2;
                ++i;
            }
            return 0;
        }
    }

    /*
     * 字符串赋值，调用前需判断目标串长度是否足够
     * 返回char*是为了使函数能够支持链式表达式
    */
    static char* StrCpy(const char* src, char* dest)
    {
        // 地址是否合法最好也放在外部判断
        if (!src || !dest)
            return nullptr;
        // 两串相等，直接返回，这里暂不考虑内存重叠
        if (src == dest)
            return dest;

        char* tmp = dest;

        // 该判断条件可以保证'\0'也被复制
        while((*dest++ = *src++) != '\0')
            ;

        return tmp;
    }

    /*
     * 字符串赋值，
     * 考虑内存重叠的情况，这种非常危险会破坏源字符串后面的内存
     * 所有字符串拷贝通常用strncpy
    */
    static char* StrOverlapCpy(const char* src, char* dest)
    {
        if (!src || !dest)
            return nullptr;
        char* tmp = dest, *p_ret = nullptr;
        p_ret = StrMemCpy(src, dest);
        if (!p_ret)
        {
            return nullptr;
        }
        return tmp;
    }

    /*
     * 字符串赋值，
     * 复制指定长度字符串
    */
    static char* StrNCpy(const char* src, size_t len, char* dest)
    {
        if (!src || !dest)
            return nullptr;

        size_t s_len = strlen(src);
        size_t off_len = 0;
        if (s_len < len)
        {
            off_len = len - s_len;
            len = s_len;
        }

        char* tmp = nullptr, *res = dest;
        // 内存重叠从高位开始复制
        if (dest > src && dest < src + s_len - 1)
        {
            dest = dest + len - 1;
            src = src + len - 1;
            tmp = dest;
            while (len--) {
                *dest-- = *src--;
            }
        }
        else
        {
            while(len--)
                *dest++ = *src++;
            tmp= dest;
        }

        // src长度小于要复制的长度时，后面以'\0'补充
        while (off_len--) {
            *tmp++ = '\0';
        }
        return res;
    }

    static int StrCmp(const char src[], int s_len, const char dest[], int d_len, int pos = 0)
    {
        if (s_len - pos < d_len)
            return ERR_CMP_FAILED;

        int i = pos, j = 0;
        while (i < s_len && j < d_len) {
            if (src[i] == dest[j])
            {
                ++i;
                ++j;
            }
            else {
                i = i - j + 1;
                j = 0;
            }
        }

        if (j == d_len)
        {
            return i - j;
        }
        else
        {
            return ERR_CMP_FAILED;
        }
    }
    static int StrCmp(const std::string& src, const std::string& dest)
    {
        return KMP::KMPCompare(src, dest);
    }

private:
    static char* StrMemCpy(const char* src, char* dest)
    {
        if (!src || !dest)
            return nullptr;
        char* tmp = dest;
        int s_len = strlen(src) + 1;

        // 内存重叠时从高位置开始复制
        if (dest > src && dest < src + s_len - 1)
        {
            dest = dest + s_len - 1;
            src = src + s_len -1;
            while (s_len--) {
                *dest-- = *src--;
            }
        }
        else
        {
            while (s_len--) {
                *dest++ = *src++;
            }
        }
        return tmp;
    }

};
