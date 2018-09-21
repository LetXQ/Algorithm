#pragma once
#include <vector>

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
}
