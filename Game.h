#pragma once
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
    int** getBoard();
	void showMenu();
	void exitGame();
	void moveAdd(int key);
	void startGame();
	void showRanking();
	bool size();

    void move(MoveDirection direction);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

    bool checkSaveLocalDate();
    void saveDate2Local();
    void loadLocalDate();
    void saveDate2RemoteDatabase();

private:
    bool is_move;
    DataInfo2048 dataInfo;
};
