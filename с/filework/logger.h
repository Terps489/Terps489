#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>

#include "log_levels.h"

int log_init(const char *filename);
void logcat(LogLevel level, const char *message);
void log_close(void);

#endif