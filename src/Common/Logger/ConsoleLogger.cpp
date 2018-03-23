/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VeyronConsoleLogger.cpp
 * Author: veyron
 * 
 * Created on June 30, 2017, 3:11 PM
 */

#include "ConsoleLogger.h"

ConsoleLogger * ConsoleLogger::instance_ = Q_NULLPTR;

AbstractLogger * ConsoleLogger::GetInstance() {
    if(!instance_){
         instance_ = new ConsoleLogger();
      }
   return instance_;
}

void ConsoleLogger::Log(QString type, const QMessageLogContext &context, const QString &msg) {
   QFileInfo file_info(context.file);
   
   printf("%s | <%s:%d> [%s:%s]:\t%s\n",
           qPrintable(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")),
           qPrintable(file_info.fileName()),
           context.line,
           qPrintable(type),
           context.category,
           qPrintable(msg));
} 

void ConsoleLogger::Config(ConfigurationManager &config){
   
}
