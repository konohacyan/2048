#include "logger.h"
#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <sys/stat.h>  // 用于C++11的目录创建
#include <sys/types.h> // 用于目录创建
#ifdef _WIN32
#include <direct.h>    // Windows下的目录创建
#endif

// 初始化静态成员
Logger* Logger::instance = nullptr;

Logger::Logger(const std::string& fileName) : m_fileName(fileName) {
    createLogDirectory();
    checkAndSwitchLogFile();
}

Logger::~Logger() {
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
}

Logger* Logger::getInstance(const std::string& fileName) {
    static std::mutex instanceMutex;
    std::lock_guard<std::mutex> lock(instanceMutex);

    if (instance == nullptr) {
        instance = new Logger(fileName);
    }
    else if (!fileName.empty() && instance->m_fileName != fileName) {
        // 如果文件名不同，删除旧实例创建新实例
        delete instance;
        instance = new Logger(fileName);
    }

    return instance;
}

std::string Logger::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);

    // 获取毫秒部分
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch() % std::chrono::seconds(1)
    ).count();

    std::tm local_tm;
#ifdef _MSC_VER  // Windows平台使用安全函数
    localtime_s(&local_tm, &now_c);
#else  // Linux/macOS平台使用线程安全版本
    localtime_r(&now_c, &local_tm);
#endif

    char time_str[32];
    std::strftime(time_str, sizeof(time_str), "%Y-%m-%d_%H:%M:%S", &local_tm);

    // 拼接毫秒
    char result[40];
    std::snprintf(result, sizeof(result), "%s.%03d", time_str, static_cast<int>(ms));
    return result;
}

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
    case LogLevel::DEBUG: return "DEBUG";
    case LogLevel::INFO:  return "INFO ";
    case LogLevel::WARNING: return "WARN ";
    case LogLevel::ERROR_: return "ERROR";  // 修复枚举与字符串的匹配
    case LogLevel::FATAL: return "FATAL";
    default: return "UNKNOWN";
    }
}

// C++11兼容的目录创建函数
void Logger::createLogDirectory() {
    const std::string dir = "log";
#ifdef _WIN32
    if (_access(dir.c_str(), 0) == -1) {  // 检查目录是否存在
        if (_mkdir(dir.c_str()) == -1) {   // 创建目录
            std::cerr << "创建日志目录失败" << std::endl;
        }
    }
#else
    struct stat info;
    if (stat(dir.c_str(), &info) != 0) {  // 检查目录是否存在
        if (mkdir(dir.c_str(), 0755) == -1) {  // 创建目录
            std::cerr << "创建日志目录失败" << std::endl;
        }
    } else if (!(info.st_mode & S_IFDIR)) {  // 检查是否为目录
        std::cerr << "log不是一个目录" << std::endl;
    }
#endif
}

void Logger::checkAndSwitchLogFile() {
    // 获取当前时间
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);

    std::tm local_tm;
#ifdef _MSC_VER  // Windows平台使用安全函数
    localtime_s(&local_tm, &now_c);
#else  // Linux/macOS平台使用线程安全版本
    localtime_r(&now_c, &local_tm);
#endif

    char date_str[16];
    std::strftime(date_str, sizeof(date_str), "%Y-%m-%d", &local_tm);
    std::string current_date = date_str;

    // 如果日期变化或文件未打开，则切换日志文件
    if (current_date != m_currentDate || !m_logFile.is_open()) {
        m_currentDate = current_date;
        // 关闭当前文件(如果已打开)
        if (m_logFile.is_open()) {
            m_logFile.close();
        }

        // 确保log目录存在
        createLogDirectory();

        // 生成新的日志文件
        std::string filename = "log/" + current_date + "_" + m_fileName + ".txt";
        // 以追加模式打开，确保UTF-8编码写入
        m_logFile.open(filename, std::ios::app | std::ios::out);

        if (!m_logFile.is_open()) {
            std::cerr << "无法打开日志文件: " << filename << std::endl;
        }
    }
}

void Logger::log(LogLevel level, const std::string& file, int line, const char* format, ...) {
    std::lock_guard<std::mutex> lock(m_mtx);

    // 检查是否需要切换日志文件
    checkAndSwitchLogFile();

    if (!m_logFile.is_open()) {
        return;
    }

    // 获取当前时间
    std::string timeStr = getCurrentTime();

    // 获取日志级别字符串
    std::string levelStr = levelToString(level);

    // 格式化日志消息
    va_list args;
    va_start(args, format);

    // 先计算消息所需大小
    int msgSize = vsnprintf(nullptr, 0, format, args) + 1;
    va_end(args);

    // 分配缓冲区并格式化消息
    char* msgBuffer = new char[msgSize];
    va_start(args, format);
    vsnprintf(msgBuffer, msgSize, format, args);
    va_end(args);

    std::string message(msgBuffer);
    delete[] msgBuffer;

    // 获取文件名(去掉路径部分)
    size_t lastSlash = file.find_last_of("/\\");
    std::string fileName = (lastSlash == std::string::npos) ? file : file.substr(lastSlash + 1);

    // 构建日志行
    std::string logLine = "[" + timeStr + " " + levelStr + " " + fileName + ":" + std::to_string(line) + "] " + message + "\n";

    // 写入日志文件
    m_logFile << logLine;
    m_logFile.flush();  // 强制刷新，确保日志及时写入

    // 同时输出到控制台
    std::cout << logLine;
}