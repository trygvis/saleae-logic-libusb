#include "log.h"

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>

int min(int x, int y) {
    return x <= y ? x : y;
}

void log_printf(struct logger *logger, enum log_level level, const char *format, ...)
{
    char name[10];
    char timestamp[11];
	char p[1024];

    strncpy(name, logger->name, sizeof(name));
    size_t name_len = min(strlen(logger->name), sizeof(name) - 1);
    memset(name + name_len, ' ', sizeof(name) - name_len);
    name[sizeof(name) - 1] = '\0';

    time_t t = time(NULL);
    const struct tm *tm = localtime(&t);
    strftime(timestamp, sizeof(timestamp), "%T", tm);

	va_list ap;
	va_start(ap, format);
	(void)vsnprintf(p, 1024, format, ap);
	va_end(ap);

    /* Would a right-adjusted name look more readable? */
	fprintf(stderr, "%s: %s: %s", timestamp, name, p);
}
