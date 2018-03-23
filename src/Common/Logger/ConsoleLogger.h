/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VeyronConsoleLogger.h
 * Author: veyron
 *
 * Created on June 30, 2017, 3:11 PM
 */

#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include <Common/Logger/AbstractLogger.h>

/**
 * @brief VeyronConsoleLogger is a singleton class that provides logging infrastructure to the console.
 */
class ConsoleLogger : public AbstractLogger {
   Q_OBJECT
public:

   static AbstractLogger* GetInstance();

public slots:

   /**
    * @brief Log the message with the given details to the console. This slot is to be connected to a logging signal.
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

private:
   ConsoleLogger() {
   }
   
   static ConsoleLogger * instance_;
};

#endif /* CONSOLELOGGER_H */

 
