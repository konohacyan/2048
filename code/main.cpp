#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "qgameboard.h"
#include "logger.h"
#include "public_macro.h"
#include "public_def.h"
#include "QDateTime"
#include "QDir"

INITIALIZE_EASYLOGGINGPP

const char* GetProcessIdAsString(const el::LogMessage*)
{
    // 获取当前进程的 ID
    qint64 pid = QCoreApplication::applicationPid();
    QString pidStr = QString::number(pid);
    return  pidStr.toStdString().c_str();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ELOG_INIT("2048_log");
    ELOG_INFO(QString("当前版本号：v").append(VERSION_NUMBER).toStdString());
    ELOG_INFO(QString("编译时间：%1-%2-%3 %4").arg(YEAR)
                      .arg(MONTH + 1, 2, 10, QChar('0'))
                      .arg(DAY, 2, 10, QChar('0'))
                      .arg(__TIME__).toStdString());

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
    LOG_INFO("2048","=====GAME START=====");
    QGameBoard gameBoard;
    gameBoard.show();
    return a.exec();
}
