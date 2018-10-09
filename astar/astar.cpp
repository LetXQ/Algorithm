#include <algorithm>
#include <iostream>
#include "astar.h"
#include "grid.h"

namespace  AStarHeuristic
{
 constexpr int IStraightCost = 10;
 constexpr int IDiagonalCost = 14;

  int CalcG(const NodeItem& cur_item, const NodeItem& next_item)
  {
    int extG = (std::abs(cur_item.pos.x - next_item.pos.x) + std::abs(cur_item.pos.y - next_item.pos.y) ) == 1 ? IStraightCost : IDiagonalCost;
    int parentG = next_item.parent ? next_item.parent->g_cost : 0;
    return extG + parentG;
  }

  //用简单的欧几里得距离计算H
 int CalcH(const NodeItem& cur_item, const NodeItem& next_item)
 {
     int dx = cur_item.pos.x - next_item.pos.x;
     int dy = cur_item.pos.y - next_item.pos.y;

     return std::sqrt(dx * dx + dy * dy) * IStraightCost;
 }

}

int NodeItem::FCost() const
{
    return g_cost + h_cost;
}

bool AStar::GetPath(const Point &start_pos, const Point &end_pos, NodeItemPtrList &path, bool isIgnoreCorner)
{
    int ret = FindPath(start_pos, end_pos, path, isIgnoreCorner);

    this->reset();
    return 0 == ret;
}

int AStar::FindPath(const Point &start_pos, const Point &end_pos, NodeItemPtrList &path, bool isIgnoreCorner)
{
    NodeItem* start = GetNodeFromCache();
    if (!start)
    {
        return 1;
    }
    start->Reset();
    start->pos = start_pos;
    start->node_type = T_START;

    NodeItem end_item(end_pos.x, end_pos.y);

    m_pOpenList.push_back(start);
    while (!m_pOpenList.empty())
    {
        auto cur_node = GetMinFNode();
        m_pOpenList.remove(cur_node);
        m_pCloseList.push_back(cur_node);

        auto surround_node = GetSurroundNode(cur_node, isIgnoreCorner);
        for (auto& elem : surround_node)
        {
            if (!IsInList(elem))
            {
                NodeItem* new_node = GetNodeFromCache();
                new_node->Reset();
                new_node->pos = elem.pos;
                new_node->parent = cur_node;
                new_node->g_cost = AStarHeuristic::CalcG(elem, *cur_node);
                new_node->h_cost =  AStarHeuristic::CalcH(elem, end_item);

                m_pOpenList.push_back(new_node);
            }
            else
            {
                int tmpG = AStarHeuristic::CalcG(elem, *cur_node);
                if (tmpG < elem.g_cost)
                {
                    elem.parent = cur_node;
                    elem.g_cost = tmpG;
                }
            }

            auto path_node = IsInList(end_item);
            if (path_node)
            {
                 while (path_node)
                 {
                     path.push_front(path_node);
                     path_node = path_node->parent;
                 }
                 return 0;
            }
        }

    }

    return 0;
}

NodeItem *AStar::GetMinFNode()
{
    if (m_pOpenList.empty())
        return nullptr;

    NodeItem* res_node = m_pOpenList.front();
    for (auto& elem : m_pOpenList)
    {
        if (res_node->FCost() > elem->FCost())
            res_node = elem;
    }
    return res_node;
}

NodeItemList AStar::GetSurroundNode(const NodeItem *cur_item, bool isIgnoreCorner)
{
    NodeItemList surround_nodes;
    for (int x = cur_item->pos.x - 1; x <= cur_item->pos.x + 1; ++x)
    {
        for (int y = cur_item->pos.y - 1; y <= cur_item->pos.y + 1; ++y)
        {
            if (IsCanReach(*cur_item, NodeItem(x, y), isIgnoreCorner))
            {
                surround_nodes.push_back(NodeItem(x, y));
            }
        }
    }
    return surround_nodes;
}

bool AStar::IsCanReach(const NodeItem &start_item, const NodeItem &target_item, bool isIgnoreCorner)
{
    if (Grid::Instance().IsBlock(target_item.pos)
            || (start_item.pos == target_item.pos)
            || IsInList(target_item, false))
    {
        return false;
    }
    else
    {
        if (1 == std::abs(target_item.pos.x - start_item.pos.x) + std::abs(target_item.pos.y - start_item.pos.y))
        {
            return true;
        }
        else
        {
            if (!Grid::Instance().IsBlock(start_item.pos.x, target_item.pos.y)
                    && !Grid::Instance().IsBlock(target_item.pos.x, start_item.pos.y))
                return true;
            else
            {
                return isIgnoreCorner;
            }
        }
    }
}

NodeItem* AStar::IsInList(const NodeItem &item, bool bOpen)
{
    if (bOpen)
    {
        for (auto& elem : m_pOpenList)
        {
            if (item.pos.x == elem->pos.x && item.pos.y == elem->pos.y)
                return elem;
        }
    }
    else
    {
        for (auto& elem : m_pCloseList)
        {
            if (item.pos.x == elem->pos.x && item.pos.y == elem->pos.y)
                return elem;
        }
    }
    return nullptr;
}

void AStar::reset()
{
    for (auto& elem : m_TempNodeCache)
    {
        delete elem;
        elem = nullptr;
    }
    m_iNode = 0;
    m_TempNodeCache.clear();
    m_pCloseList.clear();
    m_pOpenList.clear();
}

NodeItem *AStar::GetNodeFromCache()
{
    if (m_iNode >= NODE_CACHE_SIZE - 1)
    {
        auto new_node = new NodeItem;
        m_TempNodeCache.push_back(new_node);
        return new_node;
    }
    else
    {
        return &m_NodeCache[m_iNode++];
    }
}
