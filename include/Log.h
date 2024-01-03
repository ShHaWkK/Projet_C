#ifndef LOG_H
#define LOG_H

#include "include.h"

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

void Log_Init(const char* logFileName);
void Log(LogLevel level, const char* format, ...);
void Log_Close();


void Log_SetLevel(LogLevel level);
extern LogLevel currentLogLevel;

#endif // LOG_H
