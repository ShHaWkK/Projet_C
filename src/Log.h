#ifndef LOG_H
#define LOG_H

// Enumération pour les niveaux de log
typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

// Fonction pour initialiser le système de log
void Log_Init(const char* logFileName);

// Fonction pour écrire un message de log
void Log(LogLevel level, const char* format, ...);

// Fonction pour fermer le système de log
void Log_Close();

#endif
