#include<iostream>
using namespace std;
#include"Game.h"

int main()
{
    //srand((unsigned int)time(NULL));
    Game g;
    //����������2��֮��ÿ�ƶ�һ������һ��2����ͬ���ֽ��кϲ����ϲ���һ�����õ�������ķ֡�ֱ�����и��Ӷ�������
    while (true)
    {
        g.showMenu();
        int select;
        cin >> select;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                cout << "������" << endl;
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
