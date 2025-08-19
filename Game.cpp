#include "game.h"
#include "board.h"
Game::Game()
{
    board = BoardPtr::create();
    restart();
}

void Game::restart()
{
    board;
}

bool Game::isGameOver() const
{
    return gameOver;
}

bool Game::isWin() const
{
    for (int i = 0; i < board->getDataHeight(); ++i)
        for (int j = 0; j < board->getDataWidth(); ++j)
            if (board->getValue(i,j) == winValue)
                return true;

    return false;
}

void Game::move(const MoveDirection &direction)
{
    board->move(direction);
    if (!board->movePossible())
        gameOver = true;
    notifyObservers();
}

int Game::getHeight()
{
    return board->getDataHeight();
}

int Game::getWidth()
{
    return board->getDataWidth();
}



Game::BoardPtr Game::getBoard() const
{
    return board;
}
