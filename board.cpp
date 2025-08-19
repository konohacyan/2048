#include "board.h"

Board::Board()
{
    dataInfo.clear();
}

Board::Board(const Board &other)
{
    dataInfo = other.dataInfo;
}

Board::~Board()
{

}

void Board::move(const MoveDirection &direction)
{
    Board pre_move_board(*this);
    switch (direction)
    {
        case MoveDirection::Up: moveUp(); break;
        case MoveDirection::Down: moveDown(); break;
        case MoveDirection::Left: moveLeft(); break;
        case MoveDirection::Right: moveRight(); break;
        default:
            break;
    }
    if (changed(pre_move_board) /*&& !tileCollisionLastRound*/) {
        QPoint newpos = freePosition();
        dataInfo.atTile(newpos.x(), newpos.y()) = TilePtr::create();
    }

    notifyObservers();
}

int Board::getValue(const int &x, const int &y)
{
    return dataInfo.atValue(x,y);
}

Board::TilePtr Board::getTile(const int &x, const int &y)
{
    return dataInfo.atTile(x,y);
}

int Board::getDataHeight()
{
    return dataInfo.height;
}

int Board::getDataWidth()
{
    return dataInfo.width;
}

bool Board::movePossible() const
{
    if (dataInfo.isGridFull())
    {
        Board newBoard(*this);
        newBoard.move(MoveDirection::Up);
        if (changed(newBoard)) return true;
        newBoard.move(MoveDirection::Down);
        if (changed(newBoard)) return true;
        newBoard.move(MoveDirection::Left);
        if (changed(newBoard)) return true;
        newBoard.move(MoveDirection::Right);
        if (changed(newBoard)) return true;

        return false;
    }
    else
    {
        return true;
    }
}

void Board::clear()
{
    dataInfo.clear();
}

int Board::getScore()
{
    return dataInfo.score;
}

int Board::getBest()
{
    return dataInfo.best;
}

int Board::getCount()
{
    return dataInfo.count;
}

void Board::reset()
{
    dataInfo.clear();

    QPoint point = freePosition();
    dataInfo.atTile(point.x(), point.y()) = TilePtr::create();
    point = freePosition();
    dataInfo.atTile(point.x(), point.y()) = TilePtr::create();
}

