/**********************************************************************/
/* File : Log.c                                                     */
/* Date : 18/11/2023                                                 */
/* author : ShHaWkK                                                   */
/**********************************************************************/


#include "../include/Log.h"
#include "../include/include.h"
#include <string.h>

static FILE* logFile = NULL;
static char lastLoggedMessage[1024] = {0};
LogLevel currentLogLevel = LOG_INFO;
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

    // Obtenir la date et l'heure actuelles
    time_t currentTime;
    struct tm* timeInfo;
    char timeString[20];
    time_t currentTime = time(NULL);
    struct tm* timeInfo = localtime(&currentTime);
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeInfo);

    fprintf(logFile, "[%s] ", timeString);

    switch (level) {
        case LOG_INFO:
            fprintf(logFile, "[INFO] ");
            break;
        case LOG_WARNING:
            fprintf(logFile, "[WARNING] ");
            break;
        case LOG_ERROR:
            fprintf(logFile, "[ERROR] ");
            break;
    }

    fprintf(logFile, "%s\n", newMessage);
    fflush(logFile);
}

void Log_SetLevel(LogLevel level) {
    currentLogLevel = level;
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
