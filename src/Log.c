/**********************************************************************/
/* File : Log.c                                                     */
/* Date : 18/11/2023                                                 */
/* author : ShHaWkK                                                   */
/**********************************************************************/


#include "../include/Log.h"

static FILE* logFile = NULL;
static LogLevel currentLogLevel = LOG_INFO;

void Log_Init(const char* logFileName) {
    logFile = fopen(logFileName, "a");
    if (logFile == NULL) {
        printf("Error opening log file.\n");
    }
}

void Log(LogLevel level, const char* format, ...) {
    if (logFile == NULL || level < currentLogLevel) {
        return;
    }

    // Get the current time and format it
    char timeString[20];
    time_t currentTime = time(NULL);
    struct tm* timeInfo = localtime(&currentTime);
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeInfo);

    // Print the time and log level
    const char* levelString = (level == LOG_INFO) ? "INFO" : (level == LOG_WARNING) ? "WARNING" : "ERROR";
    fprintf(logFile, "[%s] [%s] ", timeString, levelString);

    // Print the formatted log message
    va_list args;
    va_start(args, format);
    vfprintf(logFile, format, args);
    va_end(args);

    fprintf(logFile, "\n");
    fflush(logFile);
}

void Log_Close() {
    if (logFile != NULL) {
        fclose(logFile);
        logFile = NULL;
    }
}

void Log_SetLevel(LogLevel level) {
    currentLogLevel = level;
}
