#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "qgameboard.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale: uiLanguages)
    {
        const QString baseName = "2048_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            a.installTranslator(&translator);
            break;
        }
    }
    srand(time(NULL));
    // MainWindow w;
    // w.show();
    QGameBoard gameBoard;
    gameBoard.show();
    return a.exec();
}
