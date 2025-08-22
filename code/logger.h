#pragma once

#include <string>
#include <fstream>
#include <mutex>
#include <chrono>
#include <ctime>

// 日志级别枚举
enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR_,
    FATAL
};

class Logger {
private:
    // 单例实例
    static Logger* instance;
    // 日志文件流
    std::ofstream m_logFile;
    // 当前日期
    std::string m_currentDate;
    // 当前日志文件名
    std::string m_currentFileName;
    // 互斥锁保证线程安全
    std::mutex m_mtx;
    // 基础文件名
    std::string m_fileName;
    // 私有构造函数确保单例
    Logger(const std::string& fileName);
    // 析构函数
    ~Logger();

    // 获取当前时间字符串
    std::string getCurrentTime();
    // 将日志级别转换为字符串
    std::string levelToString(LogLevel level);
    // 创建日志目录
    void createLogDirectory();
    // 检查是否需要切换日志文件(按日期)
    void checkAndSwitchLogFile();

public:
    // 禁止拷贝构造和赋值
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // 获取单例实例
    static Logger* getInstance(const std::string& fileName = "log");

    // 写入日志
    void log(LogLevel level, const std::string& file, int line, const char* format, ...);
};

// 带文件名参数的日志宏
#define LOG_DEBUG(fileName, format, ...) Logger::getInstance(fileName)->log(LogLevel::DEBUG, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOG_INFO(fileName, format, ...)  Logger::getInstance(fileName)->log(LogLevel::INFO,  __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOG_WARN(fileName, format, ...)  Logger::getInstance(fileName)->log(LogLevel::WARNING,  __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOG_ERROR(fileName, format, ...) Logger::getInstance(fileName)->log(LogLevel::ERROR_, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOG_FATAL(fileName, format, ...) Logger::getInstance(fileName)->log(LogLevel::FATAL, __FILE__, __LINE__, format, ##__VA_ARGS__)