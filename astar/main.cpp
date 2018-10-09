#include <iostream>
#include <vector>

#include "astar.h"
#include "grid.h"

using namespace std; 
int main()
{	
    //初始化地图，用二维矩阵代表地图，1表示障碍物，0表示可通
    vector<vector<int>> maze={
        {1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,1,1,0,1,0,0,0,0,1},
        {1,0,0,1,1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,1,0,0,1,1,1},
        {1,1,1,0,0,0,0,0,1,1,0,1},
        {1,1,0,1,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,1,0,0,0,1},
        {1,0,1,0,0,0,0,1,0,0,0,1},
        {1,0,1,0,0,0,0,1,0,0,0,1},
        {1,0,1,0,0,0,0,1,0,0,0,1},
        {1,0,1,0,0,0,0,1,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1}
    };
    Grid::Instance().Init(12,12, maze);

    //设置起始和结束点
    Point start(1,1);
    Point end(10,10);
    //A*算法找寻路径
    NodeItemPtrList path;
    bool ret =AStar::Instance().GetPath(start,end, path, false);
    std::cout << "Ret: " << (ret ? "True" : "False") << ", size: " << path.size() << std::endl;
    //打印
    for(auto &p:path)
        cout<<'('<<p->pos.x<<','<<p->pos.y<<')'<<endl;

    return 0;
}
