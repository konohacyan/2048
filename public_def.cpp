#include "public_def.h"
const string ENCRYPTION_KEY = "2048GameEncryptionKey";
const string SAVE_FILE_NAME = "game_data_2048.dat";

const string REMOTE_DB_ADDRESS = "mysql.sqlpub.com";
const int REMOTE_DB_PORT = 3306;
const string REMOTE_DB_USERNAME = "xiuxian";
const string REMOTE_DB_PASSWORD = "ef8ead2a1a2704c4";
const string DEFAULT_SCHEMA = "";


data_info_2048::data_info_2048(int w, int h) : score(0), best(0), count(0), width(w), height(h)
{
    resizeGrid(width, height);
}

void data_info_2048::clear()
{
    for (auto& row : grid)
    {
        for (auto& tile : row)
        {
            tile.reset();
        }
    }
    score = 0;
    // best = 0;
    count = 0;
}

int data_info_2048::atValue(int x, int y) const
{
    if (grid[y][x] == nullptr)
    {
        return -1;  // 空格子
    }
    return grid[y][x]->getValue();
}

TilePtr &data_info_2048::atTile(int x, int y)
{
    return grid[y][x];
}

bool data_info_2048::isGridFull() const
{
    for (const auto& row : grid)
    {
        for (const auto& tile : row)
        {
            if (tile == nullptr)
            {
                return false;
            }
        }
    }
    return true;
}

void data_info_2048::resizeGrid(int w, int h)
{
    grid.resize(h);
    for (auto& row : grid)
    {
        row.resize(w);
    }
    width = w;
    height = h;
}
