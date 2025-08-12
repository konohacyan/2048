#include<iostream>
#include <limits>
using namespace std;
#include"Game.h"

int main()
{
    //srand((unsigned int)time(NULL));
    Game g;
    while (true)
    {
        g.showMenu();
        int select;
        cin >> select;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Incorrect input!" << endl;
            system("pause");
            system("cls");
            continue;
        }
        switch (select)
        {
            case 1:
                g.startGame();
                //system("pause");
                system("cls");
                break;
            case 2:
                cout << "wait dev" << endl;
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

