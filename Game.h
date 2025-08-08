#pragma once
#define _HAS_STD_BYTE 0     // 禁用std::byte 在包含任何Windows头文件之前添加：
#include <iostream>
#include <algorithm>
#include "public_def.h"
// 以下是 windows 库
#include <conio.h>
using namespace std;

class Game
{
public:
	Game();
	void showMenu();
	void exitGame();
	void moveAdd(int key);
	void startGame();
	void showRanking();
	bool size();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

    bool checkSaveLocalDate();
    void saveDate2Local();
    void loadLocalDate();
    void saveDate2RemoteDatabase();

private:
//	int score;  // 每局累计分数
//	int best;   // 每局最高合成数字
//	int count;  // 每局合并数字次数
//	int arr[4][4];
	bool move;
    DataInfo2048 dataInfo;
};
