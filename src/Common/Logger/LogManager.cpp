/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LogManager.cpp
 * Author: Edwin Sarver
 * 
 * Created on June 30, 2017, 3:12 PM
 */

#include "LogManager.h"

//Logging category definitions

Q_LOGGING_CATEGORY(acq, "acq")
Q_LOGGING_CATEGORY(diag, "diag")
Q_LOGGING_CATEGORY(socket, "sock")
Q_LOGGING_CATEGORY(util, "util")
Q_LOGGING_CATEGORY(system, "sys")

bool LogManager::initialized_ = false;
LogManager* LogManager::instance_ = new LogManager();

void LogManager::LogMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
   switch (type) {
      case QtMsgType::QtDebugMsg:
         emit LogManager::GetInstance()->DebugLog("DBG", context, msg);
         break;
      case QtMsgType::QtInfoMsg:
         emit LogManager::GetInstance()->InfoLog("INF", context, msg);
         break;
      case QtMsgType::QtWarningMsg:
         emit LogManager::GetInstance()->WarningLog("WRN", context, msg);
         break;
      case QtMsgType::QtCriticalMsg:
         emit LogManager::GetInstance()->CriticalLog("ERR", context, msg);
         break;
      case QtMsgType::QtFatalMsg:
         emit LogManager::GetInstance()->FatalLog("FATAL", context, msg);
         break;
   }
}

LogManager::LogManager() {
//   connect(this, &LogManager::LoggerReconnect,
//           this, &LogManager::ReconnectLoggers);
//
//   connect(this, &LogManager::LogLevelChanged,
//           this, &LogManager::ChangeLogLevel);
//
//   connect(this, &LogManager::LoggerAdded,
//           this, &LogManager::AddLogger);
//
//   connect(this, &LogManager::LoggerRemoved,
//           this, &LogManager::RemoveLogger);
}

void LogManager::ClearLoggers(){
   for(auto logger : connected_loggers_){
      RemoveLogger(logger);
   }
}

void LogManager::ChangeLogLevel(QtMsgType level) {
   if (log_level_ != level) {
      log_level_ = level;

      //      emit LoggerReconnect();

      ReconnectLoggers();
      emit LogLevelChanged(log_level_);
   }
}

void LogManager::AddLogger(AbstractLogger * new_logger) {
   if (!connected_loggers_.contains(new_logger)) {
      connected_loggers_.append(new_logger);

      //      emit LoggerReconnect();
      ReconnectLoggers();
      LoggerAdded(new_logger);
   }
}

void LogManager::RemoveLogger(AbstractLogger* logger_to_remove) {
   if (connected_loggers_.contains(logger_to_remove)) {
      connected_loggers_.removeAll(logger_to_remove);

      //      emit LoggerReconnect();
      ReconnectLoggers();
      emit LoggerRemoved(logger_to_remove);
   }

}

void LogManager::ReconnectLoggers() {
   disconnect(LogManager::GetInstance(), 0, 0, 0);

   for (auto logger : connected_loggers_) {
      switch (log_level_) {
         case QtMsgType::QtFatalMsg:
            connect(LogManager::GetInstance(), &LogManager::FatalLog,
                    logger, &AbstractLogger::Log);
            break;

         case QtMsgType::QtCriticalMsg:
            connect(LogManager::GetInstance(), &LogManager::FatalLog,
                    logger, &AbstractLogger::Log);

            connect(LogManager::GetInstance(), &LogManager::CriticalLog,
                    logger, &AbstractLogger::Log);
            break;

         case QtMsgType::QtWarningMsg:
            connect(LogManager::GetInstance(), &LogManager::FatalLog,
                    logger, &AbstractLogger::Log);

            connect(LogManager::GetInstance(), &LogManager::CriticalLog,
                    logger, &AbstractLogger::Log);

            connect(LogManager::GetInstance(), &LogManager::WarningLog,
                    logger, &AbstractLogger::Log);
            break;

         case QtMsgType::QtInfoMsg:
            connect(LogManager::GetInstance(), &LogManager::FatalLog,
                    logger, &AbstractLogger::Log);

            connect(LogManager::GetInstance(), &LogManager::CriticalLog,
                    logger, &AbstractLogger::Log);

            connect(LogManager::GetInstance(), &LogManager::WarningLog,
                    logger, &AbstractLogger::Log);

            connect(LogManager::GetInstance(), &LogManager::InfoLog,
                    logger, &AbstractLogger::Log);
            break;

         case QtMsgType::QtDebugMsg:
            connect(LogManager::GetInstance(), &LogManager::FatalLog,
                    logger, &AbstractLogger::Log);

            connect(LogManager::GetInstance(), &LogManager::CriticalLog,
                    logger, &AbstractLogger::Log);

            connect(LogManager::GetInstance(), &LogManager::WarningLog,
                    logger, &AbstractLogger::Log);

            connect(LogManager::GetInstance(), &LogManager::InfoLog,
                    logger, &AbstractLogger::Log);

            connect(LogManager::GetInstance(), &LogManager::DebugLog,
                    logger, &AbstractLogger::Log);
            break;
      }
   }
   
   emit LoggerReconnect();
}

LogManager* LogManager::GetInstance() {
   if (!initialized_){
      instance_->Initialize();
   }
   
   return instance_;   
}

void LogManager::Initialize(){
   initialized_ = true;
}
