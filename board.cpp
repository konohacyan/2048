#include "board.h"

Board::Board() : dataInfo(DataInfo2048(4,4))
{
    dataInfo.clear();
}

Board::Board(const Board &other) : dataInfo(other.dataInfo)
{

}

Board::~Board()
{

}

void Board::move(const MoveDirection &direction)
{
    Board pre_move_board(*this);
    prepareForNextMove();
    switch (direction)
    {
        case MoveDirection::Up: moveUp(); break;
        case MoveDirection::Down: moveDown(); break;
        case MoveDirection::Left: moveLeft(); break;
        case MoveDirection::Right: moveRight(); break;
        default:
            break;
    }
    if (changed(pre_move_board))
    {
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

void Board::restart()
{
    dataInfo.clear();

    QPoint point = freePosition();
    dataInfo.setTile(point.x(), point.y(), TilePtr::create());
    point = freePosition();
    dataInfo.setTile(point.x(), point.y(), TilePtr::create());
}

void Board::moveUp()
{
    for (int i = 0; i < dataInfo.width; ++i)
        for (int j = 0; j < dataInfo.height; ++j)
            moveVertically(i, j, MoveDirection::Up);
}

void Board::moveDown()
{
    for (int i = dataInfo.width -1; i >= 0; --i)
        for (int j = 0; j < dataInfo.height; ++j)
            moveVertically(i, j, MoveDirection::Down);
}

void Board::moveLeft()
{
    for (int i = 0; i < dataInfo.width; ++i)
        for (int j = 0; j < dataInfo.height; ++j)
            moveHorizontally(i, j, MoveDirection::Left);
}

void Board::moveRight()
{
    for (int i = 0; i < dataInfo.width; ++i)
        for (int j = dataInfo.height-1; j >= 0; --j)
            moveHorizontally(i, j, MoveDirection::Right);
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
            i = rand() % dataInfo.width;
            j = rand() % dataInfo.height;
        } while (dataInfo.atValue(i,j) >= 0);
        pos.setX(i);
        pos.setY(j);
    }
    return pos;
}

bool Board::changed(Board &other) const
{
    if (dataInfo.height != other.getDataHeight() && dataInfo.width != other.getDataWidth())
        return false;
    for (int i = 0; i < dataInfo.width; i++)
        for (int j = 0; j < dataInfo.height; ++j)
            if ( ( (dataInfo.atValue(i,j) == 0 && other.dataInfo.atValue(i,j) != 0) ||
                 (dataInfo.atValue(i,j) != 0 && other.dataInfo.atValue(i,j) == 0) ) ||
                ( (dataInfo.atValue(i,j) != 0 && other.dataInfo.atValue(i,j) != 0) &&
                 dataInfo.atValue(i,j) != other.dataInfo.atValue(i,j)) )
                return true;
    return false;
}

void Board::moveHorizontally(const int &i, const int &j, const MoveDirection &dir)
{
    if (dataInfo.atTile(i,j) != nullptr)
    {
        bool tileCollision = false;
        int newj;
        if (dir == MoveDirection::Right)
            newj = j + 1;
        else
            newj = j - 1;

        while (inbounds(i,newj) && dataInfo.atTile(i,newj) == nullptr) {
            if (dir == MoveDirection::Right)
                newj++;
            else
                newj--;
        }

        if (!inbounds(i,newj))
        {
            if (dir == MoveDirection::Right)
                dataInfo.atTile(i,dataInfo.height - 1) = dataInfo.atTile(i,j);
            else
                dataInfo.atTile(i,0) = dataInfo.atTile(i,j);
        }
        else
        {
            if (dataInfo.atTile(i,newj)->getValue() == dataInfo.atTile(i,j)->getValue() && !dataInfo.atTile(i,newj)->getUpgratedThisMove())
            {

                tileCollision = true;
                handleCollision(i, newj);
            }
            else
            {
                if (dir == MoveDirection::Right)
                    dataInfo.atTile(i,newj - 1) = dataInfo.atTile(i,j);
                else
                    dataInfo.atTile(i,newj + 1) = dataInfo.atTile(i,j);
            }
        }
        if ( (dir == MoveDirection::Right && newj-1 != j) || (dir == MoveDirection::Left && newj+1 != j) || tileCollision )
            dataInfo.atTile(i,j).reset();

        // if (tileCollision)
        //     tileCollisionLastRound = true;
    }
}

void Board::moveVertically(const int &i, const int &j, const MoveDirection &dir)
{
    if (dataInfo.atTile(i,j) != nullptr)
    {
        bool tileCollision = false;
        int newi;
        if (dir == MoveDirection::Up)
            newi = i - 1;
        else
            newi = i + 1;

        while (inbounds(newi,j) && dataInfo.atTile(newi,j) == nullptr)
        {
            if (dir == MoveDirection::Up)
                newi--;
            else
                newi++;
        }

        if (!inbounds(newi,j))
        {
            if (dir == MoveDirection::Up)
                dataInfo.atTile(0,j) = dataInfo.atTile(i,j);
            else
               dataInfo.atTile(dataInfo.width - 1,j) = dataInfo.atTile(i,j);
        }
        else
        {
            if (dataInfo.atTile(newi,j)->getValue() == dataInfo.atTile(i,j)->getValue() && !dataInfo.atTile(newi,j)->getUpgratedThisMove())
            {
                tileCollision = true;
                handleCollision(newi, j);
            }
            else
            {
                if (dir == MoveDirection::Up)
                    dataInfo.atTile(newi+1,j) = dataInfo.atTile(i,j);
                else
                    dataInfo.atTile(newi-1,j) = dataInfo.atTile(i,j);
            }
        }

        if ( (dir == MoveDirection::Up && newi+1 != i) || (dir == MoveDirection::Down && newi-1 != i) || tileCollision )
            dataInfo.atTile(i,j) = nullptr;

        // if (tileCollision)
        //     tileCollisionLastRound = true;
    }

}

bool Board::inbounds(const int &i, const int &j)
{
    return (i >= 0 && j >= 0 && i < dataInfo.width && j < dataInfo.height);
}

void Board::handleCollision(const int &i, const int &j)
{
    dataInfo.atTile(i,j)->upgrade();
    dataInfo.atTile(i,j)->setUpgratedThisMove(true);
    dataInfo.score += dataInfo.atValue(i,j);
    dataInfo.count ++;
    dataInfo.best = dataInfo.atValue(i,j) > dataInfo.best ? dataInfo.atValue(i,j) : dataInfo.best;
}

void Board::prepareForNextMove()
{
    dataInfo.score = 0;
    for (int i = 0; i < dataInfo.width; ++i)
    {
        for (int j = 0; j < dataInfo.height; ++j)
        {
            if (dataInfo.atTile(i,j) != nullptr)
            {
                dataInfo.atTile(i,j)->setUpgratedThisMove(false);
            }
        }
    }
}
