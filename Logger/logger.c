#include "logger.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>

#define ASYNC_QUEUE_CAPACITY 256
#define MAX_LOG_MESSAGE_LEN 512

// Structure representing a single pending log entry inside the async queue
typedef struct {
    LogLevel level;
    char file[128];
    int line;
    char message[MAX_LOG_MESSAGE_LEN];
    time_t timestamp;
} LogEntry;

struct Logger {
    FILE* file_stream;
    char* filepath;
    LogLevel min_level;
    LogMode mode;
    
    // Rotation & Sizing
    size_t max_size;
    size_t current_size;
    pthread_mutex_t stream_lock; // Protects file streams and size tracking

    // Asynchronous Machinery
    pthread_t worker_thread;
    bool is_running;
    
    // Thread-safe Ring Buffer
    LogEntry queue[ASYNC_QUEUE_CAPACITY];
    int head; // Read pointer for worker thread
    int tail; // Write pointer for application threads
    int count; // Number of populated slots
    pthread_mutex_t queue_lock;   // Protects buffer indices
    pthread_cond_t queue_not_empty; // Signals worker thread there is work
    pthread_cond_t queue_not_full;  // Signals app threads there is room
};

static const char* level_strings[] = { "[DEBUG]", "[INFO ]", "[WARN ]", "[ERROR]" };

// Forward declaration of the internal worker thread routine
static void* async_worker_routine(void* arg);
static void handle_rotation(Logger* logger);
static void write_to_stream(Logger* logger, LogLevel level, const char* file, int line, const char* msg, time_t ts);

Logger* logger_create(const char* filepath, LogLevel min_level, size_t max_file_size_bytes, LogMode mode) {
    Logger* logger = malloc(sizeof(Logger));
    if (!logger) return NULL;

    logger->min_level = min_level;
    logger->max_size = max_file_size_bytes;
    logger->current_size = 0;
    logger->filepath = NULL;
    logger->mode = mode;
    logger->head = 0;
    logger->tail = 0;
    logger->count = 0;
    logger->is_running = false;

    // TODO: Initialize both 'stream_lock' and 'queue_lock' mutexes.
    // TODO: Initialize 'queue_not_empty' and 'queue_not_full' condition variables.
    // Clean up and return NULL if any initialization fails.

    if (filepath) {
        logger->filepath = strdup(filepath);
        logger->file_stream = fopen(filepath, "a");
        if (!logger->file_stream) {
            // Clean up and return NULL
        }
        // Optional: Seek to end and determine current file size to resume tracking
    } else {
        logger->file_stream = stdout;
    }

    // Spin up background worker if Async mode is chosen
    if (logger->mode == LOG_MODE_ASYNC) {
        logger->is_running = true;
        if (pthread_create(&logger->worker_thread, NULL, async_worker_routine, logger) != 0) {
            logger->is_running = false;
            // TODO: Clean up resources and return NULL
        }
    }

    return logger;
}

void logger_destroy(Logger* logger) {
    if (!logger) return;

    if (logger->mode == LOG_MODE_ASYNC) {
        // TODO: Signal to the worker thread that it should stop running.
        // Remember to acquire queue_lock, set is_running to false, and broadcast condition signs.
        
        // TODO: Join the worker thread to guarantee it finishes draining the remaining queue.
        pthread_join(logger->worker_thread, NULL);
    }

    // TODO: Destroy all mutexes and condition variables.
    // TODO: Close file_stream safely (if it isn't stdout) and free filepath.
    free(logger);
}

static void handle_rotation(Logger* logger) {
    if (!logger->filepath || logger->current_size < logger->max_size) return;

    // TODO: 1. Close current file_stream.
    // TODO: 2. Construct a backup filename string (e.g., filepath + ".old").
    // TODO: 3. Use rename() to overwrite or create the .old backup file.
    // TODO: 4. Open a fresh file at original filepath in write mode, reset current_size.
}

// Low-level formatting logic used by either the calling thread (Sync) or worker thread (Async)
static void write_to_stream(Logger* logger, LogLevel level, const char* file, int line, const char* msg, time_t ts) {
    pthread_mutex_lock(&logger->stream_lock);

    handle_rotation(logger);

    struct tm* t = localtime(&ts);
    char time_buf[26];
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", t);

    // Track structural byte counts written to keep rotation accurate
    int header_bytes = fprintf(logger->file_stream, "%s %s [%s:%d]: ", time_buf, level_strings[level], file, line);
    int msg_bytes = fprintf(logger->file_stream, "%s\n", msg);
    
    if (header_bytes > 0) logger->current_size += header_bytes;
    if (msg_bytes > 0) logger->current_size += msg_bytes;

    fflush(logger->file_stream);

    pthread_mutex_unlock(&logger->stream_lock);
}

void logger_log(Logger* logger, LogLevel level, const char* file, int line, const char* fmt, ...) {
    if (!logger || level < logger->min_level) return;

    // Capture arguments and format string up-front
    char msg_buf[MAX_LOG_MESSAGE_LEN];
    va_list args;
    va_start(args, fmt);
    vsnprintf(msg_buf, sizeof(msg_buf), fmt, args);
    va_end(args);

    time_t now = time(NULL);

    if (logger->mode == LOG_MODE_SYNC) {
        write_to_stream(logger, level, file, line, msg_buf, now);
    } else {
        // TODO: ASYNC ROUTINE
        // 1. Acquire queue_lock.
        // 2. While the ring buffer is FULL (count == ASYNC_QUEUE_CAPACITY) and logger is_running, 
        //    wait on 'queue_not_full' condition.
        // 3. If logger stopped running while waiting, drop out.
        // 4. Push log data (level, file, line, formatted msg_buf, timestamp) into queue[tail].
        // 5. Update tail index (wrap around using modulo) and increment count.
        // 6. Signal 'queue_not_empty' condition and unlock queue_lock.
    }
}

static void* async_worker_routine(void* arg) {
    Logger* logger = (Logger*)arg;

    while (true) {
        LogEntry entry;
        bool have_entry = false;

        // TODO: LOCK BOUNDARY
        // 1. Acquire queue_lock.
        // 2. While queue is empty (count == 0) and logger is_running, wait on 'queue_not_empty'.
        // 3. If count > 0, extract item from queue[head], update head index, decrement count, 
        //    signal 'queue_not_full', and mark have_entry = true.
        // 4. Unlock queue_lock.
        
        // If queue was empty and logger stopped running, break loop to exit thread cleanly
        if (!logger->is_running && !have_entry) {
            break; 
        }

        if (have_entry) {
            write_to_stream(logger, entry.level, entry.file, entry.line, entry.message, entry.timestamp);
        }
    }

    return NULL;
}
