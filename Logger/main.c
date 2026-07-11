#include "logger.h"
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 4
#define LOGS_PER_THREAD 100

void* worker_thread(void* arg) {
    Logger* log = (Logger*)arg;
    for (int i = 0; i < LOGS_PER_THREAD; i++) {
        LOG_I(log, "Thread %p tracing execution checkpoint. Loop: %d", (void*)pthread_self(), i);
        if (i % 10 == 0) {
            LOG_W(log, "Warning state emitted intentionally from thread context.");
        }
        usleep(500); // Induce rapid multitasking context switching
    }
    return NULL;
}

int main(void) {
    pthread_t threads[THREAD_COUNT];

    // ==========================================
    // TEST 1: ASYNC MODE (Aggressive Rotation Test)
    // ==========================================
    printf("Testing ASYNC Logging Mode...\n");
    Logger* async_log = logger_create("async_output.log", LOG_INFO, 1024 * 15, LOG_MODE_ASYNC);
    if (!async_log) return 1;

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, worker_thread, async_log);
    }
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    
    logger_destroy(async_log);

    // ==========================================
    // TEST 2: SYNC MODE 
    // ==========================================
    printf("Testing SYNC Logging Mode...\n");
    Logger* sync_log = logger_create("sync_output.log", LOG_INFO, 1024 * 15, LOG_MODE_SYNC);
    if (!sync_log) return 1;

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, worker_thread, sync_log);
    }
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    
    logger_destroy(sync_log);
    
    printf("\nExecution completed successfully!\nVerify that log files and '.old' variants exist.\n");
    return 0;
}
