#include <public_func.h>

namespace tool
{
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

    void startProgram(const wchar_t *programPath)
    {
        ShellExecuteW(nullptr, L"open", programPath, nullptr, nullptr, SW_SHOWNORMAL);
    }

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


    void xorEncryptDecrypt(BYTE *data, size_t size)
    {
        const BYTE *keyBytes = reinterpret_cast<const BYTE *>(ENCRYPTION_KEY.data());
        size_t keyLength = ENCRYPTION_KEY.size() * sizeof(wchar_t);

        for (size_t i = 0; i < size; ++i)
        {
            data[i] ^= keyBytes[i % keyLength];
        }
    }

    std::string wstring_to_string(const std::wstring &wstr)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
        return converter.to_bytes(wstr);
    }

}// namespace tool