#include <iostream>
#include <vector>
#include <map>

#include "algorithm.h"
#include "list/list.h"
#include "list/stack.h"
#include "list/queue.h"
#include "list/character.h"
#include "list/btree.h"
#include "sort_heap.h"

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
        std::cout << "FindDataByPos pos2:  " << tmp_p.Id << std::endl;
    }
    else
    {
        std::cout << "FindDataByPos pos2: not found " << std::endl;
    }

    ret = list.InsertByPos(2, d7);
    std::cout << "InsertByPos Ret: " << ret << std::endl;
    list.PrintElems();
    ret = list.DeleteByPos(2, tmp_p);
    std::cout << "DeleteByPos Ret: " << ret << ", Id: " << tmp_p.Id <<  std::endl;
}

void TestStack()
{
    Stack<int> test;

    int ret = test.Push(10);
    ret = test.Push(11);
    std::cout << "Push Ret: " << ret << ", size: " << test.Size() << std::endl;
    int tmp = -1;
    ret = test.Pop(tmp);
    std::cout << "Pop Ret: " << ret << ", size: " << test.Size() << ", data: " << tmp << std::endl;
}

void TestQueue()
{
    Queue<int> test;
    int ret = 0;
    for (int i = 0; i < 15; ++i)
    {
        ret = test.EnQueue(i);
        if (ret != 0)
            break;
    }
    std::cout << "Enqueue ret: " << ret << ", size: " << test.Size() << std::endl;

    int tmp = -1;
    ret = test.DeQueue(tmp);
    std::cout << "DeQueue ret: " << ret << ", size: " << test.Size()
              << ", data: " << tmp << std::endl;
}

void TestString()
{
    char str1[] = "helloworld";
    char str2[] = "wor";
    char str3[] = "hellowored";
    char str4[20] = {0};
    int ret = MyString::StrCmp(str1, strlen(str1), str2, strlen(str2));
    std::cout << "Ret: " << ret << std::endl;
    ret = MyString::StrCmp(str1, str2);
    std::cout << "Ret: " << ret << std::endl;

    ret = MyString::StrCompare(str1, str3);
    std::cout << "Ret: " << ret << std::endl;

    size_t d_len = sizeof(str4)/sizeof(char);
    if (d_len >= strlen(str1) + 1)
    {
        char* dst = MyString::StrCpy(str1, str4);
        std::cout << "StrCpy : " << dst << std::endl;
    }
    else
    {
        std::cout << "StrCpy dest not enough, need len: " << strlen(str1) + 1 << std::endl;
    }

    char* p_ret = MyString::StrOverlapCpy(str1, str1+2);
    std::cout << "StrOverlapCpy: " << p_ret << std::endl;
    std::cout << "StrOverlapCpy: " << str1 << ", len: " << strlen(str1) << std::endl;

    char str5[] = "123456";
    p_ret = MyString::StrNCpy(str5, 2, str5+2);
    std::cout << "StrNCpy: " << p_ret << "len: " << strlen(str5 + 2) <<std::endl;
}

void TestBtree()
{
    BTree btree;
    BData d1(1, "A"), d2(2, "B"), d3(3, "C"), d4(4, "D"), d5(5, "E");
    std::vector<BData> d_vec{d3,d1,d2,d4, d5};
    bool ret = btree.AddItem(d_vec);
    std::cout <<std::endl <<  (ret ? "True" : "False") << std::endl;
    btree.TraveringTree(0);
    std::cout << std::endl;
    btree.TraveringTree(1);
    std::cout << std::endl;
    btree.TraveringTree(2);
    std::cout << std::endl;
    btree.TraveringTree(3);
    std::cout << std::endl;
    btree.Destroy();

}

void TestHeapSort()
{
	std::vector<int> data{9,4,1, 5,3,2,7,8,6};
	HeapSort::HeapSortUp(data);
	for (auto& elem : data)
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;
	std::vector<int> data1{9,4,1, 5,3,2,7,8,6};
	HeapSort::HeapSortDown(data1);
	for (auto& elem : data1)
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;
}

int main(void)
{
	TestHeapSort();
    //TestBtree();
    //TestString();
    //TestQueue();
    //TestStack();
    //TestList();
    //TestGetCartPro();
    //TestCombine();
    return 0;
}
