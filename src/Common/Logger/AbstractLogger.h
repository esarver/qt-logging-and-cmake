/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AcqLogger.h
 * Author: Edwin Sarver
 *
 * Created on June 30, 2017, 3:10 PM
 */

#ifndef ABSTRACTLOGGER_H
#define ABSTRACTLOGGER_H

#include <QtCore>
#include <Common/Configuration/ConfigurationManager.h>

/**
 * @brief AcqLogger is the pure virtual base-class for logging interfaces.
 */
class AbstractLogger : public QObject {
   Q_OBJECT
public:

public slots:

   /**
    * @brief Log the message with the given details to the medium prescribed by the implementing class.
    * 
    * @param type - The string name of the type of message (DEBUG, INFO, WARN, CRITICAL, or FATAL)
    * @param context - Information pertaining to the context in which the message was created.
    * @param msg - The text of the message to be output to the given medium.
    */
   virtual void Log(QString type, const QMessageLogContext &context, const QString &msg) = 0;
   
   /**
    * @brief Configure the implementing logger with the appropriate configuration options.
    * 
    * @param config - The object that is controlling this class's configuration.
    */
   virtual void Config(ConfigurationManager &config) = 0;

protected:

   /**
    * @brief Hide the constructor from all except the base classes.
    */
   AbstractLogger() {};
};


#endif /* ABSTRACTLOGGER_H */

 
