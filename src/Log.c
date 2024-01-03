#include "../include/Log.h"
#include "../include/include.h"

static FILE* logFile = NULL;

void Log_Init(const char* logFileName) {
    logFile = fopen(logFileName, "a");
    if (logFile == NULL) {
        printf("Erreur lors de l'ouverture du fichier de log.\n");
    }
}

void Log(LogLevel level, const char* format, ...) {
    if (logFile == NULL) {
        return;
    }

    // Obtenir la date et l'heure actuelles
    time_t currentTime;
    struct tm* timeInfo;
    char timeString[20];
    time(&currentTime);
    timeInfo = localtime(&currentTime);
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeInfo);

    // Écrire la date et l'heure dans le fichier de log
    fprintf(logFile, "[%s] ", timeString);

    // Écrire le niveau de log dans le fichier de log
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

    // Écrire le message de log formaté dans le fichier de log
    va_list args;
    va_start(args, format);
    vfprintf(logFile, format, args);
    va_end(args);

    // Saut de ligne pour le prochain message
    fprintf(logFile, "\n");
    fflush(logFile);  // Assurer que le message est écrit immédiatement
}

LogLevel currentLogLevel = LOG_INFO;

void Log_SetLevel(LogLevel level) {
    currentLogLevel = level;
}

void Log_Close() {
    if (logFile != NULL) {
        fclose(logFile);
    }
}
