#include "FileLogger_Test.h"

Q_LOGGING_CATEGORY(filelogger_test, "filelogger_test")

const int FileLogger_Test::ACCEPTABLE_TIME_DIFF_ = 50;//ms

void FileLogger_Test::initTestCase(){
   qInstallMessageHandler(LogManager::LogMessageHandler);
   cleanup();
}

void FileLogger_Test::cleanup(){
   LogManager::GetInstance()->ClearLoggers();
   QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd");
   
   filelogger_test_log_ = CleanupLogFiles(QString("%1_%2.log").arg("filelogger_test", qPrintable(date)));
   acq_log_ = CleanupLogFiles(QString("%1_%2.log").arg("acq", qPrintable(date)));
   diag_log_ = CleanupLogFiles(QString("%1_%2.log").arg("diag", qPrintable(date)));
   sock_log_ = CleanupLogFiles(QString("%1_%2.log").arg("sock", qPrintable(date)));
   util_log_ = CleanupLogFiles(QString("%1_%2.log").arg("util", qPrintable(date)));
   sys_log_ = CleanupLogFiles(QString("%1_%2.log").arg("sys", qPrintable(date)));
}

QFile* FileLogger_Test::CleanupLogFiles(QString filepath){
   QFileInfo log_info(filepath);
   QFile* log = new QFile(log_info.filePath());
   if(log_info.exists() && log_info.isFile()){
      log->remove();
   }
   log->close();
   return log;
}

QList<LogMessage>* FileLogger_Test::parseLogFile(QFile* file) {
   file->open(QIODevice::ReadOnly);
   QTextStream in(file);
   
   QList<LogMessage>* parsed_file = new QList<LogMessage>();
   
   while( !in.atEnd())
   {
      QString line = in.readLine();
      //std::cout << "Input: \"" << qPrintable(line) << "\"" << std::endl;
      QRegularExpression rx ("^(?<time>.*)"
      "\\ \\|\\ \\<"
      "(?<function>.*)"
      "\\>\\ \\["
      "(?<type>.*)"
      "\\:"
      "(?<category>.*)"
      "\\]\\:\\s{1,}"
      "(?<message>.*)"
      "\\s{0,}"); // end line
      
      QRegularExpressionMatch match = rx.match(line);
      LogMessage log_message;
      if(match.hasMatch()) {
         log_message.time_ = match.captured("time");
         log_message.function_name_ = match.captured("function");
         log_message.type_ = match.captured("type");
         log_message.category_ = match.captured("category");
         log_message.message_ = match.captured("message");

      } else {
         std::cout << "No match found..." << std::endl;
      }
      parsed_file->append(log_message);     
   }
   file->close();
   return parsed_file;
}

