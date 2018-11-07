#ifndef OBB_RECT_H
#define OBB_RECT_H
#include <cmath>
#include "point.h"

class OBBRect
{
private:
    float m_width = 0.0f;            // 长
    float m_height = 0.0f;          // 高
    Point2D m_center;               // 中心点
    Point2D m_direction;         // 方向
    Point2D m_axis_vec[2];      //  矩形的轴向量（单位向量）
public:
    OBBRect(float _w, float _h, const Point2D& center, const Point2D& direction)
        : m_width(_w)
        , m_height(_h)
        , m_center(center)
        , m_direction(direction)
    {
        InitAxis();
    }

    bool IsRectIntersect(OBBRect& other)
    {
        // 由两个矩形的中心点确定的向量
        Point2D centers_vec = Point2D(other.m_center.x - m_center.x, other.m_center.y - m_center.y);

        for (int i = 0; i < 2; i++)
        {
            if (GetProjectRadius(m_axis_vec[i]) + other.GetProjectRadius(m_axis_vec[i])
                    <= Dot(centers_vec, m_axis_vec[i]))
            {
                return false;
            }

            if (GetProjectRadius(other.m_axis_vec[i]) + other.GetProjectRadius(other.m_axis_vec[i])
                    <= Dot(centers_vec, other.m_axis_vec[i]))
            {
                return false;
            }
        }

        return true;
    }

private:
    /*
     * 初始化x,y轴方向上的单位向量
    */
    void InitAxis()
    {
        m_axis_vec[0] = m_direction.UnitVector();
        m_axis_vec[1] = Point2D(-m_axis_vec[0].y, m_axis_vec[0].x);
    }

    /*
     * 获取a向量在单位向量b上的投影大小
     * （注意b是一个单位向量才能获取正确的投影值）
     * 向量的点乘 a*b = |a||b|cos(theta)，正负号表示投影在b的同方向还是反方向
    */
    float Dot(const Point2D& a, const Point2D& b_unit)
    {
        return std::abs(a.x * b_unit.x + a.y * b_unit.y);
    }

    /*
     * 获取矩形中心点到顶点在在另一个矩形的某一个轴方向(单位向量)上的投影大小
     * 由向量的加法可以知道
     * 矩形中心点到顶点的向量等于矩形两个轴方向的向量相加之和
     * 这里的轴方向向量大小是矩形中心点到两边的距离
    */
    float GetProjectRadius(const Point2D& p_unit)
    {
        float axis_x = Dot(m_axis_vec[0], p_unit);
        float axis_y = Dot(m_axis_vec[1], p_unit);

        return axis_x * m_width / 2 + axis_y * m_height / 2;
    }
};

#endif // OBB_RECT_H
