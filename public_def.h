#ifndef INC_2048GAME_PUBLIC_DEF_H
#define INC_2048GAME_PUBLIC_DEF_H
#include <iostream>
#include <algorithm>

#include "base_class.h"
using namespace std;

// 简单的XOR加密密钥
extern const string ENCRYPTION_KEY;
extern const string SAVE_FILE_NAME;

extern const string REMOTE_DB_ADDRESS;  // 远程数据库地址
extern const int REMOTE_DB_PORT;       // 远程数据库端口
extern const string REMOTE_DB_USERNAME; // 远程数据库用户名
extern const string REMOTE_DB_PASSWORD; // 远程数据库密码
extern const string DEFAULT_SCHEMA ;// 默认数据库名，根据实际情况修改

typedef struct data_info_2048
{
    int score;
    int best;
    int count;
    int width;
    int height;
    Tile** arr;
    data_info_2048()
    {
        score = 0;
        best = 0;
        count = 0;
        width = 4;
        height = 4;
        arr = new Tile*[height];
        for (int i = 0; i < height; i++)
        {
            arr[i] = new Tile[width];
        }
    }
    ~data_info_2048()
    {
        for (int i = 0; i < height; ++i)
        {
            delete[] arr[i];
        }
        delete[] arr;
    }

    void clear()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                arr[i][j] = 0;
            }
        }
        score = 0;
        best = 0;
        count = 0;
    }
    // 重新调整数组大小
    void resize(int newWidth, int newHeight)
    {
        Tile** newArr = new Tile*[newHeight];
        for (int i = 0; i < newHeight; ++i)
        {
            newArr[i] = new Tile[newWidth];
        }

        int minW = min(width, newWidth);
        int minH = min(height, newHeight);
        for (int i = 0; i < minH; ++i)
        {
            for (int j = 0; j < minW; ++j)
            {
                newArr[i][j] = arr[i][j].getValue();
            }
        }

        for (int i = 0; i < height; ++i)
        {
            delete[] arr[i];
        }
        delete[] arr;

        arr = newArr;
        width = newWidth;
        height = newHeight;
    }
    // 访问元素
    int at(int x, int y) const
    {
        return arr[y][x].getValue();
    }
    void print()
    {
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                cout << arr[i][j].getValue() << " ";
            }
            cout << endl;
        }
    }
    bool isGridFull() const
    {
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                if (arr[i][j].getValue() ==  0)// 发现空格子
                {
                    return false;
                }
            }
        }
        return true;
    }
} DataInfo2048;


enum class MoveDirection
{
    Up,
    Down,
    Left,
    Right
};

#endif // INC_2048GAME_PUBLIC_DEF_H