void FileLogger_Test::File_DebugLevel_Test(){
   LogManager* log_manager = LogManager::GetInstance();
   log_manager->AddLogger(FileLogger::GetInstance());
   
   // Test Debug level (lowest level, all messages)
   LogManager::GetInstance()->ChangeLogLevel(QtMsgType::QtDebugMsg);
   qCDebug(filelogger_test, "Test Debug Message");
   qCDebug(acq, "Test Debug Message");
   qCInfo(diag, "Test Info Message");
   qCCritical(socket, "Test Critical Message");
   
   QList<LogMessage>* filelogger_test_log_parsed = parseLogFile(filelogger_test_log_);
   
   QCOMPARE(filelogger_test_log_parsed->count(), 1);
   for(LogMessage message : *filelogger_test_log_parsed){
      QTime log_time = QTime::fromString(message.time_, "HH:mm:ss:zzz");
      int msecs_from_log_time = log_time.msecsTo(QTime::currentTime());
      
      QString explanation = QString("Time in file was %1 ms, which was outside the %2 ms acceptable range.").arg(
         qPrintable(QString::number(msecs_from_log_time)),
         qPrintable(QString::number(ACCEPTABLE_TIME_DIFF_)));
      
      QVERIFY2(msecs_from_log_time < ACCEPTABLE_TIME_DIFF_, qPrintable(explanation) );
      QCOMPARE(qPrintable(message.function_name_), "void FileLogger_Test::File_DebugLevel_Test()");
      QCOMPARE(qPrintable(message.type_), "DBG");
      QCOMPARE(qPrintable(message.category_), "filelogger_test");
      QCOMPARE(qPrintable(message.message_), "Test Debug Message");
   }
   
   QList<LogMessage>* acq_log_parsed = parseLogFile(acq_log_);
   
   QCOMPARE(acq_log_parsed->count(), 1);
   for(LogMessage message : *acq_log_parsed){
      QTime log_time = QTime::fromString(message.time_, "HH:mm:ss:zzz");
      int msecs_from_log_time = log_time.msecsTo(QTime::currentTime());
      
      QString explanation = QString("Time in file was %1 ms, which was outside the %2 ms acceptable range.").arg(
         qPrintable(QString::number(msecs_from_log_time)),
         qPrintable(QString::number(ACCEPTABLE_TIME_DIFF_)));
      
      QVERIFY2(msecs_from_log_time < ACCEPTABLE_TIME_DIFF_, qPrintable(explanation) );
      QCOMPARE(qPrintable(message.function_name_), "void FileLogger_Test::File_DebugLevel_Test()");
      QCOMPARE(qPrintable(message.type_), "DBG");
      QCOMPARE(qPrintable(message.category_), "acq");
      QCOMPARE(qPrintable(message.message_), "Test Debug Message");
   }
   
   QList<LogMessage>* diag_log_parsed = parseLogFile(diag_log_);
   
   QCOMPARE(diag_log_parsed->count(), 1);
   for(LogMessage message : *diag_log_parsed){
      QTime log_time = QTime::fromString(message.time_, "HH:mm:ss:zzz");
      int msecs_from_log_time = log_time.msecsTo(QTime::currentTime());
      
      QString explanation = QString("Time in file was %1 ms, which was outside the %2 ms acceptable range.").arg(
         qPrintable(QString::number(msecs_from_log_time)),
         qPrintable(QString::number(ACCEPTABLE_TIME_DIFF_)));
      
      QVERIFY2(msecs_from_log_time < ACCEPTABLE_TIME_DIFF_, qPrintable(explanation) );
      QCOMPARE(qPrintable(message.function_name_), "void FileLogger_Test::File_DebugLevel_Test()");
      QCOMPARE(qPrintable(message.type_), "INF");
      QCOMPARE(qPrintable(message.category_), "diag");
      QCOMPARE(qPrintable(message.message_), "Test Info Message");
   }
   
   QList<LogMessage>* sock_log_parsed = parseLogFile(sock_log_);
   
   QCOMPARE(sock_log_parsed->count(), 1);
   for(LogMessage message : *sock_log_parsed){
      QTime log_time = QTime::fromString(message.time_, "HH:mm:ss:zzz");
      int msecs_from_log_time = log_time.msecsTo(QTime::currentTime());
      
      QString explanation = QString("Time in file was %1 ms, which was outside the %2 ms acceptable range.").arg(
         qPrintable(QString::number(msecs_from_log_time)),
         qPrintable(QString::number(ACCEPTABLE_TIME_DIFF_)));
      
      QVERIFY2(msecs_from_log_time < ACCEPTABLE_TIME_DIFF_, qPrintable(explanation) );
      QCOMPARE(qPrintable(message.function_name_), "void FileLogger_Test::File_DebugLevel_Test()");
      QCOMPARE(qPrintable(message.type_), "ERR");
      QCOMPARE(qPrintable(message.category_), "sock");
      QCOMPARE(qPrintable(message.message_), "Test Critical Message");
   }
   
   QList<LogMessage>* sys_log_parsed = parseLogFile(sys_log_);
   
   QCOMPARE(sys_log_parsed->count(), 0);
}

void FileLogger_Test::File_InfoLevel_Test(){
   LogManager* log_manager = LogManager::GetInstance();
   log_manager->AddLogger(FileLogger::GetInstance());

   // Test Info level
   LogManager::GetInstance()->ChangeLogLevel(QtMsgType::QtInfoMsg);
   qCDebug(acq, "Test Debug Message"); //skipped
   qCInfo(diag, "Test Info Message");
   qCCritical(socket, "Test Critical Message");
   
   QList<LogMessage>* acq_log_parsed = parseLogFile(acq_log_);
   
   QCOMPARE(acq_log_parsed->count(), 0);
   
   QList<LogMessage>* diag_log_parsed = parseLogFile(diag_log_);
   
   QCOMPARE(diag_log_parsed->count(), 1);
   for(LogMessage message : *diag_log_parsed){
      QTime log_time = QTime::fromString(message.time_, "HH:mm:ss:zzz");
      int msecs_from_log_time = log_time.msecsTo(QTime::currentTime());
      
      QString explanation = QString("Time in file was %1 ms, which was outside the %2 ms acceptable range.").arg(
         qPrintable(QString::number(msecs_from_log_time)),
         qPrintable(QString::number(ACCEPTABLE_TIME_DIFF_)));
      
      QVERIFY2(msecs_from_log_time < ACCEPTABLE_TIME_DIFF_, qPrintable(explanation) );
      QCOMPARE(qPrintable(message.function_name_), "void FileLogger_Test::File_InfoLevel_Test()");
      QCOMPARE(qPrintable(message.type_), "INF");
      QCOMPARE(qPrintable(message.category_), "diag");
      QCOMPARE(qPrintable(message.message_), "Test Info Message");
   }
   
   QList<LogMessage>* sock_log_parsed = parseLogFile(sock_log_);
   
   QCOMPARE(sock_log_parsed->count(), 1);
   for(LogMessage message : *sock_log_parsed){
      QTime log_time = QTime::fromString(message.time_, "HH:mm:ss:zzz");
      int msecs_from_log_time = log_time.msecsTo(QTime::currentTime());
      
      QString explanation = QString("Time in file was %1 ms, which was outside the %2 ms acceptable range.").arg(
         qPrintable(QString::number(msecs_from_log_time)),
         qPrintable(QString::number(ACCEPTABLE_TIME_DIFF_)));
      
      QVERIFY2(msecs_from_log_time < ACCEPTABLE_TIME_DIFF_, qPrintable(explanation) );
      QCOMPARE(qPrintable(message.function_name_), "void FileLogger_Test::File_InfoLevel_Test()");
      QCOMPARE(qPrintable(message.type_), "ERR");
      QCOMPARE(qPrintable(message.category_), "sock");
      QCOMPARE(qPrintable(message.message_), "Test Critical Message");
   }
   
   QList<LogMessage>* sys_log_parsed = parseLogFile(sys_log_);
   
   QCOMPARE(sys_log_parsed->count(), 0);
}

