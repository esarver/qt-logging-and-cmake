/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LogManager.h
 * Author: Edwin Sarver
 *
 * Created on June 30, 2017, 3:12 PM
 */



#ifndef LOGMANAGER_H
#define LOGMANAGER_H


#include <QObject>

#include <Common/Logger/AbstractLogger.h>


//Logging Category declarations

Q_DECLARE_LOGGING_CATEGORY(acq)
Q_DECLARE_LOGGING_CATEGORY(diag)
Q_DECLARE_LOGGING_CATEGORY(socket)
Q_DECLARE_LOGGING_CATEGORY(util)
Q_DECLARE_LOGGING_CATEGORY(system)
/**
 * LogManager is a singleton class the manages the log-level and connected logging interfaces at runtime.
 */
class LogManager : public QObject {
   Q_OBJECT
public:
   /**
    * Routes the message of a Debug, Info, Warning, Critical, Fatal, or System log message to the correct signals.
    * @param type
    * @param context
    * @param msg
    */
   static void LogMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

   /**
    * Returns the static instance pointer of LogManager.
    * @return The singleton instance pointer of LogManager.
    */
   static LogManager* GetInstance();
   

public slots:
   /**
    * @brief Removes all of the loggers from the Log Manager.
    */
   void ClearLoggers();

   /**
    * @brief Changes the log level of the LogManager.
    * @param level - The new logging level.
    */
   void ChangeLogLevel(QtMsgType level);

   /**
    * Adds the given logger to the connected list.
    * @param new_logger - The logger to add to the LogManager
    */
   void AddLogger(AbstractLogger* new_logger);


   /**
    * Removes the given logger from the connected list.
    * @param logger_to_remove - Pointer to the logger to be removed.
    */
   void RemoveLogger(AbstractLogger* logger_to_remove);

signals:

   /**
    * This signal is emitted to cause a reconnection of all loggers and the current log level.
    */
   void LoggerReconnect();

   /**
    * This signal is emitted whenever a user changes the log level.
    * @param level - new level at which to log.
    */
   void LogLevelChanged(QtMsgType level);

   /**
    * This signal is emitted whenever a user wishes to add a new logger interface.
    * @param new_logger - a pointer to the new logger (must be a subclass of AbstractLogger).
    */
   void LoggerAdded(AbstractLogger* new_logger);

   /**
    * This signal is emitted whenever a user wishes to add a new logger interface.
    * @param new_logger - a pointer to the new logger (must be a subclass of AbstractLogger).
    */
   void LoggerRemoved(AbstractLogger* logger_to_remove);

   /**
    * This signal is emitted whenever qCDebug or qDebug is called. 
    * @param type
    * @param context
    * @param msg
    */
   void DebugLog(QString type, const QMessageLogContext &context, const QString &msg);

   /**
    * This signal is emitted whenever qCInfo or qInfo is called. 
    * @param type
    * @param context
    * @param msg
    */
   void InfoLog(QString type, const QMessageLogContext &context, const QString &msg);

   /**
    * This signal is emitted whenever qCWarning or qWarning is called. 
    * @param type
    * @param context
    * @param msg
    */
   void WarningLog(QString type, const QMessageLogContext &context, const QString &msg);

   /**
    * This signal is emitted whenever qCCritical or qCritical is called. 
    * @param type
    * @param context
    * @param msg
    */
   void CriticalLog(QString type, const QMessageLogContext &context, const QString &msg);

   /**
    * This signal is emitted whenever qCFatal or qFatal is called. 
    * @param type
    * @param context
    * @param msg
    */
   void FatalLog(QString type, const QMessageLogContext &context, const QString &msg);

   /**
    * This signal is emitted whenever qCSystem or qSystem is called. 
    * @param type
    * @param context
    * @param msg
    */
   void SystemLog(QString type, const QMessageLogContext &context, const QString &msg);


private slots:

   /**
    * Reconnect all the current loggers at the current log levels.
    */
   void ReconnectLoggers();

private:
   /**
    * Private constructor for singleton.
    */
   LogManager();

   static void Initialize();

   QtMsgType log_level_ = QtMsgType::QtInfoMsg;
   QList<AbstractLogger*> connected_loggers_;

   static bool initialized_;
   static LogManager* instance_;

   

};

#endif /* LOGMANAGER_H */

