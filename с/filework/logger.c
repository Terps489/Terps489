#include "logger.h"

#include <stdlib.h>
#include <time.h>

static FILE *log_file = NULL;
int log_init(const char *filename) {
    log_file = fopen(filename, "a");
    if (log_file == NULL) {
        return -1;
    }
    return 0;
}
void logcat(LogLevel level, const char *message) {
    if (log_file == NULL) {
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    fprintf(log_file, "[%04d-%02d-%02d %02d:%02d:%02d] ", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);
    switch (level) {
        case debug:
            fprintf(log_file, "[DEBUG] ");
            break;
        case trace:
            fprintf(log_file, "[TRACE] ");
            break;
        case info:
            fprintf(log_file, "[INFO] ");
            break;
        case warning:
            fprintf(log_file, "[WARNING] ");
            break;
        case error:
            fprintf(log_file, "[ERROR] ");
            break;
    }
    fprintf(log_file, "%s\n", message);
}
void log_close(void) {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
}