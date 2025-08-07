#include"Game.h"
#include "public_func.h"
#include <fstream>
#include <filesystem>
using namespace tool;
Game::Game()
{
    dataInfo.score = 0;
    dataInfo.best = 0;
    for(int i=0;i<4;i++)
    {
        for (int j = 0; j < 4; j++)
        {
            dataInfo.arr[i][j] = 0;
        }
    }
    move = true;
    dataInfo.count = 0;
}

void Game::showMenu()
{
    cout << " ------2048 Game Menu------" << endl;
    cout << "|         1.Start          |" << endl;
    cout << "|         2.Ranking        |" << endl;
    cout << "|         3.Exit           |" << endl;
    cout << " --------------------------" << endl;
    cout << "Enter your selection:" << endl;
}

void Game::exitGame()
{
    cout << "Welecom to play next time!" << endl;
    system("pause");
    exit(0);
}

void Game::moveUp()
{
    for (int i = 0; i < dataInfo.width; i++)
    {
        int index = -1;
        for (int j = 0; dataInfo.height < 4; j++)
        {
            if (dataInfo.arr[j][i] != 0)
            {
                if (index != -1)
                {
                    if (dataInfo.arr[index][i] == dataInfo.arr[j][i])
                    {
                        move = true;
                        dataInfo.arr[index][i] += dataInfo.arr[j][i];
                        dataInfo.score += dataInfo.arr[j][i];
                        dataInfo.best = dataInfo.best < dataInfo.arr[index][i] ? dataInfo.arr[index][i] : dataInfo.best;
                        dataInfo.count ++;
                        dataInfo.arr[j][i] = 0;
                        index = -1;
                    }
                    else
                    {
                        index = j;
                    }
                }
                else
                {
                    index = j;
                }
            }
        }

        int row = 0;
        for (int j = 1; j < dataInfo.height; j++)
        {
            if (dataInfo.arr[row][i] == 0)
            {
                if (dataInfo.arr[j][i] != 0)
                {
                    move = true;
                    dataInfo.arr[row][i] = dataInfo.arr[j][i];
                    dataInfo.arr[j][i] = 0;
                    row++;
                }
            }
            else
            {
                row++;
            }
        }
    }
}

void Game::moveDown()
{
    for (int i = dataInfo.width - 1 ; i >= 0; i--)
    {
        int index = -1;
        for (int j = dataInfo.height - 1; j >= 0; j--)
        {
            if (dataInfo.arr[j][i] != 0)
            {
                if (index != -1)
                {
                    if (dataInfo.arr[index][i] == dataInfo.arr[j][i])
                    {
                        move = true;
                        dataInfo.arr[index][i] += dataInfo.arr[j][i];
                        dataInfo.score += dataInfo.arr[j][i];
                        dataInfo.best = dataInfo.best < dataInfo.arr[index][i] ? dataInfo.arr[index][i] : dataInfo.best;
                        dataInfo.count ++;
                        dataInfo.arr[j][i] = 0;
                        index = -1;
                    }
                    else
                    {
                        index = j;
                    }
                }
                else
                {
                    index = j;
                }
            }
        }

        int row = 3;
        for (int j = 2; j >= 0; j--)
        {
            if (dataInfo.arr[row][i] == 0)
            {
                if (dataInfo.arr[j][i] != 0)
                {
                    move = true;
                    dataInfo.arr[row][i] = dataInfo.arr[j][i];
                    dataInfo.arr[j][i] = 0;
                    row--;
                }
            }
            else
            {
                row--;
            }
        }
    }
}

void Game::moveLeft()
{
    for (int i = 0; i < 4; i++)
    {
        //合并临近相同数字项
        int index = -1;
        for (int j = 0; j < 4; j++)
        {
            if (dataInfo.arr[i][j] != 0)
            {
                if (index != -1)
                {
                    //记录非0数字下标到index，再看下一个数字是否相等，相等就加到index的数字里，并把index初始化。
                    if (dataInfo.arr[i][index] == dataInfo.arr[i][j])
                    {
                        move = true;
                        dataInfo.arr[i][index] += dataInfo.arr[i][j];
                        dataInfo.score += dataInfo.arr[i][j];
                        dataInfo.best = dataInfo.best < dataInfo.arr[i][index] ? dataInfo.arr[i][index] : dataInfo.best;
                        dataInfo.count ++;
                        dataInfo.arr[i][j] = 0;
                        index = -1;
                    }
                        //如果不相等则index修改为新的数字的下标
                    else
                    {
                        index = j;
                    }
                }
                else
                {
                    index = j;
                }
            }
        }
        //移动数字，先记录空位的下标，把后面不为0的数字放到空位上
        int row = 0;
        for (int j = 1; j < 4; j++)
        {
            if (dataInfo.arr[i][row] == 0)
            {
                if (dataInfo.arr[i][j] != 0)
                {
                    move = true;
                    dataInfo.arr[i][row] = dataInfo.arr[i][j];
                    dataInfo.arr[i][j] = 0;
                    row++;
                }
            }
            else
            {
                row++;
            }
        }
    }
}

