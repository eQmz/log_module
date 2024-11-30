/**
 * @file log_module.h
 * @author EM2 (you@domain.com)
 * @brief This library provides a base to make a simple LOG for different aplications
 * @version 0.1
 * @date 2024-11-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef LOG_MODULE_H

#define LOG_MODULE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unistd.h"  // Para getcwd
#include "stdarg.h" //para va_start
#include <time.h>       // Para obtener la fecha y hora
#include "stdint.h"

typedef enum
{
    LOG_INFO_T,
    LOG_DEBUG_T,
    LOG_WARNING_T,
    LOG_ERROR_T,
    LOG_FATAL_T,
    LOG_UNSUPPORTED
}logType_t;

typedef enum
{
    PATH_EN_T = (1 << 0),
    NAME_FILE_EN_T = (1 << 1),
    LINE_EN_T = (1 << 2),
    DATE_EN_T =  (1 << 3),
}logFlagType_t;

typedef union
{
    uint8_t flag;
    struct 
    {
        uint8_t path : 1;
        uint8_t nameFile : 1;
        uint8_t line :1;
        uint8_t date : 1; 
        uint8_t : 4;
    }f;
    
}flgLog_t;

#define LOG_INFO(fmt, ...) log_message(LOG_INFO_T, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) log_message(LOG_DEBUG_T, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) log_message(LOG_WARNING_T, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) log_message(LOG_ERROR_T, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...) log_message(LOG_FATAL_T, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

void log_message(logType_t logType, const char *file, int line, const char *fmt, ...);
static uint8_t *getConfLog(logType_t logType);
void confLog(logType_t logType, logFlagType_t config);
#endif //_LOG_MODULE_H