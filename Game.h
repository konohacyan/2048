#pragma once
#include <QSharedPointer>
#include "public_def.h"
#include "base_class.h"
using namespace std;
class Board;
class Game : public Subject
{
    using BoardPtr = QSharedPointer<Board>;
public:
	Game();
    void restart();
    bool isGameOver() const;
    bool isWin() const;
    BoardPtr getBoard() const;
    void move(const MoveDirection& direction);
    int getHeight();
    int getWidth();
private:
    bool is_move;
    BoardPtr board;
    bool gameOver;
    const int winValue = 2048;
};
