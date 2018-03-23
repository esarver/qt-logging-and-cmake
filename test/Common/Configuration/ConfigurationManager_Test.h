/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConfigurationManager_Test.h
 * Author: veyron
 *
 * Created on December 20, 2017, 4:21 PM
 */

#ifndef CONFIGURATIONMANAGER_TEST_H
#define CONFIGURATIONMANAGER_TEST_H

#include <QtTest>
#include <QFileInfo>
#include <Common/Configuration/ConfigurationManager.h>

class ConfigurationManager_Test : public QObject {
   Q_OBJECT
   
/* All tests are defined as private slots.*/    
private slots:
    /**
     * Called at the beginning of the suite only.
     */
    void initTestCase(){}
    
    /**
     * Called before each individual test case.
     */
    void init(){}
    
    /**
     * Called after each individual test case.
     */
    void cleanup(){}
    
    /**
     * Called at the end of the suite only.
     */
    void cleanupTestCase(){}

};

#endif /* CONFIGURATIONMANAGER_TEST_H */

