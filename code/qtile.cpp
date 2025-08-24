#include "qtile.h"
#include <QGraphicsDropShadowEffect>
#include "base_class.h"
#include <QJsonObject>

QTile::QTile(TilePtr tile)
{
    setAlignment(Qt::AlignCenter);
    this->tile = tile;
    scheme = ColorScheme::cDefault;
}

void QTile::ChangeTheme()
{
    switch (scheme)
    {
        case ColorScheme::cDefault:
            break;
        case ColorScheme::cLightGray:
            setStyleSheet("QTile {"
                          "   background-color: rgb(255, 255, 255);"  // 纯白格子
                          "   border: 1px solid rgb(235, 235, 235);" // 极细边框
                          "   color: rgb(100, 100, 100);"            // 深灰数字
                          "   font: 72pt 'Segoe UI';"                // 现代字体
                          "   font: bold;"
                          "   border-radius: 10px;"
                          "}");
            break;
        case ColorScheme::cLightGreen:
            setStyleSheet("QTile {"
                          "   background-color: rgb(245, 248, 245);"  // 更浅的绿
                          "   border: 1px solid rgb(225, 230, 225);" // 边框
                          "   color: rgb(70, 90, 70);"               // 墨绿数字
                          "   font: 72pt 'Consolas';"                // 代码编辑器字体
                          "   font: bold;"
                          "   border-radius: 10px;"
                          "}");
            break;
        case ColorScheme::cTerminalBlack:
            setStyleSheet("QTile {"
                          "   background-color: rgb(50, 50, 50);"    // 稍亮的黑
                          "   border: 1px solid rgb(70, 70, 70);"   // 边框
                          "   color: rgb(200, 200, 200);"            // 浅灰数字
                          "   font: 72pt 'Courier New';"             // 终端字体
                          "   font: bold;"
                          "   border-radius: 10px;"
                          "}");
            break;
        case ColorScheme::cPaperBeige:
            setStyleSheet("QTile {"
                          "   background-color: rgb(255, 250, 240);" // 更浅的米白
                          "   border: 1px solid rgb(240, 230, 220);" // 边框
                          "   color: rgb(120, 90, 60);"              // 咖啡色数字
                          "   font: 72pt 'Times New Roman';"         // 经典衬线字体
                          "   font: bold;"
                          "   border-radius: 10px;"
                          "}");
            break;
        case ColorScheme::cGuiseExecl:
            setStyleSheet("QTile {"
                          "   background-color: rgb(248, 248, 248);"  // 格子颜色
                          "   border: 1px solid rgb(220, 220, 220);"  // 边框
                          "   color: rgb(80, 80, 80);"               // 数字颜色（深灰）
                          "   font: 72pt 'Arial';"                   // 办公字体
                          "   font: bold;"
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
        setStyleSheet("QTile { background: rgb(204,192,179); border-radius: 10px; }");
        return;
    }
    setText(QString::number(tile->getValue()));
    if(scheme == ColorScheme::cDefault)
    {
        switch (tile->getValue())
        {
            case 2:
            {
                setStyleSheet("QTile { background: rgb(238,228,218); color: rgb(119,110,101); font: bold; border-radius: 10px; font: 72pt; }");
                break;
            }
            case 4:
            {
                setStyleSheet("QTile { background: rgb(237,224,200); color: rgb(119,110,101); font: bold; border-radius: 10px; font: 72pt; }");
                break;
            }
            case 8:
            {
                setStyleSheet("QTile { background: rgb(242,177,121); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 72pt; }");
                break;
            }
            case 16:
            {
                setStyleSheet("QTile { background: rgb(245,150,100); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 72pt; }");
                break;
            }
            case 32:
            {
                setStyleSheet("QTile { background: rgb(245,125,95); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 72pt; }");
                break;
            }
            case 64:
            {
                setStyleSheet("QTile { background: rgb(245,95,60); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 72pt; }");
                break;
            }
            case 128:
            {
                setStyleSheet("QTile { background: rgb(237,207,114); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 62pt; }");
                break;
            }
            case 256:
            {
                QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect();
                dse->setColor(Qt::yellow);
                dse->setBlurRadius(20);
                dse->setOffset(-1);
                setGraphicsEffect(dse);
                setStyleSheet("QTile { background: rgb(237,204,97); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 62pt; }");
                break;
            }
            case 512:
            {
                QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect();
                dse->setColor(Qt::yellow);
                dse->setBlurRadius(30);
                dse->setOffset(-1);
                setGraphicsEffect(dse);
                setStyleSheet("QTile { background: rgb(237,204,97); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 62pt; }");
                break;
            }
            case 1024:
            {
                QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect();
                dse->setColor(Qt::yellow);
                dse->setBlurRadius(40);
                dse->setOffset(-1);
                setGraphicsEffect(dse);
                setStyleSheet("QTile { background: rgb(237,204,97); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 52pt; }");
                break;
            }
            case 2048:
            {
                QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect();
                dse->setColor(Qt::yellow);
                dse->setBlurRadius(50);
                dse->setOffset(-1);
                setGraphicsEffect(dse);
                setStyleSheet("QTile { background: rgb(237,204,97); color: rgb(255,255,255); font: bold; border-radius: 10px; font: 52pt; }");
                break;
            }
            default:
            {
                setStyleSheet("QTile { background: rgb(238,228,218); color: rgb(119,110,101); font: bold; border-radius: 10px; font: 52pt; }");
                break;
            }
        }
    }
    else
    {
        updateTileAppearance();
    }

}

void QTile::setColorScheme(const ColorScheme &cs)
{
    scheme = cs;
    // ChangeTheme();
}

void QTile::updateTileAppearance()
{
    const int value = tile->getValue();
    QColor bgColor, textColor;
    QString fontFamily;
    int fontSize = 72;
    // 根据当前主题设置基础样式
    switch (scheme)
    {
        case ColorScheme::cLightGray:
            fontFamily = "'Segoe UI'";
            textColor = QColor(100, 100, 100); // 深灰数字
            break;
        case ColorScheme::cLightGreen:
            fontFamily = "'Consolas'";
            textColor = QColor(70, 90, 70);    // 墨绿数字
            break;
        case ColorScheme::cTerminalBlack:
            fontFamily = "'Courier New'";
            textColor = QColor(200, 200, 200); // 浅灰数字
            break;
        case ColorScheme::cPaperBeige:
            fontFamily = "'Times New Roman'";
            textColor = QColor(120, 90, 60);   // 咖啡色数字
            break;
        case ColorScheme::cGuiseExecl:
            fontFamily = "'Arial'";
            textColor = QColor(80, 80, 80);    // 深灰数字
            break;
        default:
            fontFamily = "'Segoe UI'";
            textColor = Qt::black;
    }

    // 数字颜色映射（2048标准配色）
    switch (value)
    {
        case 2:    bgColor = QColor(238, 228, 218); textColor = QColor(119, 110, 101); break;
        case 4:    bgColor = QColor(237, 224, 200); textColor = QColor(119, 110, 101); break;
        case 8:    bgColor = QColor(242, 177, 121); textColor = Qt::white; break;
        case 16:   bgColor = QColor(245, 150, 100); textColor = Qt::white; break;
        case 32:   bgColor = QColor(245, 125, 95);  textColor = Qt::white; break;
        case 64:   bgColor = QColor(245, 95, 60);   textColor = Qt::white; break;
        case 128:  bgColor = QColor(237, 207, 114); textColor = Qt::white; break;
        case 256:  bgColor = QColor(237, 204, 97);  textColor = Qt::white; break;
        case 512:  bgColor = QColor(237, 200, 80);  textColor = Qt::white; break;
        case 1024: bgColor = QColor(237, 197, 63); textColor = Qt::white; break;
        case 2048: bgColor = QColor(237, 194, 46); textColor = Qt::white; break;
        default:   bgColor = QColor(238, 228, 218); textColor = QColor(119, 110, 101); break;
    }
    if (scheme == ColorScheme::cPaperBeige)
    {
        switch (value)
        {
            case 2:    bgColor = QColor(238, 228, 218); textColor = QColor(119, 110, 101); break;
            case 4:    bgColor = QColor(237, 224, 200); textColor = QColor(119, 110, 101); break;
            case 8:    bgColor = QColor(242, 177, 121); textColor = Qt::white; break;
            case 16:   bgColor = QColor(245, 150, 100); textColor = Qt::white; break;
            case 32:   bgColor = QColor(245, 125, 95);  textColor = Qt::white; break;
            case 64:   bgColor = QColor(245, 95, 60);   textColor = Qt::white; break;
            case 128:  bgColor = QColor(237, 207, 114); textColor = Qt::white; break;
            case 256:  bgColor = QColor(237, 204, 97);  textColor = Qt::white; break;
            case 512:  bgColor = QColor(237, 200, 80);  textColor = Qt::white; break;
            case 1024: bgColor = QColor(237, 197, 63);  textColor = Qt::white; break;
            case 2048: bgColor = QColor(237, 194, 46);  textColor = Qt::white; break;
            default:   bgColor = QColor(238, 228, 218); textColor = QColor(119, 110, 101);
        }
    }
    else
    {
        // 非默认主题时保持主题定义的基础颜色，仅调整背景色深浅
        switch (value)
        {
            case 2:    bgColor = textColor.lighter(150); break;
            case 4:    bgColor = textColor.lighter(140); break;
            case 8:    bgColor = textColor.lighter(130); break;
            case 16:   bgColor = textColor.lighter(120); break;
            case 32:   bgColor = textColor.lighter(110); break;
            case 64:   bgColor = textColor; break;
            case 128:  bgColor = textColor.darker(110); break;
            case 256:  bgColor = textColor.darker(120); break;
            case 512:  bgColor = textColor.darker(130); break;
            case 1024: bgColor = textColor.darker(140); break;
            case 2048: bgColor = textColor.darker(150); break;
            default:   bgColor = textColor.lighter(160);
        }
    }
    // 动态计算字体大小（根据数字位数调整）
    if (value >= 1000) fontSize = 48;
    if (value >= 10000) fontSize = 36;
    // 构建样式表
    QString style = QString("QTile {"
                            "background-color: %1;"
                            "color: %2;"
                            "font: bold %3pt %4;"
                            "border: 1px solid %5;"
                            "border-radius: 10px;"
                            "qproperty-alignment: AlignCenter;"
                            "}")
                            .arg(bgColor.name())
                            .arg(textColor.name())
                            .arg(fontSize)
                            .arg(fontFamily)
                            .arg(textColor.darker(150).name());

    setStyleSheet(style);
    // 大数字添加发光效果（仅限默认主题）
    if (value >= 256 && scheme == ColorScheme::cDefault)
    {
        auto *dse = new QGraphicsDropShadowEffect(this);
        dse->setColor(QColor(243, 215, 116));
        dse->setBlurRadius(qMin(50, 20 + value / 512 * 10));
        setGraphicsEffect(dse);
    }
    else
    {
        setGraphicsEffect(nullptr);
    }
}

