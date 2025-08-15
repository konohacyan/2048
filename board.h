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
public:
    Board();
    Board(const Board& other);
    ~Board();
    void move(MoveDirection direction);
    int getValue(const QPoint&  potin);
    int getDataHeigth();
    int getDataWidth();
    bool movePossible() const;  // 是否可以移动
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
