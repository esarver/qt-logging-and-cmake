#ifndef LOGGER_TEST_H
#define LOGGER_TEST_H

#include <QtTest>
#include <QFileInfo>
#include <Common/Logger/LogManager.h>
#include <Common/Logger/ConsoleLogger.h>
#include <Common/Logger/FileLogger.h>

#include <iostream>

Q_DECLARE_LOGGING_CATEGORY(filelogger_test)

struct LogMessage {
   QString time_;
   QString function_name_;
   QString type_;
   QString category_;
   QString message_;
};

/**
 * The Logger Test is an exception to the class-to-class relationship of unit
 * testing because there is not a good way to test the logger as individual 
 * parts. Each type of logger (file, console, database, etc.) will have it's own
 * set of tests and some tests mixed with the other tests. 
 * 
 * The Logger Tests ensure that all the expected information is logged in the 
 * expected locations when a Qt logging macro is called. This makes sure that 
 * changes to the system do not affect the overall logging performance. 
 */
class FileLogger_Test : public QObject {
    Q_OBJECT

/* All tests are defined as private slots.*/    
private slots:
    /**
     * Called at the beginning of the suite only.
     */
    void initTestCase();
    
    /**
     * Called before each individual test case.
     */
    void init(){}
    
    /**
     * Called after each individual test case.
     */
    void cleanup();
    
    /**
     * Called at the end of the suite only.
     */
    void cleanupTestCase(){}
    
    /**
     * Ensure the File logger logs all messages when the level is set to the "Debug" level. When it does
     * log, make sure the messages contain the correct information. 
     */
    void File_DebugLevel_Test(); 
    
    /**
     * Ensure the File logger logs all messages except "Debug" level messages when the level is set to the "Info" level. 
     * When it does log, make sure the messages contain the correct information. 
     */
    void File_InfoLevel_Test();
    
    /**
     * Ensure the File logger logs all messages except "Debug" and "Info" level messages when the level is set to the 
     * "Warning" level. When it does log, make sure the messages contain the correct information. 
     */
    void File_WarningLevel_Test();
    
    /**
     * Ensure the File logger only logs "Critical" level messages when the level is set to the "Critical" level. When 
     * it does log, make sure the messages contain the correct information. 
     */
    void File_CriticalLevel_Test();
    
    
 private:
    
    /**
     * Get rid of any latent log files that might confuse our tests.
     * @param filepath - the filepath (relative or absolute) of the file to be cleaned up.
     */
    QFile* CleanupLogFiles(QString filepath);
    
    /**
     * Parse all the log files into a list of <code>LogMessage</code> structs to make for easy checking.
     * @param file - a pointer to the file that is to be parsed.
     */
    QList<LogMessage>* parseLogFile(QFile* file);
    
    QFile* acq_log_;
    QFile* diag_log_;
    QFile* sock_log_;
    QFile* sys_log_;
    QFile* util_log_;
    QFile* filelogger_test_log_;
    
    static const int ACCEPTABLE_TIME_DIFF_;
};

#endif  /*LOGGER_TEST_H*/
