#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QPlainTextEdit>

class Logger
{
public:
    enum Level {
        Info,
        Warning,
        Error
    };
    
    static void log(const QString &message, Level level = Info);
    
    static void log(const QString &message, Level level, QPlainTextEdit *widget);
    
private:
    static QString levelToString(Level level);
};

// -------- 宏封装 --------
#define LOG_INFO(msg, widget)  Logger::log(QString(msg), Logger::Level::Info, widget)
#define LOG_WARN(msg, widget)  Logger::log(QString(msg), Logger::Level::Warning, widget)
#define LOG_ERROR(msg, widget) Logger::log(QString(msg), Logger::Level::Error, widget)

#endif // LOG_H
