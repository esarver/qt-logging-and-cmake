/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileLogger.cpp
 * Author: Edwin Sarver
 * 
 * Created on June 30, 2017, 3:11 PM
 */

#include "FileLogger.h"

FileLogger * FileLogger::instance_ = Q_NULLPTR;

AbstractLogger * FileLogger::GetBaseInstance() {
   if(!instance_){
         instance_ = new FileLogger();
      }
   return instance_;
}

FileLogger * FileLogger::GetInstance() {
   if(!instance_){
      instance_ = new FileLogger();
   }
   return instance_;
}

void FileLogger::Log(QString type, const QMessageLogContext &context, const QString &msg) {

   QString log_filename = QString("%1_%2.log").arg(
           context.category,
           qPrintable(QDateTime::currentDateTime().toString("yyyy-MM-dd")));

   QFile log_file(log_filename);

   QFileInfo file_info(context.file);

   QString message = QString("%1 | <%2> [%3:%4]:\t%5\n").arg(
           qPrintable(QTime::currentTime().toString("HH:mm:ss:zzz")),
           qPrintable(context.function),
           qPrintable(type),
           context.category,
           qPrintable(msg));

   if (log_file.open(QIODevice::Append)) {
      log_file.write(qPrintable(message));
   }

   log_file.close();
}

void FileLogger::Config(ConfigurationManager &config){
   
}

 
