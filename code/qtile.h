#ifndef QTILE_H
#define QTILE_H
#include <QLabel>
#include <QSharedPointer>
#include "public_def.h"
class Tile;
class QTile : public QLabel
{
    Q_OBJECT
    using TilePtr = QSharedPointer<Tile>;
public:
    QTile(TilePtr tile);
    void ChangeTheme();
    void draw();
    void setColorScheme(const ColorScheme& cs);
private:
    void updateTileAppearance();
    TilePtr tile;
    ColorScheme scheme;
};

#endif// QTILE_H
