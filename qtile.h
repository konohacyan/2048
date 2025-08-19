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
    void ChangeTheme(const ColorScheme& cs);
    void draw();
private:
    TilePtr tile;

};

#endif// QTILE_H