void Board::moveUp()
{
    bool bMoveAdd = true;
    for (int i = 0; i < dataInfo.width; i++)
    {
        int index = -1;
        for (int j = 0; j < dataInfo.height; j++)
        {
            if (dataInfo.grid[j][i] != nullptr)
            {
                if (index != -1)
                {
                    if (dataInfo.grid[index][i] == dataInfo.grid[j][i])
                    {
                        // is_move = true;
                        dataInfo.grid[index][i]->getValue() += dataInfo.grid[j][i]->getValue();
                        dataInfo.score += dataInfo.grid[j][i]->getValue();
                        dataInfo.best = (((dataInfo.best) > (dataInfo.grid[index][i])->getValue()) ? (dataInfo.best) : (dataInfo.grid[index][i]->getValue()));
                        if(bMoveAdd)
                        {
                            dataInfo.count++;
                            bMoveAdd = false;
                        }
                        dataInfo.grid[j][i].reset();
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
            if (dataInfo.grid[row][i]->getValue() == 0)
            {
                if (dataInfo.grid[j][i]->getValue() != 0)
                {
                    if(bMoveAdd)
                    {
                        dataInfo.count++;
                        bMoveAdd = false;
                    }
                    // is_move = true;
                    dataInfo.grid[row][i]->getValue()= dataInfo.grid[j][i]->getValue();
                    dataInfo.grid[j][i].reset();
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

void Board::moveDown()
{
    bool bMoveAdd = true;
    for (int i = 0; i < dataInfo.width; i++)
    {
        int index = -1;
        for (int j = dataInfo.height - 1; j >= 0; j--)
        {
            if (dataInfo.grid[j][i] != nullptr)
            {
                if (index != -1)
                {
                    if (dataInfo.grid[index][i] == dataInfo.grid[j][i])
                    {
                        // is_move = true;
                        dataInfo.grid[index][i]->getValue() += dataInfo.grid[j][i]->getValue();
                        dataInfo.score += dataInfo.grid[j][i]->getValue();
                        dataInfo.best = (((dataInfo.best) > (dataInfo.grid[index][i])->getValue()) ? (dataInfo.best) : (dataInfo.grid[index][i])->getValue());
                        if(bMoveAdd)
                        {
                            dataInfo.count++;
                            bMoveAdd = false;
                        }
                        dataInfo.grid[j][i].reset();
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
        int row = dataInfo.height - 1;
        for (int j = dataInfo.height - 2; j >= 0; j--)
        {
            if (dataInfo.grid[row][i] == nullptr)
            {
                if (dataInfo.grid[j][i] != nullptr)
                {
                    if(bMoveAdd)
                    {
                        dataInfo.count++;
                        bMoveAdd = false;
                    }
                    // is_move = true;
                    dataInfo.grid[row][i]->getValue() = dataInfo.grid[j][i]->getValue();
                    dataInfo.grid[j][i].reset();
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

void Board::moveLeft()
{
    bool bMoveAdd = true;
    for (int i = 0; i < dataInfo.height; i++)
    {
        int index = -1;
        for (int j = 0; j < dataInfo.width; j++)
        {
            if (dataInfo.grid[i][j] != nullptr)
            {
                if (index != -1)
                {
                    if (dataInfo.grid[i][index] == dataInfo.grid[i][j])
                    {
                        // is_move = true;
                        dataInfo.grid[i][index]->getValue() += dataInfo.grid[i][j]->getValue();
                        dataInfo.score += dataInfo.grid[i][j]->getValue();
                        dataInfo.best = (((dataInfo.best) > (dataInfo.grid[i][index])->getValue()) ? (dataInfo.best) : (dataInfo.grid[i][index])->getValue());
                        if(bMoveAdd)
                        {
                            dataInfo.count++;
                            bMoveAdd = false;
                        }
                        dataInfo.grid[i][j].reset();
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
        for (int j = 1; j < dataInfo.width; j++)
        {
            if (dataInfo.grid[i][row] == nullptr)
            {
                if (dataInfo.grid[i][j] != nullptr)
                {
                    if(bMoveAdd)
                    {
                        dataInfo.count++;
                        bMoveAdd = false;
                    }
                    // is_move = true;
                    dataInfo.grid[i][row]->getValue() = dataInfo.grid[i][j]->getValue();
                    dataInfo.grid[i][j].reset();
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

void Board::moveRight()
{
    bool bMoveAdd = true;
    for (int i = 0; i < dataInfo.height; i++)
    {
        int index = -1;
        for (int j = dataInfo.width - 1; j >= 0; j--)
        {
            if (dataInfo.grid[i][j] != nullptr)
            {
                if (index != -1)
                {
                    if (dataInfo.grid[i][index] == dataInfo.grid[i][j])
                    {
                        // is_move = true;
                        dataInfo.grid[i][index]->getValue() += dataInfo.grid[i][j]->getValue();
                        dataInfo.score += dataInfo.grid[i][j]->getValue();
                        dataInfo.best = (((dataInfo.best) > (dataInfo.grid[i][index]->getValue())) ? (dataInfo.best) : (dataInfo.grid[i][index]->getValue()));
                        if(bMoveAdd)
                        {
                            dataInfo.count++;
                            bMoveAdd = false;
                        }
                        dataInfo.grid[i][j].reset();
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
        int row = dataInfo.width - 1;
        for (int j = dataInfo.width - 2; j >= 0; j--)
        {
            if (dataInfo.grid[i][row] == nullptr)
            {
                if (dataInfo.grid[i][j] != nullptr)
                {
                    if(bMoveAdd)
                    {
                        dataInfo.count++;
                        bMoveAdd = false;
                    }
                    // is_move = true;
                    dataInfo.grid[i][row]->getValue() = dataInfo.grid[i][j]->getValue();
                    dataInfo.grid[i][j].reset();
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


QPoint Board::freePosition()
{
    QPoint pos;
    if (dataInfo.isGridFull())
    {
        pos.setX(-1);
        pos.setY(-1);
    }
    else
    {
        int i,j;
        do {
            i = rand() % dataInfo.height;
            j = rand() % dataInfo.width;
        } while (dataInfo.atValue(i,j) != 0);
        pos.setX(i);
        pos.setY(j);
    }
    return pos;
}

bool Board::changed(Board &other) const
{
    if (dataInfo.height != other.getDataHeight() && dataInfo.width != other.getDataWidth())
        return false;
    for (int i = 0; i < dataInfo.height; i++)
        for (int j = 0; j < dataInfo.width; ++j)
            if ( ( (dataInfo.atValue(i,j) == 0 && other.dataInfo.atValue(i,j) != 0) ||
                 (dataInfo.atValue(i,j) != 0 && other.dataInfo.atValue(i,j) == 0) ) ||
                ( (dataInfo.atValue(i,j) != 0 && other.dataInfo.atValue(i,j) != 0) &&
                 dataInfo.atValue(i,j) != other.dataInfo.atValue(i,j)) )
                return true;
    return false;
}
