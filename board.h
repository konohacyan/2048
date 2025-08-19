#ifndef BOARD_H
#define BOARD_H
#include "base_class.h"
#include "public_def.h"
#include <QPoint>

/**
 @brief 只控制方块数值，不控制游戏进度
**/
class Board : public Subject
{
    using TilePtr = QSharedPointer<Tile>;
public:
    Board();
    Board(const Board& other);
    ~Board();
    void move(const MoveDirection& direction);
    int getValue(const int& x, const int& y);
    TilePtr getTile(const int& x, const int& y);
    int getDataHeight();
    int getDataWidth();
    bool movePossible() const;  // 是否可以移动
    void clear();
    int getScore();
    int getBest();
    int getCount();
    void reset();
private:
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    QPoint freePosition();  ///< 随机生成位置
    bool changed(Board& other) const;
    DataInfo2048 dataInfo;

};

#endif// BOARD_H
