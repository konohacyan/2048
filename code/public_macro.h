#ifndef PUBLIC_MACRO_H
#define PUBLIC_MACRO_H

// #include "../easyloggingpp/easylogging++.h"

#define VERSION_NUMBER  "0.2"    //当前版本号

#define YEAR ((((__DATE__ [7] - '0') * 10 + (__DATE__ [8] - '0')) * 10 \
    + (__DATE__ [9] - '0')) * 10 + (__DATE__ [10] - '0'))
#define MONTH (__DATE__ [2] == 'n' ? (__DATE__ [1] == 'a' ? 0 : 5)  \
    : __DATE__ [2] == 'b' ? 1 \
    : __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? 2 : 3) \
    : __DATE__ [2] == 'y' ? 4 \
    : __DATE__ [2] == 'l' ? 6 \
    : __DATE__ [2] == 'g' ? 7 \
    : __DATE__ [2] == 'p' ? 8 \
    : __DATE__ [2] == 't' ? 9 \
    : __DATE__ [2] == 'v' ? 10 : 11)
#define DAY ((__DATE__ [4] == ' ' ? 0 : __DATE__ [4] - '0') * 10 \
    + (__DATE__ [5] - '0'))

/*
// 日志初始化
#define ELOG_INIT(logName) \
do { \
            el::Helpers::installCustomFormatSpecifier(el::CustomFormatSpecifier("%process", GetProcessIdAsString)); \
            el::Configurations conf; \
            conf.setGlobally(el::ConfigurationType::Format, "[%datetime] %process %fbase:%line %level - %msg"); \
            QDateTime currentDateTime = QDateTime::currentDateTime(); \
            QDir logDir("./log"); \
            if (!logDir.exists()) { \
                if (!logDir.mkpath(".")) { \
                    qDebug() << "创建目录失败"; \
                    break; \
        } \
    } \
            QString logFileName =  "./log/" + currentDateTime.toString("yyyyMMdd") + "_" + (logName) + ".log"; \
            conf.setGlobally(el::ConfigurationType::Filename, logFileName.toUtf8().constData()); \
            el::Loggers::reconfigureAllLoggers(conf); \
            el::Loggers::addFlag(el::LoggingFlag::AutoSpacing); \
} while(0)

// 信息
#define ELOG_INFO(message)      LOG(INFO) << (std::string(message))
// 告警
#define ELOG_WARNING(message)   LOG(WARNING) << (std::string(message))
// 调试
#define ELOG_DEBUG(message)     LOG(DEBUG) << (std::string(message))
// 错误
#define ELOG_ERROR(message)     LOG(ERROR) << (std::string(message))
// 致命
#define ELOG_FATAL(message)     LOG(FATAL) << (std::string(message))
// 跟踪
#define ELOG_TRACE(message)     LOG(TRACE) << (std::string(message))
*/

#endif// PUBLIC_MACRO_H
