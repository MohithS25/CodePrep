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
    FILE* file_stream;                               //#file where log message written
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
    if (pthread_mutex_init(&logger->stream_lock, NULL) != 0){
        free(logger);
        return NULL;
    }
    if (pthread_mutex_init(&logger->queue_lock, NULL) != 0){
        pthread_mutex_destroy(&logger->stream_lock);
        free(logger);
        return NULL;
    }

    // TODO: Initialize 'queue_not_empty' and 'queue_not_full' condition variables.
    // Clean up and return NULL if any initialization fails.
    if (pthread_cond_init(&logger->queue_not_empty, NULL) != 0 ){
        pthread_mutex_destroy(&logger->queue_lock);
        pthread_mutex_destroy(&logger->stream_lock);
        free(logger);
        return NULL;
    }

    if (pthread_cond_init(&logger->queue_not_full, NULL) != 0 ){
        pthread_cond_destroy(&logger->queue_not_empty);
        pthread_mutex_destroy(&logger->queue_lock);
        pthread_mutex_destroy(&logger->stream_lock);
        free(logger);
        return NULL;
    }

    if (filepath) {
        logger->filepath = strdup(filepath);
        if(!logger->filepath){
            pthread_cond_destroy(&logger->queue_not_full);
            pthread_cond_destroy(&logger->queue_not_empty);
            pthread_mutex_destroy(&logger->queue_lock);
            pthread_mutex_destroy(&logger->stream_lock);
            free(logger);
            return NULL;
        }
        logger->file_stream = fopen(filepath, "a");
        if (!logger->file_stream) {
            // Clean up and return NULL
            free(logger->filepath);
            pthread_cond_destroy(&logger->queue_not_full);
            pthread_cond_destroy(&logger->queue_not_empty);
            pthread_mutex_destroy(&logger->queue_lock);
            pthread_mutex_destroy(&logger->stream_lock);
            free(logger);
            return NULL;
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
            if (logger->file_stream != stdout) {
                fclose(logger->file_stream);
            }
            free(logger->filepath);
            pthread_cond_destroy(&logger->queue_not_full);
            pthread_cond_destroy(&logger->queue_not_empty);
            pthread_mutex_destroy(&logger->queue_lock);
            pthread_mutex_destroy(&logger->stream_lock);
            free(logger);
            return NULL;
        }
    }
    printf("Logger created\n");
    return logger;
}

void logger_destroy(Logger* logger) {
    if (!logger) return;

    if (logger->mode == LOG_MODE_ASYNC) {
        // TODO: Signal to the worker thread that it should stop running.
        // Remember to acquire queue_lock, set is_running to false, and broadcast condition signs.
        pthread_mutex_lock(&logger->queue_lock);
        
        logger->is_running = false;
        pthread_cond_broadcast(&logger->queue_not_empty);
        pthread_cond_broadcast(&logger->queue_not_full);
        
        pthread_mutex_unlock(&logger->queue_lock);

        // TODO: Join the worker thread to guarantee it finishes draining the remaining queue.
        pthread_join(logger->worker_thread, NULL);
    }

    // TODO: Destroy all mutexes and condition variables.
    pthread_cond_destroy(&logger->queue_not_full);
    pthread_cond_destroy(&logger->queue_not_empty);
    pthread_mutex_destroy(&logger->queue_lock);
    pthread_mutex_destroy(&logger->stream_lock);
    // TODO: Close file_stream safely (if it isn't stdout) and free filepath.
    if (logger->file_stream != stdout) {
        fclose(logger->file_stream);
    }
    free(logger->filepath);
    free(logger);

    printf("Logger destroyed\n");
}

static void handle_rotation(Logger* logger) {
    if (!logger->filepath || logger->current_size < logger->max_size) return;

    // TODO: 1. Close current file_stream.
    fclose(logger->file_stream);
    // TODO: 2. Construct a backup filename string (e.g., filepath + ".old").
    size_t filepath_len = strlen(logger->filepath);
    char backup_filepath[filepath_len + sizeof(".old")];
    memcpy(backup_filepath, logger->filepath, filepath_len);
    memcpy(backup_filepath + filepath_len, ".old", sizeof(".old"));
    // TODO: 3. Use rename() to overwrite or create the .old backup file.
    if (rename(logger->filepath, backup_filepath) != 0) {
        logger->file_stream = fopen(logger->filepath, "a");
        return;
    }
    // TODO: 4. Open a fresh file at original filepath in write mode, reset current_size.
    logger->file_stream = fopen(logger->filepath, "w");
    if (logger->file_stream != NULL) {
        logger->current_size = 0;
    }


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
        pthread_mutex_lock(&logger->queue_lock);

        while(logger->count == ASYNC_QUEUE_CAPACITY && logger->is_running == true){
            pthread_cond_wait(&logger->queue_not_full, &logger->queue_lock);
        }
        if (!logger->is_running) {
            pthread_mutex_unlock(&logger->queue_lock);
            return;
        }

        LogEntry* entry = &logger->queue[logger->tail];

        entry->level = level;
        entry->line = line;
        entry->timestamp = now;

        snprintf(entry->file, sizeof(entry->file), "%s", file);
        snprintf(entry->message, sizeof(entry->message), "%s", msg_buf);

        logger->tail = (logger->tail + 1) % ASYNC_QUEUE_CAPACITY;
        logger->count++;

        pthread_cond_signal(&logger->queue_not_empty);

        pthread_mutex_unlock(&logger->queue_lock);
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
        pthread_mutex_lock(&logger->queue_lock);
        
        while(logger->count == 0 && logger->is_running == true){
            pthread_cond_wait(&logger->queue_not_empty, &logger->queue_lock);
        }

        if(logger->count > 0){
            entry = logger->queue[logger->head];
            logger->head = (logger->head + 1) % ASYNC_QUEUE_CAPACITY;
            logger->count--;
            pthread_cond_signal(&logger->queue_not_full);
            have_entry = true;
        }

        pthread_mutex_unlock(&logger->queue_lock);
        
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
