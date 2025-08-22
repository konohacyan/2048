#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "qgameboard.h"
#include "logger.h"
#include "public_macro.h"

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
    LOG_INFO("=====GAME START=====");
    LOG_INFO(QString("编译时间：%1-%2-%3 %4").arg(YEAR)
                             .arg(MONTH + 1, 2, 10, QChar('0'))
                             .arg(DAY, 2, 10, QChar('0'))
                             .arg(__TIME__).toStdString().c_str());
    QGameBoard gameBoard;
    gameBoard.show();
    return a.exec();
}
