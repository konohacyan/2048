#include "Game.h"
#include "public_func.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
// 以下是 windows 库


using namespace tool;

Game::Game()
{
    dataInfo.score = 0;
    dataInfo.best = 0;
    for (int i = 0; i < dataInfo.height; i++)
    {
        for (int j = 0; j < dataInfo.width; j++)
        {
            dataInfo.arr[i][j] = 0;
        }
    }
    move = true;
    dataInfo.count = 0;
}

void Game::showMenu()
{
    std::cout << " ------2048 Game Menu------" << std::endl;
    std::cout << "|         1.Start          |" << std::endl;
    std::cout << "|         2.Ranking        |" << std::endl;
    std::cout << "|         3.Exit           |" << std::endl;
    std::cout << " --------------------------" << std::endl;
    std::cout << "Enter your selection:" << std::endl;
}

void Game::exitGame()
{
    std::cout << "Welecom to play next time!" << std::endl;
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();
    exit(0);
}

void Game::moveUp()
{
    bool bMoveAdd = true;
    for (int i = 0; i < dataInfo.width; i++)
    {
        int index = -1;
        for (int j = 0; j < dataInfo.height; j++)
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
                        dataInfo.best = (((dataInfo.best) > (dataInfo.arr[index][i])) ? (dataInfo.best) : (dataInfo.arr[index][i]));
                        if(bMoveAdd)
                        {
                            dataInfo.count++;
                            bMoveAdd = false;
                        }
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
                    if(bMoveAdd)
                    {
                        dataInfo.count++;
                        bMoveAdd = false;
                    }
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
    bool bMoveAdd = true;
    for (int i = 0; i < dataInfo.width; i++)
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
                        dataInfo.best = (((dataInfo.best) > (dataInfo.arr[index][i])) ? (dataInfo.best) : (dataInfo.arr[index][i]));
                        if(bMoveAdd)
                        {
                            dataInfo.count++;
                            bMoveAdd = false;
                        }
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

        int row = dataInfo.height - 1;
        for (int j = dataInfo.height - 2; j >= 0; j--)
        {
            if (dataInfo.arr[row][i] == 0)
            {
                if (dataInfo.arr[j][i] != 0)
                {
                    if(bMoveAdd)
                    {
                        dataInfo.count++;
                        bMoveAdd = false;
                    }
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
    bool bMoveAdd = true;
    for (int i = 0; i < dataInfo.height; i++)
    {
        int index = -1;
        for (int j = 0; j < dataInfo.width; j++)
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
                        dataInfo.best = (((dataInfo.best) > (dataInfo.arr[i][index])) ? (dataInfo.best) : (dataInfo.arr[i][index]));
                        if(bMoveAdd)
                        {
                            dataInfo.count++;
                            bMoveAdd = false;
                        }
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
        int row = 0;
        for (int j = 1; j < dataInfo.width; j++)
        {
            if (dataInfo.arr[i][row] == 0)
            {
                if (dataInfo.arr[i][j] != 0)
                {
                    if(bMoveAdd)
                    {
                        dataInfo.count++;
                        bMoveAdd = false;
                    }
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
    bool bMoveAdd = true;
    for (int i = 0; i < dataInfo.height; i++)
    {
        int index = -1;
        for (int j = dataInfo.width - 1; j >= 0; j--)
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
                        dataInfo.best = (((dataInfo.best) > (dataInfo.arr[i][index])) ? (dataInfo.best) : (dataInfo.arr[i][index]));
                        if(bMoveAdd)
                        {
                            dataInfo.count++;
                            bMoveAdd = false;
                        }
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
        int row = dataInfo.width - 1;
        for (int j = dataInfo.width - 2; j >= 0; j--)
        {
            if (dataInfo.arr[i][row] == 0)
            {
                if (dataInfo.arr[i][j] != 0)
                {
                    if(bMoveAdd)
                    {
                        dataInfo.count++;
                        bMoveAdd = false;
                    }
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
    if (key == 1)
    {
        moveLeft();
        return;
    }
    if (key == 2)
    {
        moveRight();
        return;
    }
    if (key == 3)
    {
        moveDown();
        return;
    }
    moveUp();
}

bool nonzero(int val)
{
    return val != 0;
}

bool Game::size()
{
    for (int i = 0; i < dataInfo.height; i++)
    {
        for (int j = 0; j < dataInfo.width; j++)
        {
            if (j != dataInfo.width - 1)
            {
                if (i != dataInfo.height - 1)
                {
                    if (dataInfo.arr[i][j] == dataInfo.arr[i][j + 1] || dataInfo.arr[i][j] == dataInfo.arr[i + 1][j] || dataInfo.arr[i][j] == 0 || dataInfo.arr[i][j + 1] == 0 || dataInfo.arr[i + 1][j] == 0)
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
                if (i != dataInfo.height - 1 && dataInfo.arr[i][j] == dataInfo.arr[i + 1][j])
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
    std::random_device rd;
    std::mt19937 gen(rd());
    while (is_start)
    {
        // 清屏（跨平台）
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        if (move)
        {
            // 随机生成一个空格位置
            std::vector<std::pair<int, int>> emptyCells;
            for (int i = 0; i < dataInfo.height; ++i)
            {
                for (int j = 0; j < dataInfo.width; ++j)
                {
                    if (dataInfo.arr[i][j] == 0)
                        emptyCells.emplace_back(i, j);
                }
            }
            if (!emptyCells.empty())
            {
                std::uniform_int_distribution<> dis(0, static_cast<int>(emptyCells.size()) - 1);
                auto [ran_i, ran_j] = emptyCells[dis(gen)];
                dataInfo.arr[ran_i][ran_j] = 2;
                move = false;
            }
        }

        cout << "2048 Game Menu" << endl;
        cout << "SCORE: " << dataInfo.score << "\nBEST: " << dataInfo.best << "\nMERGE COUNT: " << dataInfo.count << endl;
        cout << "BOOS Key: B" << "\tReturn Home: R" << endl;
        cout << " -------------------" << endl;
        bool arr_full = true;
        for (int i = 0; i < dataInfo.height; i++)
        {
            std::cout << "|";
            for (int j = 0; j < dataInfo.width; j++)
            {
                if (dataInfo.arr[i][j] == 0)
                {
                    std::cout << "    ";
                    arr_full = false;
                }
                else if (dataInfo.arr[i][j] < 10)
                {
                    std::cout << dataInfo.arr[i][j] << "   ";
                }
                else if (dataInfo.arr[i][j] < 100)
                {
                    std::cout << dataInfo.arr[i][j] << "  ";
                }
                else if (dataInfo.arr[i][j] < 1000)
                {
                    std::cout << dataInfo.arr[i][j] << " ";
                }
                else
                {
                    std::cout << dataInfo.arr[i][j];
                }
                if(arr_full)
                {
                    if(i >0 && dataInfo.arr[i][j] == dataInfo.arr[i-1][j] || 
                        (j > 0 && dataInfo.arr[i][j] == dataInfo.arr[i][j-1]) || 
                        (i < dataInfo.height - 1 && dataInfo.arr[i][j] == dataInfo.arr[i+1][j]) ||
                        (j < dataInfo.width - 1 && dataInfo.arr[i][j] == dataInfo.arr[i][j+1]))
                    {
                        arr_full = false;
                    }
                }
                std::cout << "|";
            }
            std::cout << std::endl
                      << " -------------------" << std::endl;
        }
        if (arr_full)
        {
            dataInfo.clear();
            move = true;
            std::cout << "Game Over!" << std::endl;
            std::cout << "Press Enter to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();
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
                    case 'c':
                    case 'C':
//                        saveDate2Local();
                        break;
                    case 'B':
                    case 'b':// 老板键
                    {
                        HWND hwnd = GetForegroundWindow();
                        ShowWindow(hwnd, SW_MINIMIZE);
                        tool::activateRandomWindow();
                    }
                    break;
                    case 'r':
                    case 'R':
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
                        std::cout << "Invalid input, try again." << std::endl;
                        break;
                }
            }
        }
    }
}

void Game::saveDate2Local()
{
    try
    {
        // 获取并检查缓存路径
        std::string cacheDir = getAppCachePath();
        if (cacheDir.empty())
        {
            cerr << "Error: Unable to obtain the application cache directory path" << endl;
            return;
        }

        std::filesystem::path cachePath = std::filesystem::path(cacheDir) / SAVE_FILE_NAME;
        std::cout << "save path: " << cachePath << std::endl;

        std::filesystem::path parentPath = cachePath.parent_path();
        if (!std::filesystem::exists(parentPath))
        {
            std::cout << "Directory does not exist, creating: " << parentPath << std::endl;
            std::error_code ec;
            if (!std::filesystem::create_directories(parentPath, ec))
            {
                std::cerr << "Error: Failed to create directory " << parentPath
                          << "\nError code: " << ec.value()
                          << "\nError message: " << ec.message() << std::endl;
                return;
            }
            std::cout << "Directory created successfully" << std::endl;
        }

        size_t baseSize = sizeof(dataInfo.score) + sizeof(dataInfo.best) +
                          sizeof(dataInfo.count) + sizeof(dataInfo.width) +
                          sizeof(dataInfo.height);
        size_t arrSize = dataInfo.width * dataInfo.height * sizeof(int);
        size_t totalSize = baseSize + arrSize;

        std::cout << "数据大小 - 基础: " << baseSize
                  << ", 数组: " << arrSize
                  << ", 总计: " << totalSize << std::endl;

        if (dataInfo.width <= 0 || dataInfo.height <= 0)
        {
            std::cerr << "错误：无效的数组宽度 width=" << dataInfo.width
                      << ", height=" << dataInfo.height << std::endl;
            return;
        }

        std::vector<uint8_t> buffer(totalSize);
        uint8_t *ptr = buffer.data();

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
        std::cout << "数据加密完成" << std::endl;

        // 写入文件
        std::ofstream file(cachePath, std::ios::binary);
        if (!file)
        {
            std::error_code ec;
            ec.assign(errno, std::system_category());
            std::cerr << "错误：无法打开文件 " << cachePath
                      << "\n错误代码: " << ec.value()
                      << "\n错误信息: " << ec.message() << std::endl;
            return;
        }

        file.write(reinterpret_cast<const char *>(buffer.data()), totalSize);

        if (!file)
        {
            std::error_code ec;
            ec.assign(errno, std::system_category());
            std::cerr << "Error: Writing to file failed"
                      << "\n错误代码: " << ec.value()
                      << "\n错误信息: " << ec.message() << std::endl;
            return;
        }

        std::cout << "成功保存 " << totalSize << " 字节数据到 " << cachePath << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "异常: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "未知异常" << std::endl;
    }
}

void Game::loadLocalDate()
{
    std::filesystem::path cachePath = getAppCachePath() + "/" + SAVE_FILE_NAME;

    std::ifstream file(cachePath, std::ios::binary | std::ios::ate);
    if (!file) return;

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);
    if (file.read(reinterpret_cast<char *>(buffer.data()), size))
    {
        // 解密数据
        xorEncryptDecrypt(buffer.data(), size);

        const uint8_t *ptr = buffer.data();

        // 读取基本数据
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

        // 分配数组内存
        if (dataInfo.arr)
        {
            for (int i = 0; i < dataInfo.height; ++i)
            {
                delete[] dataInfo.arr[i];
            }
            delete[] dataInfo.arr;
        }

        dataInfo.arr = new int *[dataInfo.height];
        for (int i = 0; i < dataInfo.height; ++i)
        {
            dataInfo.arr[i] = new int[dataInfo.width];
        }

        // 读取数组数据
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

bool Game::checkSaveLocalDate()
{
    std::string cachePath = getAppCachePath() + SAVE_FILE_NAME;
    std::ifstream file(cachePath, std::ios::binary);
    return file.good();
}
