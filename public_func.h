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
// 以下是 windows 库
#include <shlobj.h>
#include <tlhelp32.h>
#include <windows.h>
#include <system_error>

namespace tool
{

    // 检查指定进程是否在运行
    bool isProcessRunning(const wchar_t *processName)
    {
        bool exists = false;
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(PROCESSENTRY32);

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (Process32First(snapshot, &entry))
        {
            while (Process32Next(snapshot, &entry))
            {
                if (_wcsicmp(reinterpret_cast<const wchar_t *>(entry.szExeFile), processName) == 0)
                {
                    exists = true;
                    break;
                }
            }
        }
        CloseHandle(snapshot);
        return exists;
    }

    // 启动指定程序
    void startProgram(const wchar_t *programPath)
    {
        ShellExecuteW(nullptr, L"open", programPath, nullptr, nullptr, SW_SHOWNORMAL);
    }

    // 获取所有顶层窗口的句柄
    BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam)
    {
        auto *handles = reinterpret_cast<std::vector<HWND> *>(lParam);

        if (IsWindowVisible(hwnd) && !IsIconic(hwnd))
        {
            int length = GetWindowTextLength(hwnd);
            if (length > 0)
            {
                handles->push_back(hwnd);
            }
        }
        return TRUE;
    }

    // 随机激活一个窗口
    void activateRandomWindow()
    {
        std::vector<HWND> windowHandles;
        EnumWindows(enumWindowsProc, reinterpret_cast<LPARAM>(&windowHandles));

        if (!windowHandles.empty())
        {
            HWND foreground = GetForegroundWindow();
            windowHandles.erase(std::remove(windowHandles.begin(), windowHandles.end(), foreground), windowHandles.end());

            if (!windowHandles.empty())
            {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(0, windowHandles.size() - 1);
                HWND randomWindow = windowHandles[dis(gen)];

                ShowWindow(randomWindow, SW_RESTORE);
                SetForegroundWindow(randomWindow);
            }
        }
    }

    // 获取缓存路径
    // 获取缓存路径，返回 std::string
    std::string getAppCachePath()
    {
        namespace fs = std::filesystem;

        // 获取本地应用数据目录
        PWSTR path = nullptr;
        if (FAILED(SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, nullptr, &path)))
        {
            return "";
        }

        try
        {
            // 转换为 filesystem::path 并自动释放内存
            fs::path cachePath(path);
            CoTaskMemFree(path);

            // 构建子目录路径
            fs::path fullPath = cachePath / "2048Plan" / "FacingTheWholeWorld" / "Cache";

            // 创建目录（递归创建）
            std::error_code ec;
            if (!fs::create_directories(fullPath, ec) && !ec)
            {
                // 检查是否因为目录已存在而"失败"（这不是真正的错误）
                if (!fs::exists(fullPath))
                {
                    // 真正的错误发生
                    return "";
                }
            }

            // 返回UTF-8字符串
            return fullPath.u8string();
        }
        catch (...)
        {
            CoTaskMemFree(path);
            return "";
        }
    }


// 使用 std::string_view 作为密钥参数（C++17 特性）
    inline void xorEncryptDecrypt(BYTE *data, size_t size, std::string key = ENCRYPTION_KEY)
    {
        const BYTE *keyBytes = reinterpret_cast<const BYTE *>(key.data());
        size_t keyLength = key.size() * sizeof(wchar_t);

        for (size_t i = 0; i < size; ++i)
        {
            data[i] ^= keyBytes[i % keyLength];
        }
    }


// 宽字符串转多字节字符串(C++17方式)
    std::string wstring_to_string(const std::wstring &wstr)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
        return converter.to_bytes(wstr);
    }

}

#endif//INC_2048GAME_PUBLIC_FUNC_H
