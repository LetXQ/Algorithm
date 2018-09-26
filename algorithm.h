#pragma once
#include <vector>
#include <array>

using int_vec_t = std::vector<int>;
using int_vec_vec_t = std::vector<int_vec_t>;
namespace AlgorithmFunc
{

/*
 * Cartesian Product
 * 求取多组数据的笛卡尔积
 * eg: A{1, 2} B{3, 4}, C{5}
 *  AXBXC = {{1,3,5}, {1,4, 5}, {2,3,5}, {2,4, 5}}
 *
 * @param : src_data 所有数组的集合
 * @param : res_data 返回笛卡尔积结果的集合
 * @param : layer 索引循环层数
 * @param : cur_data 具体一组结果
*/
void GetCartPro(const int_vec_vec_t& src_data, int_vec_vec_t& res_data, int layer, int_vec_t& cur_data)
{
    if (layer < src_data.size() - 1)
    {
        for (int i = 0; i < src_data[layer].size(); ++i)
        {
            int_vec_t tmp{cur_data};
            tmp.push_back(src_data[layer][i]);

            GetCartPro(src_data, res_data, layer + 1, tmp);
        }
    }
    else if (layer == src_data.size() - 1)
    {
        for (int i = 0; i < src_data[layer].size(); ++i)
        {
            cur_data.push_back(src_data[layer][i]);
            res_data.push_back(cur_data);
            cur_data.pop_back();
        }
    }
}

/*
 * 递归求组合
 *
 * @param : data 原始数组
 * @param : startIndex 起始循环索引
 * @param : m 要取个数
 * @param : arr 具体一组组合
 * @param : res_data 所有组合的集合
*/
void RecursionCombine(const int_vec_t &data,
                       int startIndex,
                       int m,
                       int_vec_t& arr,
                       int_vec_vec_t& res_data)
{
    int src_size = data.size();
    if(m == 0)
    {
        std::cout << "(";
         for (size_t i = 0; i < arr.size(); i++)
         {
            std::cout << arr[i] << " ";
         }
         std::cout << ")";
         res_data.push_back(arr);
         return;
    }

    int endIndex = src_size - m;
    for(int i=startIndex; i<= endIndex; i++)
    {
        int_vec_t tmp_vec{arr};
        tmp_vec.push_back(data[i]);
        RecursionCombine(data,  i+1, m-1, tmp_vec, res_data);
    }
}

void RecursionCombine(int* arr, int arr_len, int m, int* out, int out_len)
{
    if(m == 0)
    {
        for (int j = 0; j < arr_len; j++)
            std::cout << out[j] << " ";
        std::cout << std::endl;

        return;
    }

    for (int i = arr_len; i >= m; --i)	//从后往前依次选定一个
    {
        out[m-1] = arr[i-1]; //选定一个后
        RecursionCombine(arr,i-1,m-1,out,out_len); // 从前i-1个里面选取m-1个进行递归
    }
}

/*
 * 输出从n个数中取m个数的组合
 * 所有组合个数应该是Cmn = (n!) / (m!) * ((n-m)!)
 * eg: n = 4, m =  2, 对(0,1,2,3)进行计算，所有组合个数= 6
 * (0,1)(0,2)(0,3)(1,2)(1,3)(2,3)
*/
void  OutputCombine(int n, int m)
{
    int_vec_vec_t res_data;
    int_vec_t src_tmp, tmp_vec;
    for (int i = 0; i < n; ++i)
    {
        src_tmp.push_back(i);
    }

    RecursionCombine(src_tmp, 0, m, tmp_vec, res_data);
    std::cout << "Total Size: " << res_data.size() << std::endl;
}
void OutputAllCombine(int n)
{
    for (int i = n; i > 0; --i)
    {
        std::cout << "i: " << i << std::endl;
        for (int j = i; j > 0; --j)
        {
            OutputCombine(n, j);
        }
    }
}

void OutputAllCombine(int* arr, int nLen, int m)
{
    auto tmp_arr = new int[m];
}

void GetCombine(int cur_size, int_vec_vec_t& in_vec)
{

}

void GetNextCombine(int need_size, int cur_size)
{
//    int_vec_vec_t res_vec;
//    int loop_num = cur_size - need_size;
//    while (loop_num--)
//    {
//        GetCombine(cur_size, res_vec);
//    }
//    std::cout << "Need size: " << need_size << ", CurSize: " << cur_size << std::endl;
//    for (auto& elem : res_vec)
//    {
//        for (auto& int_data: elem)
//        {
//            std::cout << int_data << " ";
//        }
//        std::cout << std::endl;
//    }
}

void GetArrayCombine(int num)
{
    for (int i = num; i > 0; --i)
    {
        for (int j = i; j > 0; --j)
        {
            GetNextCombine(j, i);
        }
    }
}
}