void Game::moveRight()
{
    for (int i = 3; i >= 0; i--)
    {
        int index = -1;
        for (int j = 3; j >= 0; j--)
        {
            if (dataInfo.arr[i][j] != 0)
            {
                if (index != -1)
                {
                    if (dataInfo.arr[i][index] == dataInfo.arr[i][j])
                    {
                        move = true;
                        dataInfo.arr[i][index] += dataInfo.arr[i][j];
                        dataInfo.score += dataInfo.arr[i][j];
                        dataInfo.best = dataInfo.best < dataInfo.arr[i][index] ? dataInfo.arr[i][index] : dataInfo.best;
                        dataInfo.count ++;
                        dataInfo.arr[i][j] = 0;
                        index = -1;
                    }
                    else
                    {
                        index = j;
                    }
                }
                else
                {
                    index = j;
                }
            }
        }

        int row = 3;
        for (int j = 2; j >= 0; j--)
        {
            if (dataInfo.arr[i][row] == 0)
            {
                if (dataInfo.arr[i][j] != 0)
                {
                    move = true;
                    dataInfo.arr[i][row] = dataInfo.arr[i][j];
                    dataInfo.arr[i][j] = 0;
                    row--;
                }
            }
            else
            {
                row--;
            }
        }
    }
}

void Game::moveAdd(int key)
{
    if(key==1)
    {
        for (int i = 0; i < 4; i++)
        {
            //合并临近相同数字项
            int index = -1;
            for (int j = 0; j < 4; j++)
            {
                if (dataInfo.arr[i][j] != 0)
                {
                    if (index != -1)
                    {
                        //记录非0数字下标到index，再看下一个数字是否相等，相等就加到index的数字里，并把index初始化。
                        if (dataInfo.arr[i][index] == dataInfo.arr[i][j])
                        {
                            move = true;
                            dataInfo.arr[i][index] += dataInfo.arr[i][j];
                            dataInfo.arr[i][j] = 0;
                            index = -1;
                        }
                            //如果不相等则index修改为新的数字的下标
                        else
                        {
                            index = j;
                        }
                    }
                    else
                    {
                        index = j;
                    }
                }
            }
            //移动数字，先记录空位的下标，把后面不为0的数字放到空位上
            int row = 0;
            for (int j = 1; j < 4; j++)
            {
                if (dataInfo.arr[i][row] == 0)
                {
                    if (dataInfo.arr[i][j] != 0)
                    {
                        move = true;
                        dataInfo.arr[i][row] = dataInfo.arr[i][j];
                        dataInfo.arr[i][j] = 0;
                        row++;
                    }
                }
                else
                {
                    row++;
                }
            }
        }
        return;
    }

    if (key == 2)
    {
        for (int i = 3; i >= 0; i--)
        {
            int index = -1;
            for (int j = 3; j >= 0; j--)
            {
                if (dataInfo.arr[i][j] != 0)
                {
                    if (index != -1)
                    {
                        if (dataInfo.arr[i][index] == dataInfo.arr[i][j])
                        {
                            move = true;
                            dataInfo.arr[i][index] += dataInfo.arr[i][j];
                            dataInfo.arr[i][j] = 0;
                            index = -1;
                        }
                        else
                        {
                            index = j;
                        }
                    }
                    else
                    {
                        index = j;
                    }
                }
            }

            int row = 3;
            for (int j = 2; j >= 0; j--)
            {
                if (dataInfo.arr[i][row] == 0)
                {
                    if (dataInfo.arr[i][j] != 0)
                    {
                        move = true;
                        dataInfo.arr[i][row] = dataInfo.arr[i][j];
                        dataInfo.arr[i][j] = 0;
                        row--;
                    }
                }
                else
                {
                    row--;
                }
            }
        }
        return;
    }

    if (key == 3)
    {
        for (int i = 3; i >= 0; i--)
        {
            int index = -1;
            for (int j = 3; j >= 0; j--)
            {
                if (dataInfo.arr[j][i] != 0)
                {
                    if (index != -1)
                    {
                        if (dataInfo.arr[index][i] == dataInfo.arr[j][i])
                        {
                            move = true;
                            dataInfo.arr[index][i] += dataInfo.arr[j][i];
                            dataInfo.arr[j][i] = 0;
                            index = -1;
                        }
                        else
                        {
                            index = j;
                        }
                    }
                    else
                    {
                        index = j;
                    }
                }
            }

            int row = 3;
            for (int j = 2; j >= 0; j--)
            {
                if (dataInfo.arr[row][i] == 0)
                {
                    if (dataInfo.arr[j][i] != 0)
                    {
                        move = true;
                        dataInfo.arr[row][i] = dataInfo.arr[j][i];
                        dataInfo.arr[j][i] = 0;
                        row--;
                    }
                }
                else
                {
                    row--;
                }
            }
        }
        return;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            int index = -1;
            for (int j = 0; j < 4; j++)
            {
                if (dataInfo.arr[j][i] != 0)
                {
                    if (index != -1)
                    {
                        if (dataInfo.arr[index][i] == dataInfo.arr[j][i])
                        {
                            move = true;
                            dataInfo.arr[index][i] += dataInfo.arr[j][i];
                            dataInfo.arr[j][i] = 0;
                            index = -1;
                        }
                        else
                        {
                            index = j;
                        }
                    }
                    else
                    {
                        index = j;
                    }
                }
            }

            int row = 0;
            for (int j = 1; j < 4; j++)
            {
                if (dataInfo.arr[row][i] == 0)
                {
                    if (dataInfo.arr[j][i] != 0)
                    {
                        move = true;
                        dataInfo.arr[row][i] = dataInfo.arr[j][i];
                        dataInfo.arr[j][i] = 0;
                        row++;
                    }
                }
                else
                {
                    row++;
                }
            }
        }
        return;
    }
}

