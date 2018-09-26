#include <iostream>
#include <vector>
#include <map>

#include "algorithm.h"
#include "list/list.h"
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

void TestList()
{
    List list;
    Data d1(1,"A"),d2(2, "B"), d3(3,"C"),d4(4, "D"), d5(5,"E"),d6(6, "F"), d7(188, "Hello");
    int ret = list.HeadInsert(d1);
    ret =list.HeadInsert(d2);
    ret =list.HeadInsert(d3);
    ret = list.HeadInsert(d4);
    ret = list.HeadInsert(d5);
    ret =list.HeadInsert(d6);
    std::cout << "Ret: " << ret << std::endl;
    list.PrintElems();
    Data tmp_p;
    ret = list.FindDataByPos(2, tmp_p);
    if (0 == ret)
    {
        std::cout << "Find pos2:  " << tmp_p.Id << std::endl;
    }
    else
    {
        std::cout << "Find pos2: not found " << std::endl;
    }

    ret = list.InsertByPos(2, d7);
    std::cout << "Ret: " << ret << std::endl;
    list.PrintElems();
    list.Destroy();
}

int main(void)
{
    TestList();
    //TestGetCartPro();
    //TestCombine();
    return 0;
}
