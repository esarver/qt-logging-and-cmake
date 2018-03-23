add_library(
    Common-Logger 
    OBJECT 
    AbstractLogger.h 
    ConsoleLogger.cpp
    FileLogger.cpp
    LogManager.cpp
)

