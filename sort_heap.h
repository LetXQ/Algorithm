#ifndef HEAP_SORT_H_
#define HEAR_SORT_H_
#include <vector>
#include "common_define.h"
#include "common_template.h"

class HeapSort
{
public:
    /*
     * 不减的堆排序
     * 1，先构建一个大顶堆（父节点的元素大于子节点）
     * 2，构建完大顶堆后，根节点的元素肯定是数组里最大的元素
     *  此时，将根节点元素和最末尾元素交换，重新调整n-1个元素的数组为大顶堆
     * 最后一个元素已经在正确位置，不用再调整了，循环交换及调整直到成为有序数组
    */
    static void HeapSortUp(int_vec_t& data_vec)
    {
        InitMaxHeap(data_vec);

        // 只需要调整n-1次，最后一次不需要交换
        for (int i = int(data_vec.size()) - 1; i >= 1; --i)
        {
            CommonSwap<int>(data_vec[0], data_vec[i]);
            MaxHeapAdjust(data_vec, 0, i);
        }
    }

private:
    /*
     * 初始化一个大顶堆
     * 1，将数组视为完全二叉树，按层序遍历排布进行编号(从0开始)
     * 2，最后一个非叶子节点 的索引为 len/2 -1
     * 3，从最后一个非叶子节点开始调整该子树
    */
    static void InitMaxHeap(int_vec_t& data_vec)
    {
        int len = (int)data_vec.size();
        for (int i = len / 2 - 1; i >= 0; --i)
        {
            MaxHeapAdjust(data_vec, i, len);
        }
    }

    static void MaxHeapAdjust(int_vec_t& data_vec, int index, int len)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int maxIdx = index;

        if (left < len && data_vec[left] > data_vec[maxIdx])
        {
            maxIdx = left;
        }
        if (right < len && data_vec[right] > data_vec[maxIdx])
        {
            maxIdx = right;
        }
        if (maxIdx != index)
        {
            CommonSwap<int>(data_vec[maxIdx], data_vec[index]);
            // 递归调整其他不满足堆性质的部分
            MaxHeapAdjust(data_vec, maxIdx, len);
        }
    }
};

#endif // HEAR_SORT_H_
