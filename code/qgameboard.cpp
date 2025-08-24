#include "qgameboard.h"
#include <QGridLayout>
#include "qtile.h"
#include <QKeyEvent>
#include "public_def.h"
#include "board.h"
#include <QIcon>

QGameBoard::QGameBoard(QWidget *parent) : QWidget(parent)
{
    game = GamePtr::create();
    setWindowTitle("2048面向世界");
    setWindowIcon(QIcon(":/res/logo.ico"));
    // 窗口大小
    resize(150 * game->getWidth() , 150 * game->getWidth() + 10);
    mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    setMinimumSize(800,800);

    boardLayout = nullptr;

    game->registerObserver(QSharedPointer<Observer>(this));


    // 初始化棋盘格子指针
    gui_board.resize(game->getBoard()->getDataHeight());
    for (int i = 0; i < game->getBoard()->getDataWidth(); ++i)
        gui_board[i].resize(game->getBoard()->getDataHeight());
    for (int i = 0; i < game->getBoard()->getDataHeight(); ++i)
        for (int j = 0; j < game->getBoard()->getDataWidth(); ++j)
            gui_board[i][j].reset();

    drawBoard();

    score = new QLabel(QString("积分: %1   合成次数: %2   最大合成数: %3").arg(game->getBoard()->getScore()).
                       arg(game->getBoard()->getCount()).
                       arg(game->getBoard()->getBest()));
    QFont font("SimHei", 12, QFont::Bold, true);
    score->setFont(font);
    score->setStyleSheet("QLabel { color: rgb(235,224,214); font: 16pt; }");
    score->setFixedHeight(50);
    mainLayout->insertWidget(1, score, 0, Qt::AlignRight);

    setStyleSheet("QGameBoard { background-color: rgb(187,173,160) }"); // 经典
    // scheme = ColorScheme::cDefault;
    // ChangeTheme();
}

void QGameBoard::notify()
{
    if (game->isGameOver())
        resetGame();
    // if (game->isWin())
    //     score->setText(QString("You hit 2048, congratulations! Keep playing to increase your score.\t\t SCORE: %1").arg(game->getScore()));
    // else
    //     score->setText(QString("SCORE: %1").arg(game->getBoard()->getScore()));
    score->setText(QString("积分: %1   合成次数: %2   最大合成数: %3").arg(game->getBoard()->getScore()).
                   arg(game->getBoard()->getCount()).
                   arg(game->getBoard()->getBest()));
    drawBoard();
}

void QGameBoard::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Up:
            game->move(MoveDirection::Up);
            break;
        case Qt::Key_Left:
            game->move(MoveDirection::Left);
            break;
        case Qt::Key_Right:
            game->move(MoveDirection::Right);
            break;
        case Qt::Key_Down:
            game->move(MoveDirection::Down);
            break;
    }
}

void QGameBoard::ChangeTheme()
{
    for (int i = 0; i < gui_board.size(); ++i)
    {
        for (int j = 0; j < gui_board[i].size(); ++j)
        {
            gui_board[i][j]->setColorScheme(scheme);
        }
    }
    switch (scheme)
    {
        case ColorScheme:: cDefault:
            setStyleSheet("QGameBoard { background-color: rgb(187,173,160) }"); // 经典
            break;
        case ColorScheme::cLightGray:
            setStyleSheet("QGameBoard {"
                          "   background-color: rgb(245, 245, 245);"  // 极浅灰
                          "   border: 1px solid rgb(230, 230, 230);" // 边框
                          "}");
            break;
        case ColorScheme::cLightGreen:
            setStyleSheet("QGameBoard {"
                          "   background-color: rgb(235, 240, 235);"  // 极浅绿
                          "   border: 1px solid rgb(220, 225, 220);" // 边框
                          "}");
            break;
        case ColorScheme::cTerminalBlack:
            setStyleSheet("QGameBoard {"
                          "   background-color: rgb(30, 30, 30);"    // 深灰黑
                          "   border: 1px solid rgb(60, 60, 60);"    // 边框
                          "}");
            break;
        case ColorScheme::cPaperBeige:
            setStyleSheet("QGameBoard {"
                          "   background-color: rgb(250, 240, 230);" // 米黄
                          "   border: 1px solid rgb(230, 220, 210);" // 边框
                          "}");
            break;
        case ColorScheme::cGuiseExecl:
            setStyleSheet("QGameBoard {"
                          "   background-color: rgb(255, 255, 255);"  // 纯白背景
                          "   border: 1px solid rgb(200, 200, 200);"  // 细边框
                          "}");
            break;
        default:
            break;
    }
}

void QGameBoard::resetGame()
{
    game->restart();
    drawBoard();
    score->setText(QString("积分: %1   合成次数: %2   最大合成数: %3").arg(game->getBoard()->getScore()).
                   arg(game->getBoard()->getCount()).
                   arg(game->getBoard()->getBest()));
}

void QGameBoard::drawBoard()
{
    delete boardLayout;
    boardLayout = new QGridLayout();
    for (int i = 0; i < game->getHeight(); ++i)
    {
        for (int j = 0; j < game->getWidth(); ++j)
        {
            gui_board[i][j].reset();
            gui_board[i][j] = QTilePtr::create(game->getBoard()->getTile(i,j));
            boardLayout->addWidget(gui_board[i][j].get(), i, j);
            gui_board[i][j]->draw();
        }
    }
    mainLayout->insertLayout(0, boardLayout);
}