void FileLogger_Test::File_WarningLevel_Test(){
   LogManager* log_manager = LogManager::GetInstance();
   log_manager->AddLogger(FileLogger::GetInstance());

   // Test Warning level
   LogManager::GetInstance()->ChangeLogLevel(QtMsgType::QtWarningMsg);
   qCDebug(acq, "Test Debug Message"); //skipped
   qCInfo(diag, "Test Info Message"); //skipped
   qCCritical(socket, "Test Critical Message");
   
   QList<LogMessage>* acq_log_parsed = parseLogFile(acq_log_);
   
   QCOMPARE(acq_log_parsed->count(), 0);
   
   QList<LogMessage>* diag_log_parsed = parseLogFile(diag_log_);
   
   QCOMPARE(diag_log_parsed->count(), 0);
   
   QList<LogMessage>* sock_log_parsed = parseLogFile(sock_log_);
   
   QCOMPARE(sock_log_parsed->count(), 1);
   for(LogMessage message : *sock_log_parsed){
      QTime log_time = QTime::fromString(message.time_, "HH:mm:ss:zzz");
      int msecs_from_log_time = log_time.msecsTo(QTime::currentTime());
      
      QString explanation = QString("Time in file was %1 ms, which was outside the %2 ms acceptable range.").arg(
         qPrintable(QString::number(msecs_from_log_time)),
         qPrintable(QString::number(ACCEPTABLE_TIME_DIFF_)));
      
      QVERIFY2(msecs_from_log_time < ACCEPTABLE_TIME_DIFF_, qPrintable(explanation) );
      QCOMPARE(qPrintable(message.function_name_), "void FileLogger_Test::File_WarningLevel_Test()");
      QCOMPARE(qPrintable(message.type_), "ERR");
      QCOMPARE(qPrintable(message.category_), "sock");
      QCOMPARE(qPrintable(message.message_), "Test Critical Message");
   }
   
   QList<LogMessage>* sys_log_parsed = parseLogFile(sys_log_);
   
   QCOMPARE(sys_log_parsed->count(), 0);
}

void FileLogger_Test::File_CriticalLevel_Test(){
   LogManager* log_manager = LogManager::GetInstance();
   log_manager->AddLogger(FileLogger::GetInstance());

   // Test Critical level (highest level, only Critical messages)
   LogManager::GetInstance()->ChangeLogLevel(QtMsgType::QtCriticalMsg);
   qCDebug(acq, "Test Debug Message"); //skipped
   qCInfo(diag, "Test Info Message"); //skipped
   qCCritical(socket, "Test Critical Message");
   
QList<LogMessage>* acq_log_parsed = parseLogFile(acq_log_);
   
   QCOMPARE(acq_log_parsed->count(), 0);
   
   QList<LogMessage>* diag_log_parsed = parseLogFile(diag_log_);
   
   QCOMPARE(diag_log_parsed->count(), 0);
   
   QList<LogMessage>* sock_log_parsed = parseLogFile(sock_log_);
   
   QCOMPARE(sock_log_parsed->count(), 1);
   for(LogMessage message : *sock_log_parsed){
      QTime log_time = QTime::fromString(message.time_, "HH:mm:ss:zzz");
      int msecs_from_log_time = log_time.msecsTo(QTime::currentTime());
      
      QString explanation = QString("Time in file was %1 ms, which was outside the %2 ms acceptable range.").arg(
         qPrintable(QString::number(msecs_from_log_time)),
         qPrintable(QString::number(ACCEPTABLE_TIME_DIFF_)));
      
      QVERIFY2(msecs_from_log_time < ACCEPTABLE_TIME_DIFF_, qPrintable(explanation) );
      QCOMPARE(qPrintable(message.function_name_), "void FileLogger_Test::File_CriticalLevel_Test()");
      QCOMPARE(qPrintable(message.type_), "ERR");
      QCOMPARE(qPrintable(message.category_), "sock");
      QCOMPARE(qPrintable(message.message_), "Test Critical Message");
   }
   
   QList<LogMessage>* sys_log_parsed = parseLogFile(sys_log_);
   
   QCOMPARE(sys_log_parsed->count(), 0);
}

QTEST_MAIN(FileLogger_Test)
