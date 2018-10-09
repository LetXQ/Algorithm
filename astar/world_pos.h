#ifndef WORLD_POS_H
#define WORLD_POS_H
#include <list>

struct Point
{
    Point(int _x = 0, int _y = 0)
        : x(_x)
        , y(_y)
    {}
    int x = 0;
    int y = 0;
    const Point& operator =(const Point& o)
    {
        if (this != &o)
        {
            x = o.x;
            y = o.y;
        }
        return *this;
    }

    bool operator==(const Point& o) const
    {
        return x == o.x && y == o.y;
    }

    void Reset()
    {
        x = 0;
        y = 0;
    }
};
using PointList = std::list<Point>;
#endif // WORLD_POS_H
