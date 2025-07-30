#ifndef INC_2048GAME_PUBLIC_FUNC_H
#define INC_2048GAME_PUBLIC_FUNC_H
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include <algorithm>
#include <random>
#include <shlobj.h>
#include <string>


namespace tool{


    // 检查指定进程是否在运行
    bool IsProcessRunning(const wchar_t* processName)
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
    void StartProgram(const wchar_t* programPath)
    {
        ShellExecuteW(nullptr, L"open", programPath, nullptr, nullptr, SW_SHOWNORMAL);
    }

    // 获取所有顶层窗口的句柄
    BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
    {
        auto* handles = reinterpret_cast<std::vector<HWND>*>(lParam);

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
    void ActivateRandomWindow()
    {
        std::vector<HWND> windowHandles;
        EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&windowHandles));

        if (!windowHandles.empty())
        {
            HWND foreground = GetForegroundWindow();
            windowHandles.erase(std::remove(windowHandles.begin(), windowHandles.end(), foreground), windowHandles.end());

            if (!windowHandles.empty()) {
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
    std::wstring GetAppCachePath()
    {
        PWSTR path = nullptr;
        if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, nullptr, &path))) {
            std::wstring cachePath(path);
            CoTaskMemFree(path);

            // 添加子目录
            std::vector<std::wstring> dirs = { L"2048Plan", L"FacingTheWholeWorld", L"Cache" };
            std::wstring currentPath = cachePath + L"\\";

            for (const auto& dir : dirs) {
                currentPath += dir + L"\\";
                if (!CreateDirectoryW(currentPath.c_str(), nullptr)) {
                    DWORD err = GetLastError();
                    if (err == ERROR_ALREADY_EXISTS) {
                        continue;  // 目录已存在，继续下一级
                    }
                    LPWSTR errMsg = nullptr;
                    FormatMessageW(
                            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                            nullptr,
                            err,
                            0,
                            reinterpret_cast<LPWSTR>(&errMsg),
                            0,
                            nullptr
                    );

                    std::wcerr << L"创建目录失败: " << currentPath
                               << L"\n错误代码: " << err
                               << L"\n错误信息: " << (errMsg ? errMsg : L"未知错误")
                               << std::endl;

                    if (errMsg) LocalFree(errMsg);
                    return L"";  // 关键错误时返回
                }
            }
            return currentPath;
        }
        return L"";
    }


}

#endif//INC_2048GAME_PUBLIC_FUNC_H
