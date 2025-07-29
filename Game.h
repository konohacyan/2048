#pragma once
#include<iostream>
using namespace std;
#include <conio.h>
#include<algorithm>

class Game
{
public:
	Game();
	void show_Menu();
	void exit_Game();
	void move_add(int key);
	void start_Game();
	void show_Ranking();
	bool size();

	void move_up();
	void move_down();
	void move_left();
	void move_right();

	int score;
	int best;
	int count;
	int arr[4][4];
	bool move;
};
