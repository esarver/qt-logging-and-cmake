/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileLogger.h
 * Author: Edwin Sarver
 *
 * Created on June 30, 2017, 3:11 PM
 */

#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <Common/Logger/AbstractLogger.h>

/**
 * @brief ConsoleLogger is a singleton class that provides logging infrastructure to the File System.
 */
class FileLogger : public AbstractLogger {
   Q_OBJECT
public:

   static AbstractLogger* GetBaseInstance();
   
   static FileLogger* GetInstance();
   
public slots:

   /**
    * @brief Log the message with the given details to the proper file. This 
    * slot is to be connected to a logging signal.
    * 
    * @param type - The string name of the type of message (DEBUG, INFO, WARN, CRITICAL, or FATAL)
    * @param context - Information pertaining to the context in which the message was created.
    * @param msg - The text of the message to be output to the given medium.
    */
   void Log(QString type, const QMessageLogContext &context, const QString &msg);
   
   /**
    * @brief Configure this logger with 
    * @param config
    */
   void Config(ConfigurationManager &config);
   
   /**
    * @brief Change the directory in which logs are stored.
    * @param log_directory - The string containing the full or relative path to 
    * the log directory.
    */
   void SetLogDirectory(QString log_directory){
       log_directory_ = log_directory;
   }
   
   /**
    * @brief Get the currently set log directory.
    * @return The currently set log directory.
    */
   QString GetLogDirectory(){
       return log_directory_;
   }

private:

    /**
     * Hidden constructor for singleton.
     */
    FileLogger() {
    }
   
   QString log_directory_;
   
   static FileLogger * instance_;
};

#endif /* FILELOGGER_H */

 
