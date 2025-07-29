#ifndef INC_2048GAME_PUBLIC_FUNC_H
#define INC_2048GAME_PUBLIC_FUNC_H
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include <algorithm>
#include <random>

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






#endif//INC_2048GAME_PUBLIC_FUNC_H
