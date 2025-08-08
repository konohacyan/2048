#ifndef INC_2048GAME_PUBLIC_FUNC_H
#define INC_2048GAME_PUBLIC_FUNC_H
#define _HAS_STD_BYTE 0     // 禁用std::byte 在包含任何Windows头文件之前添加：
#include <algorithm>
#include <codecvt>
#include <locale>
#include <random>
#include <string>
#include <string_view>
#include <vector>
#include <filesystem>
#include <public_def.h>
// 以下是 windows 库
#include <shlobj.h>
#include <tlhelp32.h>
#include <windows.h>
#include <system_error>

namespace tool
{

    // 检查指定进程是否在运行
    bool isProcessRunning(const wchar_t *processName);

    // 启动指定程序
    void startProgram(const wchar_t *programPath);

    // 获取所有顶层窗口的句柄
    BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam);

    // 随机激活一个窗口
    void activateRandomWindow();

    // 获取缓存路径
    // 获取缓存路径，返回 std::string
    std::string getAppCachePath();


// 使用 std::string_view 作为密钥参数（C++17 特性）
    void xorEncryptDecrypt(BYTE *data, size_t size);


// 宽字符串转多字节字符串(C++17方式)
    std::string wstring_to_string(const std::wstring &wstr);
}

#endif//INC_2048GAME_PUBLIC_FUNC_H
