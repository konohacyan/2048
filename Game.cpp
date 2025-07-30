#include"Game.h"
#include "public_func.h"
Game::Game()
{
	this->score = 0;
	this->best = 0;
	for(int i=0;i<4;i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->arr[i][j] = 0;
		}
	}
	this->move = true;
	this->count = 0;
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
	for (int i = 0; i < 4; i++)
	{
		int index = -1;
		for (int j = 0; j < 4; j++)
		{
			if (this->arr[j][i] != 0)
			{
				if (index != -1)
				{
					if (this->arr[index][i] == this->arr[j][i])
					{
						this->move = true;
						this->arr[index][i] += this->arr[j][i];
                        score += this->arr[j][i];
                        best = best < this->arr[index][i] ? this->arr[index][i] : best;
                        count ++;
						this->arr[j][i] = 0;
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
			if (this->arr[row][i] == 0)
			{
				if (this->arr[j][i] != 0)
				{
					this->move = true;
					arr[row][i] = arr[j][i];
					arr[j][i] = 0;
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
	for (int i = 3; i >= 0; i--)
	{
		int index = -1;
		for (int j = 3; j >= 0; j--)
		{
			if (this->arr[j][i] != 0)
			{
				if (index != -1)
				{
					if (this->arr[index][i] == this->arr[j][i])
					{
						this->move = true;
						this->arr[index][i] += this->arr[j][i];
                        score += this->arr[j][i];
                        best = best < this->arr[index][i] ? this->arr[index][i] : best;
                        count ++;
						this->arr[j][i] = 0;
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
			if (this->arr[row][i] == 0)
			{
				if (this->arr[j][i] != 0)
				{
					this->move = true;
					arr[row][i] = arr[j][i];
					arr[j][i] = 0;
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
			if (this->arr[i][j] != 0)
			{
				if (index != -1)
				{
					//记录非0数字下标到index，再看下一个数字是否相等，相等就加到index的数字里，并把index初始化。
					if (this->arr[i][index] == this->arr[i][j])
					{
						this->move = true;
						this->arr[i][index] += this->arr[i][j];
                        this->score += this->arr[i][j];
                        best = best < this->arr[i][index] ? this->arr[i][index] : best;
                        count ++;
						this->arr[i][j] = 0;
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
			if (this->arr[i][row] == 0)
			{
				if (this->arr[i][j] != 0)
				{
					this->move = true;
					arr[i][row] = arr[i][j];
					arr[i][j] = 0;
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
			if (this->arr[i][j] != 0)
			{
				if (index != -1)
				{
					if (this->arr[i][index] == this->arr[i][j])
					{
						this->move = true;
						this->arr[i][index] += this->arr[i][j];
                        score += this->arr[i][j];
                        best = best < this->arr[i][index] ? this->arr[i][index] : best;
                        count ++;
						this->arr[i][j] = 0;
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
			if (this->arr[i][row] == 0)
			{
				if (this->arr[i][j] != 0)
				{
					this->move = true;
					arr[i][row] = arr[i][j];
					arr[i][j] = 0;
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
				if (this->arr[i][j] != 0)
				{
					if (index != -1)
					{
						//记录非0数字下标到index，再看下一个数字是否相等，相等就加到index的数字里，并把index初始化。
						if (this->arr[i][index] == this->arr[i][j])
						{
							this->move = true;
							this->arr[i][index] += this->arr[i][j];
							this->arr[i][j] = 0;
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
				if (this->arr[i][row] == 0)
				{
					if (this->arr[i][j] != 0)
					{
						this->move = true;
						arr[i][row] = arr[i][j];
						arr[i][j] = 0;
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
				if (this->arr[i][j] != 0)
				{
					if (index != -1)
					{
						if (this->arr[i][index] == this->arr[i][j])
						{
							this->move = true;
							this->arr[i][index] += this->arr[i][j];
							this->arr[i][j] = 0;
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
				if (this->arr[i][row] == 0)
				{
					if (this->arr[i][j] != 0)
					{
						this->move = true;
						arr[i][row] = arr[i][j];
						arr[i][j] = 0;
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
				if (this->arr[j][i] != 0)
				{
					if (index != -1)
					{
						if (this->arr[index][i] == this->arr[j][i])
						{
							this->move = true;
							this->arr[index][i] += this->arr[j][i];
							this->arr[j][i] = 0;
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
				if (this->arr[row][i] == 0)
				{
					if (this->arr[j][i] != 0)
					{
						this->move = true;
						arr[row][i] = arr[j][i];
						arr[j][i] = 0;
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
				if (this->arr[j][i] != 0)
				{
					if (index != -1)
					{
						if (this->arr[index][i] == this->arr[j][i])
						{
							this->move = true;
							this->arr[index][i] += this->arr[j][i];
							this->arr[j][i] = 0;
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
				if (this->arr[row][i] == 0)
				{
					if (this->arr[j][i] != 0)
					{
						this->move = true;
						arr[row][i] = arr[j][i];
						arr[j][i] = 0;
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
					if (arr[i][j] == arr[i][j + 1] || arr[i][j] == arr[i + 1][j] || arr[i][j] == 0 || arr[i][j + 1] == 0 || arr[i + 1][j] == 0)
					{
						return true;
					}
				}
				else
				{
					if (arr[i][j] == arr[i][j + 1])
					{
						return true;
					}
				}
			}
			else
			{
				if (arr[i][j] == arr[i + 1][j])
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
		if (this->move)
		{
			
			while (true)
			{
				int ran_i = rand() % 3;
				int ran_j = rand() % 3;
				if (this->arr[ran_i][ran_j] == 0)
				{
					arr[ran_i][ran_j] = 2;
					this->move = false;
					break;
				}
			}
		}

		cout << "2048 Game Menu" << endl;
		cout << "SCORE: " << this->score << "\nBEST: " << this->best << "\nMERGE COUNT: " << this->count << endl;
        cout << "BOOS Key: B" << "\tReturn Home: R" << endl;
		cout << " -------------------" << endl;
		bool arr_full = true;
		for (auto & i : arr)
		{
			cout << "|";
			for (int j : i)
			{
				if (j == 0)
				{
					cout << "    ";
					arr_full = false;
				}
				else if (j < 10)
				{
					cout << j << "   ";
				}
				else if(j < 100)
				{
					cout << j << "  ";
				}
				else if (j < 1000)
				{
					cout << j << " ";
				}
				else
				{
					cout << j;
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
                        tool::ActivateRandomWindow();
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
