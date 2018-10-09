#pragma once
#include <list>
#include "world_pos.h"
#include "singleton.h"
enum NodeType
{
    T_START = 1,
    T_END = 2,
};

struct NodeItem
{
    NodeItem() {}
    NodeItem(int x, int y)
        : pos(Point(x, y)){}
    NodeItem(int type, Point _cur_pos)
        : node_type(type)
        , pos(_cur_pos)
    {}

    void Reset()
    {
        node_type = 0;
        g_cost = 0;
        h_cost = 0;
        pos.Reset();
        parent = nullptr;
    }

    int FCost() const;
    int node_type = 0;
    int g_cost = 0; // 表示从起点 A 移动到网格上指定方格的移动耗费 (可沿斜方向移动).
    int h_cost = 0; // 表示从指定的方格移动到终点 B 的预计耗费 (H 有很多计算方法, 本文代码使用简单的欧几里得距离计算方法)
    Point pos;
    NodeItem* parent = nullptr;
};
using NodeItemPtrList = std::list<NodeItem*>;
using NodeItemList = std::list<NodeItem>;
constexpr int NODE_CACHE_SIZE = 100;

class AStar : public Singleton<AStar>
{
public:
    bool GetPath(const Point& start_pos, const Point& end_pos, NodeItemPtrList& path, bool isIgnoreCorner);

private:
    int FindPath(const Point &start_pos, const Point &end_pos, NodeItemPtrList& path, bool isIgnoreCorner);
    NodeItem* GetMinFNode();
    NodeItemList GetSurroundNode(const NodeItem* cur_item, bool isIgnoreCorner);
    bool IsCanReach(const NodeItem& start_item, const NodeItem& target_item, bool isIgnoreCorner);
    NodeItem* IsInList(const NodeItem& item, bool bOpen = true);
    NodeItem* GetNodeFromCache();
    void reset();
private:
    int m_iNode = 0;
    NodeItem m_NodeCache[NODE_CACHE_SIZE];
    NodeItemPtrList m_TempNodeCache;
    NodeItemPtrList m_pOpenList;
    NodeItemPtrList m_pCloseList;
};
