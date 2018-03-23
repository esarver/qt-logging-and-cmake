#include <signal.h>

#include <QtCore>

#include <Common/Logger/LogManager.h>
#include <Common/Logger/ConsoleLogger.h>
#include <Common/Logger/FileLogger.h>

static void SignalHandler(int sig) {
  bool handled = false;
  QString signal_name;

  switch (sig) {
    case SIGINT: // a.k.a. Ctrl-C
      signal_name = "Interrupt";
      handled = true;
      break;
    case SIGHUP:
      signal_name = "Hang-up";
      handled = true;
      break;
    case SIGTERM:
      signal_name = "Terminate";
      handled = true;
      break;
    case SIGPIPE:
      signal_name = "Broken Pipe";
      handled = true;
      break;
    case SIGSEGV:
      signal_name = "Segmentation Fault";
      handled = false;
      break;
    default:
      signal_name = "<unhandled>";
      handled = false;
      break;
  } // end switch on signal

  qCCritical(system,
          "PetAcq exiting on signal %d (%s)...\n",
          sig, qPrintable(signal_name));

  if (handled) {
    QCoreApplication::quit();
  }
} // signal_handler

bool Initialize() {
   // Initialize signal handlers
   signal(SIGINT, SignalHandler);
   signal(SIGHUP, SignalHandler);
   signal(SIGTERM, SignalHandler);
   signal(SIGPIPE, SignalHandler);
   
   // Initialize Logging
   qInstallMessageHandler(LogManager::LogMessageHandler);

   LogManager* log_manager = LogManager::GetInstance();

   log_manager->AddLogger(ConsoleLogger::GetInstance());
   log_manager->AddLogger(FileLogger::GetBaseInstance());
   return true;
} // Initialize

int main(int argc, char * argv[]) {
   QCoreApplication app(argc, argv);

   if (!Initialize()) {
      exit(EXIT_FAILURE);
   }

   app.exec();
}
