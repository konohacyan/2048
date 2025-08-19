#include "public_func.h"
#include <QStandardPaths>
#include <QDir>
#include <QGuiApplication>
#include <QWindow>
#include <QRandomGenerator>
#include <QDebug>
#include <algorithm>
#include <codecvt>
#include <locale>
#include <random>
#include <string>
#include <string_view>
#include <vector>
#include <filesystem>
namespace tool
{
    bool isProcessRunning(const  QString &processName)
    {
        QProcess process;
            process.start("tasklist", QStringList() << "/FI" << QString("IMAGENAME eq %1").arg(processName));
            process.waitForFinished();
            QString output = process.readAllStandardOutput();
            return output.contains(processName);
    }

    void startProgram(const QString &programPath)
    {
        QProcess::startDetached(programPath);
    }

    void activateRandomWindow()
    {
        QList<QWindow*> windows = QGuiApplication::allWindows();
           if (windows.isEmpty()) return;

           QList<QWindow*> visibleWindows;
           for (QWindow* window : windows)
           {
               if (window->isVisible() && !(window->windowState() & Qt::WindowMinimized))
               {
                   visibleWindows.append(window);
               }
           }

           if (visibleWindows.isEmpty()) return;

           QWindow* activeWindow = QGuiApplication::focusWindow();
           if (activeWindow) {
               visibleWindows.removeAll(activeWindow);
           }

           if (!visibleWindows.isEmpty())
           {
               int randomIndex = QRandomGenerator::global()->bounded(visibleWindows.size());
               QWindow* randomWindow = visibleWindows.at(randomIndex);

               randomWindow->show();
               randomWindow->raise();
               randomWindow->requestActivate();
           }
    }

    std::string getAppCachePath()
    {
        try
        {
            // 获取应用数据目录（跨平台）
            QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
            if (cacheDir.isEmpty()) {
                qWarning() << "Failed to get application data location";
                return "";
            }

            QDir dir(cacheDir);
            if (!dir.mkpath("2048Plan/FacingTheWholeWorld/Cache")) {
                qWarning() << "Failed to create cache directory";
                return "";
            }

            QString fullPath = dir.filePath("2048Plan/FacingTheWholeWorld/Cache");

            // 转换为UTF-8编码的std::string
            return fullPath.toStdString();

            // 如果需要确保使用正斜杠（跨平台兼容）
            // return QDir::toNativeSeparators(fullPath).toStdString();
        }
        catch (...)
        {
            qWarning() << "Exception occurred while getting cache path";
            return "";
        }
    }


    void xorEncryptDecrypt(char *data, size_t size)
    {

        if (ENCRYPTION_KEY.empty()) return;
        const char* keyData = ENCRYPTION_KEY.data();
        size_t keyLength = ENCRYPTION_KEY.size();

        for (size_t i = 0; i < size; ++i)
        {
            data[i] ^= keyData[i % keyLength];
        }
    }

    QString getAppCachePathQt()
    {
        QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        if (cacheDir.isEmpty())
        {
            return QString();
        }

        QDir dir(cacheDir);
        if (!dir.mkpath("2048Plan/FacingTheWholeWorld/Cache"))
        {
            return QString();
        }

        return dir.filePath("2048Plan/FacingTheWholeWorld/Cache");
    }

    void xorEncryptDecrypt(QByteArray &data)
    {
        if (data.isEmpty()) return;
        xorEncryptDecrypt(data.data(), static_cast<size_t>(data.size()));
    }

    void minimizeActiveWindow()
    {
        QWindow* activeWindow = QGuiApplication::focusWindow();
        if (activeWindow)
        {
            activeWindow->showMinimized();
        }
    }

}// namespace tool
