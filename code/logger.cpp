#include "logger.h"
#include <QDebug>

QtLogger* QtLogger::instance = nullptr;

QtLogger::QtLogger(const QString& logName, QObject* parent)
    : QObject(parent), m_logName(logName) {
    ensureLogDirectory();
    checkAndSwitchLogFile();
}

QtLogger::~QtLogger() {
    if (m_logFile.isOpen()) {
        m_logFile.close();
    }
}

QtLogger* QtLogger::getInstance(const QString& logName) {
    static QMutex instanceMutex;
    QMutexLocker lock(&instanceMutex);

    if (!instance) {
        instance = new QtLogger(logName, QCoreApplication::instance());
    } else if (!logName.isEmpty() && instance->m_logName != logName) {
        delete instance;
        instance = new QtLogger(logName, QCoreApplication::instance());
    }

    return instance;
}

QString QtLogger::getCurrentTime() const {
    return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
}

QString QtLogger::levelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::DEBUG:   return "DEBUG";
        case LogLevel::INFO:    return "INFO ";
        case LogLevel::WARNING: return "WARN ";
        case LogLevel::ERROR_:  return "ERROR";
        case LogLevel::FATAL:   return "FATAL";
        default:                return "UNKNOWN";
    }
}

void QtLogger::ensureLogDirectory() const {
    QDir logDir("logs");
    if (!logDir.exists()) {
        if (!logDir.mkpath(".")) {
            qWarning() << "Failed to create log directory";
        }
    }
}

void QtLogger::checkAndSwitchLogFile() {
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");

    if (currentDate != m_currentDate || !m_logFile.isOpen()) {
        QMutexLocker lock(&m_mutex);
        m_currentDate = currentDate;

        if (m_logFile.isOpen()) {
            m_logFile.close();
        }

        ensureLogDirectory();

        QString fileName = QString("logs/%1_%2.log").arg(currentDate).arg(m_logName);
        m_logFile.setFileName(fileName);

        if (!m_logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            qWarning() << "Cannot open log file:" << fileName;
            return;
        }
    }
}

void QtLogger::log(LogLevel level, const char* file, int line, const QString& message) {
    QMutexLocker lock(&m_mutex);
    checkAndSwitchLogFile();

    if (!m_logFile.isOpen()) {
        return;
    }

    // 提取文件名（不含路径）
    QString fileName = QFileInfo(file).fileName();
    QString logLine = QString("[%1 %2 %3:%4] %5\n")
                              .arg(getCurrentTime())
                              .arg(levelToString(level))
                              .arg(fileName)
                              .arg(line)
                              .arg(message);

    QTextStream stream(&m_logFile);
    stream << logLine;
    stream.flush();

    // 同时输出到控制台（Qt内部已处理线程安全）
    qDebug().noquote() << logLine.trimmed();

    if (level == LogLevel::FATAL) {
        abort();
    }
}
