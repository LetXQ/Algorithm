#include <iostream>
#include <vector>
#include <map>

#include "algorithm.h"
using namespace std;

void TestGetCartPro()
{
    int_vec_t k1{1, 2,3}, k2{4, 5}, k3{6, 7, 8};
    int_vec_vec_t src_data{k1, k2, k3};

    int_vec_vec_t res_data;
    int_vec_t cur_data;
    int layer = 0;
    AlgorithmFunc::GetCartPro(src_data, res_data, layer, cur_data);

    for (auto& elem : res_data)
    {
        for (auto& int_data : elem)
        {
            std::cout << int_data << " ";
        }
        std::cout << std::endl;
    }
}

void TestCombine()
{
    AlgorithmFunc::OutputCombine(4, 2);
    std::cout << "\n---------------\n";
    AlgorithmFunc::OutputAllCombine(4);
}

int main(void)
{
    //TestGetCartPro();
    TestCombine();
    return 0;
}
