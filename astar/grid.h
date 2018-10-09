#pragma once
#include <vector>
#include "singleton.h"
#include "world_pos.h"
using int_vec_t = std::vector<int>;
using int_vec_vec_t = std::vector<int_vec_t>;
class Grid : public Singleton<Grid>
{
public:
    void Init(int _row, int _col, const int_vec_vec_t& map);
    bool IsBlock(const Point& cur_pos) const;
    bool IsBlock(int x, int y) const;
private:
    int m_grid_row = 0;
    int m_grid_col = 0;
    int_vec_vec_t m_grid;
};
