#ifndef LOG_H
#define LOG_H

#include "include.h"
#include <time.h>

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

// Initializes the logging system.
void Log_Init(const char* logFileName);

// Logs a message at the given log level.
void Log(LogLevel level, const char* format, ...);

// Closes the logging system.
void Log_Close();

// Sets the current log level. Messages below this level will not be logged.
void Log_SetLevel(LogLevel level);

#endif // LOG_H
