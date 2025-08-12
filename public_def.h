#ifndef INC_2048GAME_PUBLIC_DEF_H
#define INC_2048GAME_PUBLIC_DEF_H
#define _HAS_STD_BYTE 0     // 禁用std::byte 在包含任何Windows头文件之前添加：
#include <iostream>
#include <algorithm>
// 以下是 windows 库
//#include <conio.h>

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
    int** arr;
    data_info_2048()
    {
        score = 0;
        best = 0;
        count = 0;
        width = 4;
        height = 4;
        arr = new int*[height];
        for (int i = 0; i < height; i++)
        {
            arr[i] = new int[width];
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
        int** newArr = new int*[newHeight];
        for (int i = 0; i < newHeight; ++i)
        {
            newArr[i] = new int[newWidth];
        }

        int minW = min(width, newWidth);
        int minH = min(height, newHeight);
        for (int i = 0; i < minH; ++i)
        {
            for (int j = 0; j < minW; ++j)
            {
                newArr[i][j] = arr[i][j];
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
    int& at(int x, int y)
    {
        return arr[y][x];
    }
    void print()
    {
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }
} DataInfo2048;

#endif // INC_2048GAME_PUBLIC_DEF_H