bool nonzero(int val)
{
    return val != 0;
}

bool Game::size()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (j != 3)
            {
                if (i != 3)
                {
                    if (dataInfo.arr[i][j] == dataInfo.arr[i][j + 1] || dataInfo.arr[i][j] == dataInfo.arr[i + 1][j]
                        || dataInfo.arr[i][j] == 0 || dataInfo.arr[i][j + 1] == 0 || dataInfo.arr[i + 1][j] == 0)
                    {
                        return true;
                    }
                }
                else
                {
                    if (dataInfo.arr[i][j] == dataInfo.arr[i][j + 1])
                    {
                        return true;
                    }
                }
            }
            else
            {
                if (dataInfo.arr[i][j] == dataInfo.arr[i + 1][j])
                {
                    return true;
                }
            }
        }
    }
    return false;
}
void Game::startGame()
{
    bool is_start = true;
    while (is_start)
    {
        system("cls");
        if (move)
        {

            while (true)
            {
                int ran_i = rand() % 3;
                int ran_j = rand() % 3;
                if (dataInfo.arr[ran_i][ran_j] == 0)
                {
                    dataInfo.arr[ran_i][ran_j] = 2;
                    move = false;
                    break;
                }
            }
        }

        cout << "2048 Game Menu" << endl;
        cout << "SCORE: " << dataInfo.score << "\nBEST: " << dataInfo.best << "\nMERGE COUNT: " << dataInfo.count << endl;
        cout << "BOOS Key: B" << "\tReturn Home: R" << endl;
        cout << " -------------------" << endl;
        bool arr_full = true;
        for (int i = 0; i < dataInfo.width; i++)
        {
            cout << "|";
            for (int j = 0; j < dataInfo.height; j++)
            {
                if (dataInfo.arr[i][j] == 0)
                {
                    cout << "    ";
                    arr_full = false;
                }
                else if (dataInfo.arr[i][j] < 10)
                {
                    cout << dataInfo.arr[i][j] << "   ";
                }
                else if(dataInfo.arr[i][j] < 100)
                {
                    cout << dataInfo.arr[i][j] << "  ";
                }
                else if (dataInfo.arr[i][j] < 1000)
                {
                    cout << dataInfo.arr[i][j] << " ";
                }
                else
                {
                    cout << dataInfo.arr[i][j];
                }
                cout << "|";
            }
            cout << endl<<" -------------------" << endl;
        }
        if (arr_full)
        {
            cout << "Game Over!" << endl;
            system("pause");
            return;
        }

        int keywork;
        bool key = true;
        while (key)
        {
            if (_kbhit())
            {
                keywork = _getch();
                switch (keywork)
                {
                    case 'B':
                    case 'b':   // 老板键
                    {
                        // 最小化当前窗口
                        HWND hwnd = GetForegroundWindow();
                        ShowWindow(hwnd, SW_MINIMIZE);
                        // 随机激活另一个窗口
                        tool::activateRandomWindow();
                    }
                        break;
                    case 'r':
                    case 'R':   // 返回首页
                        is_start = false;
                        key = false;
                        break;
                    case 'a':
                    case 'A':
                        moveLeft();
                        key = false;
                        break;
                    case 'd':
                    case 'D':
                        moveRight();
                        key = false;
                        break;
                    case 's':
                    case 'S':
                        moveDown();
                        key = false;
                        break;
                    case 'w':
                    case 'W':
                        moveUp();
                        key = false;
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
void Game::saveDate2Local()
{
    std::wstring cachePath = getAppCachePath() + L"\\game_data_2048.dat";
    std::string narrowPath = wstring_to_string(cachePath);

    size_t baseSize = sizeof(dataInfo.score) + sizeof(dataInfo.best) +
                      sizeof(dataInfo.count) + sizeof(dataInfo.width) +
                      sizeof(dataInfo.height);
    size_t arrSize = dataInfo.width * dataInfo.height * sizeof(int);
    size_t totalSize = baseSize + arrSize;

    std::vector<unsigned char> buffer(totalSize);
    unsigned char* ptr = buffer.data();

    memcpy(ptr, &dataInfo.score, sizeof(dataInfo.score));
    ptr += sizeof(dataInfo.score);

    memcpy(ptr, &dataInfo.best, sizeof(dataInfo.best));
    ptr += sizeof(dataInfo.best);

    memcpy(ptr, &dataInfo.count, sizeof(dataInfo.count));
    ptr += sizeof(dataInfo.count);

    memcpy(ptr, &dataInfo.width, sizeof(dataInfo.width));
    ptr += sizeof(dataInfo.width);

    memcpy(ptr, &dataInfo.height, sizeof(dataInfo.height));
    ptr += sizeof(dataInfo.height);

    for (int i = 0; i < dataInfo.height; ++i)
    {
        for (int j = 0; j < dataInfo.width; ++j)
        {
            memcpy(ptr, &dataInfo.arr[i][j], sizeof(int));
            ptr += sizeof(int);
        }
    }

    // 加密数据
    xorEncryptDecrypt(buffer.data(), totalSize);

    std::ofstream file(narrowPath, std::ios::binary);
    if (file)
    {
        file.write(reinterpret_cast<const char*>(buffer.data()), totalSize);
    }
}
void Game::loadLocalDate()
{
    std::wstring cachePath = getAppCachePath() + L"\\game_data_2048.dat";
    std::string narrowPath = wstring_to_string(cachePath);

    std::ifstream file(narrowPath, std::ios::binary | std::ios::ate);
    if (!file) return;

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<unsigned char> buffer(size);
    if (file.read(reinterpret_cast<char*>(buffer.data()), size))
    {
        // 解密数据
        xorEncryptDecrypt(buffer.data(), size);

        const unsigned char* ptr = buffer.data();

        memcpy(&dataInfo.score, ptr, sizeof(dataInfo.score));
        ptr += sizeof(dataInfo.score);
        memcpy(&dataInfo.best, ptr, sizeof(dataInfo.best));

        ptr += sizeof(dataInfo.best);
        memcpy(&dataInfo.count, ptr, sizeof(dataInfo.count));
        ptr += sizeof(dataInfo.count);

        memcpy(&dataInfo.width, ptr, sizeof(dataInfo.width));
        ptr += sizeof(dataInfo.width);

        memcpy(&dataInfo.height, ptr, sizeof(dataInfo.height));
        ptr += sizeof(dataInfo.height);

        if (dataInfo.arr)
        {
            for (int i = 0; i < dataInfo.height; ++i)
            {
                delete[] dataInfo.arr[i];
            }
            delete[] dataInfo.arr;
        }

        dataInfo.arr = new int*[dataInfo.height];
        for (int i = 0; i < dataInfo.height; ++i)
        {
            dataInfo.arr[i] = new int[dataInfo.width];
        }

        for (int i = 0; i < dataInfo.height; ++i)
        {
            for (int j = 0; j < dataInfo.width; ++j)
            {
                memcpy(&dataInfo.arr[i][j], ptr, sizeof(int));
                ptr += sizeof(int);
            }
        }
    }
}
