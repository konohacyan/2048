#include "qtile.h"
#include <QGraphicsDropShadowEffect>
#include "base_class.h"
QTile::QTile(TilePtr tile)
{
    setAlignment(Qt::AlignCenter);
    this->tile = tile;
}

void QTile::ChangeTheme(const ColorScheme &cs)
{
    switch (cs)
    {
        case ColorScheme::cLightGray:
            setStyleSheet("QTile {"
                          "   background-color: rgb(255, 255, 255);"  // 纯白格子
                          "   border: 1px solid rgb(235, 235, 235);" // 极细边框
                          "   color: rgb(100, 100, 100);"            // 深灰数字
                          "   font: 12pt 'Segoe UI';"                // 现代字体
                          "}");
            break;
        case ColorScheme::cLightGreen:
            setStyleSheet("QTile {"
                          "   background-color: rgb(245, 248, 245);"  // 更浅的绿
                          "   border: 1px solid rgb(225, 230, 225);" // 边框
                          "   color: rgb(70, 90, 70);"               // 墨绿数字
                          "   font: 12pt 'Consolas';"                // 代码编辑器字体
                          "}");
            break;
        case ColorScheme::cTerminalBlack:
            setStyleSheet("QTile {"
                          "   background-color: rgb(50, 50, 50);"    // 稍亮的黑
                          "   border: 1px solid rgb(70, 70, 70);"   // 边框
                          "   color: rgb(200, 200, 200);"            // 浅灰数字
                          "   font: 12pt 'Courier New';"             // 终端字体
                          "}");
            break;
        case ColorScheme::cPaperBeige:
            setStyleSheet("QTile {"
                          "   background-color: rgb(255, 250, 240);" // 更浅的米白
                          "   border: 1px solid rgb(240, 230, 220);" // 边框
                          "   color: rgb(120, 90, 60);"              // 咖啡色数字
                          "   font: 12pt 'Times New Roman';"         // 经典衬线字体
                          "}");
            break;
        case ColorScheme::cGuiseExecl:
            setStyleSheet("QTile {"
                          "   background-color: rgb(248, 248, 248);"  // 格子颜色
                          "   border: 1px solid rgb(220, 220, 220);"  // 边框
                          "   color: rgb(80, 80, 80);"               // 数字颜色（深灰）
                          "   font: 12pt 'Arial';"                   // 办公字体
                          "}");
            break;
        default:
            break;
    }
}

void QTile::draw()
{
    if (tile.isNull())
    {
        setText("");
    }
    else
    {
        setText(QString::number(tile->getValue()));
        switch (tile->getValue())
        {
            case 2:
            {
                setStyleSheet("QTile { background: rgb(238,228,218); color: rgb(119,110,101); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 4:
            {
                setStyleSheet("QTile { background: rgb(237,224,200); color: rgb(119,110,101); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 8:
            {
                setStyleSheet("QTile { background: rgb(242,177,121); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 16:
            {
                setStyleSheet("QTile { background: rgb(245,150,100); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 32:
            {
                setStyleSheet("QTile { background: rgb(245,125,95); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 64:
            {
                setStyleSheet("QTile { background: rgb(245,95,60); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 128:
            {
                setStyleSheet("QTile { background: rgb(237,207,114); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 256:
            {
                QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect();
                dse->setColor(Qt::yellow);
                dse->setBlurRadius(20);
                dse->setOffset(-1);
                setGraphicsEffect(dse);
                setStyleSheet("QTile { background: rgb(237,204,97); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 512:
            {
                QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect();
                dse->setColor(Qt::yellow);
                dse->setBlurRadius(30);
                dse->setOffset(-1);
                setGraphicsEffect(dse);
                setStyleSheet("QTile { background: rgb(237,204,97); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 1024:
            {
                QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect();
                dse->setColor(Qt::yellow);
                dse->setBlurRadius(40);
                dse->setOffset(-1);
                setGraphicsEffect(dse);
                setStyleSheet("QTile { background: rgb(237,204,97); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            case 2048:
            {
                QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect();
                dse->setColor(Qt::yellow);
                dse->setBlurRadius(50);
                dse->setOffset(-1);
                setGraphicsEffect(dse);
                setStyleSheet("QTile { background: rgb(237,204,97); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
            default:
            {
                setStyleSheet("QTile { background: rgb(238,228,218); color: rgb(119,110,101); font: bold; border-radius: 10px; font: 40pt; }");
                break;
            }
        }
    }
}
