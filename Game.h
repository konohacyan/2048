#pragma once
#include<iostream>
#include <conio.h>
#include<algorithm>
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

    void saveDate2Local();
    void loadLocalDate();
    void saveDate2RemoteDatabase();

private:
	int score;  // 每局累计分数
	int best;   // 每局最高合成数字
	int count;  // 每局合并数字次数
	int arr[4][4];
	bool move;
};
