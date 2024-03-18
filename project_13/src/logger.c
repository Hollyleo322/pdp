#include "logger.h"
#include "log_levels.h"
#include <time.h>
#include <stdio.h>

FILE *log_init(char *filename)
{
    FILE *res = fopen(filename, "a");
    if (res == NULL)
        res = NULL;
    return res;
}
int logcat(FILE *log_file, char *message, log_level level)
{
    int res;
    time_t t = time(NULL);
    struct tm* ptr = localtime(&t);

    if (log_file)
    {
        res = 1;
        switch (level)
        {
        case 0:
            fprintf(log_file, "%s %02d %02d %02d %s\n", "DEBUG", ptr->tm_hour, ptr->tm_min, ptr->tm_sec, message);
            break;
        case 1:
            fprintf(log_file, "%s %02d %02d %02d %s\n", "TRACE", ptr->tm_hour, ptr->tm_min, ptr->tm_sec, message);
            break;
        case 2:
            fprintf(log_file, "%s %02d %02d %02d %s\n", "INFO", ptr->tm_hour, ptr->tm_min, ptr->tm_sec, message);
            break;
        case 3:
            fprintf(log_file, "%s %02d %02d %02d %s\n", "WARNING", ptr->tm_hour, ptr->tm_min, ptr->tm_sec, message);
            break;
        case 4:
            fprintf(log_file, "%s %02d %02d %02d %s\n", "ERROR", ptr->tm_hour, ptr->tm_min, ptr->tm_sec, message);
            break;
        }
    }
    else
        res = 0;
    return res;
}
int log_close(FILE *log_file) {
    int res = 1;
    if (!fclose(log_file))
        res = 0;
    return res;
}