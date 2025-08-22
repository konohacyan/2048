#ifndef QGAMEBOARD_H
#define QGAMEBOARD_H

#include <QWidget>
#include <QSharedPointer>
#include <QVector>
#include "base_class.h"
#include "game.h"
#include "qtile.h"
#include "public_def.h"
using QTilePtr = QSharedPointer<QTile>;
using GamePtr = QSharedPointer<Game>;
class QVBoxLayout;
class QGridLayout;
class QKeyEvent;

/**
@brief 游戏棋盘
**/
class QGameBoard : public QWidget , public Observer
{
    Q_OBJECT
public:
    explicit QGameBoard(QWidget *parent = nullptr);
    void notify() override;     // 观察者通知回调

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void ChangeTheme(); // 变更主题

signals:

public slots:
    void resetGame();

private:
    void drawBoard();   // 绘制棋盘
    QLabel *score;
    GamePtr game;
    QVector<QVector<QTilePtr>> gui_board;
    QVBoxLayout *mainLayout;
    QGridLayout *boardLayout;
    ColorScheme scheme;     ///< 主题配色
};

#endif// QGAMEBOARD_H
