#ifndef KMP_H
#define KMP_H
#include <string.h>
#include <iostream>
#include <vector>

using int_vec_t = std::vector<int>;
class KMP
{
public:
    static int KMPCompare(const std::string& src, const std::string& dest)
    {
        const char* src_str = src.c_str();
        int src_len = src.length();
        const char* dest_str = dest.c_str();
        int dest_len = dest.length();

        if (dest_len > src_len)
            return -1;

        int_vec_t next_vec;
        if (!GetNext(dest_str, dest_len, next_vec))
            return -1;

        std::cout << "Next: ";
        for (auto& elem : next_vec)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        int i = 0, j = 0;
        while ((i < src_len) && (j < dest_len)) {
            if (j == -1 || src_str[i] == dest_str[j])
            {
                ++i;
                ++j;
            }
            else
            {
                j = next_vec[j];
            }
        }

        if (j == dest_len)
        {
            return i - j;
        }
        else
            return - 1;
    }

private:
    static bool GetNext(const char* src, int len, int_vec_t& int_vec)
    {
        if (!src || len <= 0)
            return false;

        int k = -1;
        int j = 0;
        int_vec.push_back(-1);

        // NextVec默认第一个值是-1，表示没有相同的首尾串
        while(j < (len - 1))
        {
            if (-1 == k || src[k] == src[j])
            {
                ++j;
                int_vec.push_back(++k);
            }
            else
            {
                k = int_vec[k];
            }
        }
        return true;
    }
};

#endif // KMP_H
