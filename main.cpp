#include<iostream>
using namespace std;
#include"Game.h"

int main()
{
    //srand((unsigned int)time(NULL));
    Game g;
    //先生成两个2，之后每移动一下生成一个2，相同数字进行合并，合并成一个数得到这个数的分。直到所有格子都填满。
    while (true)
    {
        g.showMenu();
        int select;
        cin >> select;
        switch (select)
        {
            case 1:
                g.startGame();
                //system("pause");
                system("cls");
                break;
            case 2:
                cout << "待开发" << endl;
                system("pause");
                system("cls");
                break;
            case 3:
                g.exitGame();
                break;
            default:
                cout << "Incorrect input!" << endl;
                system("pause");
                system("cls");
        }
    }

    system("pause");
    return 0;
}
