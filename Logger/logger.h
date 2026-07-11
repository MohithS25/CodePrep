#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stddef.h>

typedef enum {
    LOG_MODE_SYNC,
    LOG_MODE_ASYNC
} LogMode;

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} LogLevel;

typedef struct Logger Logger;

// Initializes the logger. If filepath is NULL, default to stdout (and ignore rotation).
Logger* logger_create(const char* filepath, LogLevel min_level, size_t max_file_size_bytes, LogMode mode);
void logger_destroy(Logger* logger);

void logger_log(Logger* logger, LogLevel level, const char* file, int line, const char* fmt, ...);

#define LOG_D(logger, fmt, ...) logger_log(logger, LOG_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_I(logger, fmt, ...) logger_log(logger, LOG_INFO,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_W(logger, fmt, ...) logger_log(logger, LOG_WARN,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_E(logger, fmt, ...) logger_log(logger, LOG_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif // LOGGER_H