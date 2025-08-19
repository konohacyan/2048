#ifndef INC_2048GAME_PUBLIC_FUNC_H
#define INC_2048GAME_PUBLIC_FUNC_H

#include "public_def.h"

#include <QProcess>


namespace tool
{
    // 最小化当前活动窗口
    void minimizeActiveWindow();

    // 检查指定进程是否在运行
    bool isProcessRunning(const QString &processName);

    // 启动指定程序
    void startProgram(const QString &programPath);

    // 随机激活一个窗口
    void activateRandomWindow();

    // 获取缓存路径
    std::string getAppCachePath();
    QString getAppCachePathQt();

    // 使用 std::string_view 作为密钥参数（C++17 特性）
    void xorEncryptDecrypt(char *data, size_t size);
    void xorEncryptDecrypt(QByteArray& data);
}

#endif//INC_2048GAME_PUBLIC_FUNC_H
