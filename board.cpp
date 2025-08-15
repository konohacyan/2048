#include "board.h"

Board::Board(const Board &other)
{
    dataInfo = other.dataInfo;
}

Board::~Board()
{

}

void Board::move(MoveDirection direction)
{
    switch (direction)
    {
        case MoveDirection::Up: moveUp(); break;
        case MoveDirection::Down: moveDown(); break;
        case MoveDirection::Left: moveLeft(); break;
        case MoveDirection::Right: moveRight(); break;
        default:
            break;
    }
}

int Board::getValue(const QPoint &potin)
{
    return dataInfo.arr[potin.x(),potin.y()]->getValue();
}

int Board::getDataHeigth()
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

void Board::moveUp()
{
    bool bMoveAdd = true;
    for (int i = 0; i < dataInfo.width; i++)
    {
        int index = -1;
        for (int j = 0; j < dataInfo.height; j++)
        {
            if (dataInfo.arr[j][i].getValue() != 0)
            {
                if (index != -1)
                {
                    if (dataInfo.arr[index][i] == dataInfo.arr[j][i])
                    {
                        is_move = true;
                        dataInfo.arr[index][i].getValue() += dataInfo.arr[j][i].getValue();
                        dataInfo.score += dataInfo.arr[j][i].getValue();
                        dataInfo.best = (((dataInfo.best) > (dataInfo.arr[index][i]).getValue()) ? (dataInfo.best) : (dataInfo.arr[index][i].getValue()));
                        if(bMoveAdd)
                        {
                            dataInfo.count++;
                            bMoveAdd = false;
                        }
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
            if (dataInfo.arr[row][i].getValue() == 0)
            {
                if (dataInfo.arr[j][i].getValue() != 0)
                {
                    if(bMoveAdd)
                    {
                        dataInfo.count++;
                        bMoveAdd = false;
                    }
                    is_move = true;
                    dataInfo.arr[row][i] = dataInfo.arr[j][i].getValue();
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
        } while (dataInfo.at(i,j) != 0);
        pos.setX(i);
        pos.setY(j);
    }
    return pos;
}

bool Board::changed(Board &other) const
{
    if (dataInfo.height != other.getDataHeigth() && dataInfo.width != other.getDataWidth())
        return false;
    for (int i = 0; i < dataInfo.height; i++)
        for (int j = 0; j < dataInfo.width; ++j)
            if ( ( (dataInfo.at(i,j) == 0 && other.dataInfo.at(i,j) != 0) ||
                 (dataInfo.at(i,j) != 0 && other.dataInfo.at(i,j) == 0) ) ||
                ( (dataInfo.at(i,j) != 0 && other.dataInfo.at(i,j) != 0) &&
                 dataInfo.at(i,j) != other.dataInfo.at(i,j)) )
                return true;
    return false;
}
