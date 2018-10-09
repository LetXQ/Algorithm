#include "grid.h"

void Grid::Init(int _row, int _col, const int_vec_vec_t &map)
{
    m_grid_row = _row;
    m_grid_col = _col;
    m_grid = map;
}

bool Grid::IsBlock(const Point &cur_pos) const
{
    if (cur_pos.x >= m_grid_row || cur_pos.x < 0
            || cur_pos.y >= m_grid_col || cur_pos.y < 0
            || (m_grid[cur_pos.x][cur_pos.y] != 0))
    {
        return true;
    }
    return false;
}

bool Grid::IsBlock(int x, int y) const
{
    if (x >= m_grid_row || x < 0
            || y >= m_grid_col || y < 0
            || (m_grid[x][y] != 0))
    {
        return true;
    }
    return false;
}
