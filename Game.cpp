#include"Game.h"
#include "public_func.h"
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
