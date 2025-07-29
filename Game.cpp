#include"Game.h"

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

void Game::show_Menu()
{
	cout << " ------2048 Game Menu------" << endl;
	cout << "|         1.Start          |" << endl;
	cout << "|         2.Ranking        |" << endl;
	cout << "|         3.Exit           |" << endl;
	cout << " --------------------------" << endl;
	cout << "Enter your selection:" << endl;
}

void Game::exit_Game()
{
	cout << "Welecom to play next time!" << endl;
	system("pause");
	exit(0);
}

void Game::move_up()
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

void Game::move_down()
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

void Game::move_left()
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

void Game::move_right()
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

void Game::move_add(int key)
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
void Game::start_Game()
{
	while (true)
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
		cout << "SCORE: " << this->score << "\nBEST: " << this->best << "\nMOVE COUNT: " << this->count << endl;
		cout << " -------------------" << endl;
		bool arr_full = true;
		for (int i = 0; i < 4; i++)
		{
			cout << "|";
			for (int j = 0; j < 4; j++)
			{
				if (arr[i][j] == 0)
				{
					cout << "    ";
					arr_full = false;
				}
				else if (arr[i][j] < 10)
				{
					cout << arr[i][j] << "   ";
				}
				else if(arr[i][j] < 100)
				{
					cout << arr[i][j] << "  ";
				}
				else if (arr[i][j] < 1000)
				{
					cout << arr[i][j] << " ";
				}
				else
				{
					cout << arr[i][j];
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
                    case 65:
                    case 97:
                        //a
                        move_left();
                        key = false;
                        break;
                    case 68:
                    case 100:
                        //d
                        move_right();
                        key = false;
                        break;
                    case 83:
                    case 115:
                        //s
                        move_down();
                        key = false;
                        break;
                    case 87:
                    case 119:
                        //w
                        move_up();
                        key = false;
                        break;
                    default:
                        break;
                }
			}
		}
	}
}
