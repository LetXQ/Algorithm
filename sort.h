#ifndef SORT_H
#define SORT_H
#include "common_funcs.h"
#include "common_template.h"

class Sort
{
public:
    // 每一步将一个待排序的记录，插入到前面已经排好序的有序序列中去，直到插完所有元素为止。
    static void InsertSort(int_vec_t& data_vec)
    {
        int size = (int)data_vec.size();
        if (size <= 1)
            return;
        for (int i = 1; i < size; ++i)
        {
            int tmp = data_vec[i];
            int j = i - 1;
            // 给当前位置的元素在前面序列中找到一个合适的位置
            // 结束条件是往前遍历比较到第0个或者遍历到的元素小于当前要比较的元素
            for (; j >= 0 && data_vec[j] > tmp; --j)
            {
                data_vec[j+1] = data_vec[j];
            }
            data_vec[j+1] = tmp;
            std::cout << i << ": ";
            CommonFunc::PrintIntVec(data_vec);
        }
    }

    // 对相邻的元素进行两两比较，顺序相反则进行交换，
    // 这样，每一趟会将最小或最大的元素“浮”到顶端，最终达到完全有序
    static void BubbleSort(int_vec_t& data_vec)
    {
        int size = (int)data_vec.size();
        if (size <= 1)
            return;
        for (int i = 0; i < size - 1; ++i)
        {
            // 设定一个标记位，因为每趟排序完，后面的数据一定是有序且比前面的数据都大
            // 所以如果一趟排序没有元素交换，可以认为该组数据已经有序了
            bool flag = false;
            for (int j = 0; j < size - 1 - i; ++j)
            {
                if (data_vec[j] > data_vec[j + 1])
                {
                    flag = true;
                    CommonSwap<int>(data_vec[j], data_vec[j + 1]);
                }
            }
            if (!flag)
                break;
            std::cout << i << ": ";
            CommonFunc::PrintIntVec(data_vec);
        }
    }

    // 每一趟从待排序的数据元素中选择最小（或最大）的一个元素作为首元素，直到所有元素排完为止
    // 跟冒泡排序的区别是，每一趟比较完只进行一次元素交换位置，冒泡排序一趟排序会进行多次元素的交换
    static void SelectSort(int_vec_t& data_vec)
    {
        int size = (int)data_vec.size();
        if (size <= 1)
            return;

        for (int i = 0; i < size; ++i)
        {
            int k = i;
            for (int j = i + 1; j < size; ++j)
            {
                if (data_vec[k] > data_vec[j])
                    k = j;
            }

            if (k != i)
                CommonSwap<int>(data_vec[k], data_vec[i]);

            std::cout << i << ": ";
            CommonFunc::PrintIntVec(data_vec);
        }
    }
    // 优化: 每趟比较将最大和最小数找出放到数列首位
    static void SelectSort2(int_vec_t& data_vec)
    {
        int size = (int)data_vec.size();
        if (size <= 1)
            return;

        for (int left = 0, right = size - 1; left < right; ++left, --right)
        {
            int min = left, max = right;
            for (int i = left; i <= right; ++i)
            {
                if (data_vec[i] < data_vec[min])
                    min = i;
                if (data_vec[i] > data_vec[max])
                    max = i;
            }
            if (min != left)
                CommonSwap<int>(data_vec[min], data_vec[left]);
            // 上一行逻辑更改了left位置的值，所以这里要对max重新赋值
            if (max == left)
            {
                max = min;
            }
            if (max != right)
                CommonSwap<int>(data_vec[max], data_vec[right]);
            std::cout << left << ": ";
            CommonFunc::PrintIntVec(data_vec);
        }
    }

    // 每次排序的时候设置一个基准点，将小于等于基准点的数全部放到基准点的左边，
    // 将大于等于基准点的数全部放到基准点的右边
    static void QuickSort(int_vec_t& data_vec)
    {
        int size = (int)data_vec.size();
        if (size <= 1)
            return;
        QuickSort(0, size-1, data_vec);
    }

    // shell排序，缩小增量排序，最后是直接插入排序
    static void ShellSort(int_vec_t& data_vec)
    {
        int size = (int)data_vec.size();
        if (size <= 1)
            return;

        //  gap是选取的增量
        for (int gap = size/ 2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < size; ++i)
            {
                for (int j = i - gap; j >= 0 && data_vec[j] > data_vec[j+gap]; j -= gap)
                {
                    CommonSwap<int>(data_vec[j], data_vec[j+gap]);
                }
            }
        }
    }

private:
    static void QuickSort(int left, int right, int_vec_t& data_vec)
    {
        if (left > right)
            return;
        int i = left, j = right;
        int tmp = data_vec[left];

        while (i != j) {
            // 从右往左找到第一个比基准值小的数，交换位置
            while (i < j && data_vec[j] >= tmp) {
                --j;
            }
            CommonSwap<int>(data_vec[i], data_vec[j]);

            // 从左往右找到第一个比基准值大的数，交换位置
            while (i < j && data_vec[i] <= tmp) {
               ++i;
            }
            CommonSwap<int>(data_vec[j], data_vec[i]);
        }
        data_vec[i] = tmp;
        QuickSort(left, i-1, data_vec);
        QuickSort(i+1, right,data_vec);
    }
};

#endif // SORT_H
