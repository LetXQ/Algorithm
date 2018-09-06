#ifndef COMMON_FUNCS_H
#define COMMON_FUNCS_H
#include "common_define.h"

namespace CommonFunc {
    void PrintIntVec(const int_vec_t& vec)
    {
        for (auto& elem : vec)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}
#endif // COMMON_FUNCS_H
