#pragma once

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>
#include <QMutexLocker>
#include <QCoreApplication>
#include <QDir>

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR_,
    FATAL
};

class QtLogger : public QObject {
    Q_OBJECT
private:
    static QtLogger* instance;
    QFile m_logFile;
    QString m_currentDate;
    QString m_logName;
    QMutex m_mutex;

    explicit QtLogger(const QString& logName = "2048", QObject* parent = nullptr);
    ~QtLogger();

    QString getCurrentTime() const;
    QString levelToString(LogLevel level) const;
    void ensureLogDirectory() const;
    void checkAndSwitchLogFile();

public:
    QtLogger(const QtLogger&) = delete;
    QtLogger& operator=(const QtLogger&) = delete;

    static QtLogger* getInstance(const QString& logName = "2048");
    void log(LogLevel level, const char* file, int line, const QString& message);
};

// 简化后的日志宏（无需每次指定日志名称）
#define LOG_DEBUG(format, ...) \
QtLogger::getInstance()->log(LogLevel::DEBUG, __FILE__, __LINE__, QString::asprintf(format, ##__VA_ARGS__))
#define LOG_INFO(format, ...) \
        QtLogger::getInstance()->log(LogLevel::INFO, __FILE__, __LINE__, QString::asprintf(format, ##__VA_ARGS__))
#define LOG_WARN(format, ...) \
        QtLogger::getInstance()->log(LogLevel::WARNING, __FILE__, __LINE__, QString::asprintf(format, ##__VA_ARGS__))
#define LOG_ERROR(format, ...) \
        QtLogger::getInstance()->log(LogLevel::ERROR_, __FILE__, __LINE__, QString::asprintf(format, ##__VA_ARGS__))
#define LOG_FATAL(format, ...) \
        QtLogger::getInstance()->log(LogLevel::FATAL, __FILE__, __LINE__, QString::asprintf(format, ##__VA_ARGS__))
