#include "Log.h"

void Logger::log(const QString &message, Level level)
{
    QString timeStr = QDateTime::currentDateTime().toString("yyyy-M-d hh:mm:ss");
    QString logStr = QString("[%1] %2 %3")
                         .arg(timeStr, levelToString(level), message);
    
    qDebug().noquote() << logStr;   // noquote 避免多余的引号
}

void Logger::log(const QString &message,Level level,  QPlainTextEdit *widget)
{
    // QString timeStr = QDateTime::currentDateTime().toString("yyyy-M-d hh:mm:ss");
    QString timeStr = QDateTime::currentDateTime().toString("yyyy-M-d hh:mm:ss");
    QString logStr = QString("[%1] %2 %3")
                         .arg(timeStr, levelToString(level), message);
    
    widget->appendPlainText(logStr);
    
    //qDebug().noquote() << logStr;   // noquote 避免多余的引号
}

QString Logger::levelToString(Level level)
{
    switch (level) {
    case Info:    return "[INFO]";
    case Warning: return "[WARN]";
    case Error:   return "[ERROR]";
    }
    return "[UNKNOWN]";
}

