/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConfigurationManager.h
 * Author: veyron
 *
 * Created on December 20, 2017, 4:20 PM
 */

#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

#include <QtCore>

//TODO - Use QSetting to manage settings files. Each setting should be a member QVariant with a signal. Any class which depends on that property will have a slot to handle the change.


class ConfigurationManager : public QObject{
   Q_OBJECT
public slots:
   
signals:
   void ConfigChanged(ConfigurationManager * config);

   protected:
      ConfigurationManager(){}
   
   
   private:

};

#endif /* CONFIGURATIONMANAGER_H */

