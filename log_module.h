/**
 * @file log_module.h
 * @author EM2 (you@domain.com)
 * @brief This library provides a base to make a simple LOG for different aplications
 * @NOTE: The color of the LOG depends of the terminal or console. This take effect on systems based of UNIX. 
 * @version 1.0
 * @date 2024-11-29
 * 
 * @code
    #include "log_module.h"

    int main(int argc, char const *argv[])
    {
        confLog(LOG_INFO_T, PATH_EN_T | NAME_FILE_EN_T | LINE_EN_T | DATE_EN_T);
        confLog(LOG_DEBUG_T, PATH_EN_T | NAME_FILE_EN_T | LINE_EN_T);
        confLog(LOG_WARNING_T, PATH_EN_T | NAME_FILE_EN_T);
        confLog(LOG_ERROR_T, PATH_EN_T);

        LOG_INFO("This is an INFO message.");
        LOG_DEBUG("This is a DEBUG message.");
        LOG_WARNING("This is a WARNING message.");
        LOG_ERROR("This is an ERROR message.");
        LOG_FATAL("This is a FATAL message.");
        return 0;
    }

    Output:
    [INFO] C:\Users\a_gc\Documents\Q\c\VS_CODE\LOG_test\ExampleLOG\main.c (Line 10) [2024-12-02 09:57:11]: This is an INFO message.
    [DBG] C:\Users\a_gc\Documents\Q\c\VS_CODE\LOG_test\ExampleLOG\main.c (Line 11) : This is a DEBUG message.
    [WRN] C:\Users\a_gc\Documents\Q\c\VS_CODE\LOG_test\ExampleLOG\main.c : This is a WARNING message.
    [ERR] C:\Users\a_gc\Documents\Q\c\VS_CODE\LOG_test\ExampleLOG\: This is an ERROR message.
    [FATAL] : This is a FATAL message.
 * @endcode
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef LOG_MODULE_H

#define LOG_MODULE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unistd.h"  // to use getcwd
#include "stdarg.h" // to use va_start
#include <time.h>   //To get the date
#include "stdint.h"

/**
 * @brief This is the type to select the LOG type
 * 
 */
typedef enum
{
    LOG_INFO_T,
    LOG_DEBUG_T,
    LOG_WARNING_T,
    LOG_ERROR_T,
    LOG_FATAL_T,
    LOG_UNSUPPORTED
}logType_t;

/**
 * @brief This is the type to select the flags for the LOG configuration.
 * @enum PAHT_EN_T enables or shows the path where the LOG was called.
 * @enum NAME_FILE_EN_T enables or shows the name of the file or module where the LOG was called.
 * @enum LINE_EN_T enables or shows the line in the file or module where the LOG was called.
 * @enum DATE_EN_T enables oe shows the time when the LOG was called.
 * 
 */
typedef enum
{
    PATH_EN_T = (1 << 0),
    NAME_FILE_EN_T = (1 << 1), // 0000 0010 -> ~1111 1101
    LINE_EN_T = (1 << 2),
    DATE_EN_T =  (1 << 3),
    ALL_DISABLED_T =  (0x00),
    ALL_ENABLED_T =  (0x0F)
}logFlagType_t;

/**
 * @brief This is the bit field type to allocate the flags or LOG configuration. 
 * 
 */
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

/**
 * @brief This is the MACRO fuctions for INFO LOG.
 * 
 */
#define LOG_INFO(fmt, ...) log_message(LOG_INFO_T, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

/**
 * @brief This is the MACRO fuctions for DEBUG LOG.
 * 
 */
#define LOG_DEBUG(fmt, ...) log_message(LOG_DEBUG_T, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

/**
 * @brief This is the MACRO fuctions for WARNING LOG.
 * 
 */
#define LOG_WARNING(fmt, ...) log_message(LOG_WARNING_T, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

/**
 * @brief This is the MACRO fuctions for ERROR LOG.
 * 
 */
#define LOG_ERROR(fmt, ...) log_message(LOG_ERROR_T, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

/**
 * @brief This is the MACRO fuctions for FATAL LOG.
 * 
 */
#define LOG_FATAL(fmt, ...) log_message(LOG_FATAL_T, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

/**
 * @brief This is the abstraction function to generate the message for the differents LOGS.
 * 
 * @param logType is the LOG type and indicates the context to use the LOG particularities.
 * @param file  is the file name where the LOG was called.
 * @param line is the line number where the LOG was called.
 * @param fmt this is the string format to print the data or message.
 * @param ... these are the var parameters to be printed.
 */
void log_message(logType_t logType, const char *file, int line, const char *fmt, ...);

/**
 * @brief Get the Conf Log object to know the LOG configuration.
 * 
 * @param logType is the LOG type wich its LOG configuration is wanted to know.
 * @return uint8_t* returns the instance of the LOG configuration singleton.
 */
static uint8_t *getConfLog(logType_t logType);

/**
 * @brief This function sets the LOG configuration.
 * 
 * @param logType indicates the type of LOG to be configured.
 * @param config this parameter contains the desired flag configurations. 
 * You could do several OR combination to select the different LOG options (PATH_EN_T, NAME_FILE_EN_T, LINE_EN_T, DATE_EN_T)
 * 
 * Example to enables only shows the path and the name of the file where the LOG was called:
 * 
 * confLog(LOG_INFO_T, PATH_EN_T | NAME_FILE_EN_T);
 * 
 * To disable any configuration flag, you have to chosse again the configuration flags
 * 
 * Example to disable path and the name of the file where the LOG was called, after these was configured:
 * 
 * confLog(LOG_INFO_T, PATH_EN_T | NAME_FILE_EN_T)
 * 
 * confLog(LOG_INFO_T, DATE_EN_T)
 * 
 * The line above only configurates the date when the LOG was called and it omits the rest of the flags. 
 * 
 * If you want to enable all configuration flags you have to use:
 * 
 * confLog(LOG_INFO_T, PATH_EN_T | NAME_FILE_EN_T | LINE_EN_T | DATE_EN_T);
 * 
 * or
 * 
 * confLog(LOG_INFO_T, ALL_ENABLED_T)
 * 
 * On the other hand, if a LOG is not configured, all configuration flags are disabled for this LOG.
 */
void confLog(logType_t logType, logFlagType_t config);
#endif //_LOG_MODULE_H