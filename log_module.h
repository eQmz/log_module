/**
 * @file log_module.h
 * @author EM2 (you@domain.com)
 * @brief This library provides a base to make a simple LOG for different aplications
 * @NOTE: The color of the LOG depends of the terminal or console. It takes effect on systems based of UNIX. 
 * @version 2.0
 * @date 2024-11-29
 * 
 * @example An usage example is showed as follows:
 * 
 *  To use the log_module.c/h library effectively, is recommended to create an interface layer (e.g., my_logs.h file). In this layer
 *  all logs could be defined to be used for any module that includes the layer.
 * 
 * @code
 *  #ifndef _MY_LOGS_
    #define _MY_LOGS_

    #include "log_module.h"

    CREATE_LOG_MACRO(USER, TXT_BLUE);
    CREATE_LOG_MACRO(MODULE1, TXT_NAVY_BLUE);
    CREATE_LOG_MACRO(MODULE2, TXT_PURPLE);
    CREATE_LOG_MACRO(MODULE3, TXT_LILAC);
    CREATE_LOG_MACRO(MODULE6, TXT_TURQUOISE);
    CREATE_LOG_MACRO(EVENT1, TXT_L_LILAC);
    CREATE_LOG_MACRO(EVENT2, TXT_GREEN_DRK);
    CREATE_LOG_MACRO(EVENT3, TXT_CYAN);
    CREATE_LOG_MACRO(EVENT4, TXT_BLACK);
    CREATE_LOG_MACRO(EVENT5, TXT_GRAY);
    CREATE_LOG_MACRO(EVENT6, TXT_BROWN);
    CREATE_LOG_MACRO(EVENT7, TXT_VINE);
    CREATE_LOG_MACRO(EVENT8, TXT_WHITE);

    CREATE_LOG_MACRO(INFO, TXT_L_TURQUOISE);
    CREATE_LOG_MACRO(DEBUG, TXT_GREEN);
    CREATE_LOG_MACRO(WARNING, TXT_YELLOW);
    CREATE_LOG_MACRO(ERROR, TXT_ORAGE);
    CREATE_LOG_MACRO(FATAL, TXT_RED);

    #endif //_MY_LOGS_
 * @endcode
 *
 *  This interface layer allows the use of all created logs in any module where it is included.
 *  
 *  Therefore, the main.c file could include my_logs.h file and use all the created logs.
 * @code
    #include "myLogs.h"

    int main(int argc, char const *argv[])
    { 
        GIT_VERSION();
        GIT_VERSION_LOG();
        
        confLog(LOG_INFO_T, (PATH_EN_T | NAME_FILE_EN_T | LINE_EN_T | DATE_EN_T) | LOG_ENABLE_T);
        confLog(LOG_DEBUG_T, (PATH_EN_T | NAME_FILE_EN_T | LINE_EN_T) | LOG_ENABLE_T);
        confLog(LOG_WARNING_T, PATH_EN_T | NAME_FILE_EN_T | LOG_ENABLE_T);
        confLog(LOG_ERROR_T, PATH_EN_T | LOG_ENABLE_T);

        LOG_MODULE1(FL,"This is a MODULE1 message.");
        LOG_USER(FL,"dog.");
        LOG_MODULE6(FL,"This is a MODULE1 message.");
        LOG_INFO(FL,"This is an INFO message.");
        LOG_MODULE2(FL,"This is a MODULE2 message.");
        LOG_MODULE3(FL,"This is a MODULE3 message.");
        LOG_EVENT1(FL,"This is a EVENT1 message.");
        LOG_EVENT2(FL,"This is a EVENT2 message.");
        LOG_EVENT3(FL,"This is a EVENT3 message.");
        LOG_DEBUG(FL,"This is a DEBUG message.");
        LOG_EVENT4(FL,"This is a EVENT4 message.");
        LOG_EVENT5(FL,"This is a EVENT5 message.");
        LOG_EVENT6(FL,"This is a EVENT6 message.");
        LOG_EVENT7(FL,"This is a EVENT7 message.");
        LOG_EVENT8(FL,"This is a EVENT8 message.\n");

        LOG_INFO(FL, "This is a INFO message.");
        LOG_DEBUG(FL,"This is a DEBUG message.");
        LOG_WARNING(FL,"This is a WARNING message.");
        LOG_ERROR(FL,"This is an ERROR message.");
        LOG_FATAL(FL,"This is a FATAL message.");

        printf("Press Enter key to exit...");
        getchar();
        
        return 0;
    }

    Output:
    ====================================================
                MODULE: main.c             
    ====================================================

    [Branch: master]
    [Commit: 5283f91e7d6fe2966c95b929cc672a35f793a555]

    ====================================================

    ====================================================
                    MODULE: log_module                 
    ====================================================

    [Branch: develop]
    [Commit: d442018192b76a05441ed71469adf3a170292194]

    ====================================================

    [MODULE1] : This is a MODULE1 message.
    [USER] : dog.
    [MODULE6] : This is a MODULE1 message.
    [INFO] /mnt/c/Users/a_gc/Documents/Q/c/VS_CODE/LOG_test/ExampleLOG/main.c (Line 16) [2024-12-17 15:30:54]: This is an INFO message.  
    [MODULE2] : This is a MODULE2 message.
    [MODULE3] : This is a MODULE3 message.
    [EVENT1] : This is a EVENT1 message.
    [EVENT2] : This is a EVENT2 message.
    [EVENT3] : This is a EVENT3 message.
    [DEBUG] /mnt/c/Users/a_gc/Documents/Q/c/VS_CODE/LOG_test/ExampleLOG/main.c (Line 22) : This is a DEBUG message.
    [EVENT4] : This is a EVENT4 message.
    [EVENT5] : This is a EVENT5 message.
    [EVENT6] : This is a EVENT6 message.
    [EVENT7] : This is a EVENT7 message.
    [EVENT8] : This is a EVENT8 message.

    [INFO] /mnt/c/Users/a_gc/Documents/Q/c/VS_CODE/LOG_test/ExampleLOG/main.c (Line 30) [2024-12-17 15:30:54]: This is a INFO message.   
    [DEBUG] /mnt/c/Users/a_gc/Documents/Q/c/VS_CODE/LOG_test/ExampleLOG/main.c (Line 31) : This is a DEBUG message.
    [WARNING] /mnt/c/Users/a_gc/Documents/Q/c/VS_CODE/LOG_test/ExampleLOG/main.c : This is a WARNING message.
    [ERROR] /mnt/c/Users/a_gc/Documents/Q/c/VS_CODE/LOG_test/ExampleLOG/: This is an ERROR message.
    [FATAL] : This is a FATAL message.
    Press Enter key to exit...
 * @endcode
 * 
 * On the other hand, if the my_logs.h file is included in another module or library, that library can use any created log. 
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
    LOG_ENABLE_T =  (1 << 4),
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
        uint8_t enable : 1; 
        uint8_t : 3;
    }f;
    
}flgLog_t;

/**
 * @brief This type is designed to create variables that store different log types.
 * 
 */
typedef uint8_t logType_t;

/**
 * @brief This type creates variables to store the LOG name or label.
 * 
 */
typedef char *logLabel_t;

/**
 * @brief This MACRO was created to pass the current line and file where the LOG was called
 *  It must be used with every created LOG.
 *  For instance, if you created the LOG named USER, it should be used as follows:
 * 
 *  CREATE_LOG_MACRO(USER, TXT_BLUE);
 * 
 *  LOG_USER(LF,"Hello Dog"); 
 *  LOG_USER(LF,"value: %d", value); 
 * 
 * 
 */
#define FL __FILE__, __LINE__

#define CREATE_LOG_MACRO(name, color) \
    static const logType_t LOG_##name##_T = __COUNTER__; \
    static const logLabel_t LABEL_##name = #name;\
    static inline void LOG_##name(char *file, int line, const char *fmt, ...) { \
        va_list args; \
        va_start(args, fmt); \
        log_message(LOG_##name##_T, color, LABEL_##name, file, line, fmt, args); \
        va_end(args); \
    }
/**
 * @brief It defines the max number of LOGS that could be created.
 * 
 */
#define LOG_UNSUPPORTED 120
// static uint8_t configLogs[LOG_UNSUPPORTED] = { [0 ... LOG_UNSUPPORTED - 1] = 0x10 };

/**
 * @brief This macro prints the branch and the commit of the module wich calls the macro
 * 
 */
#define GIT_VERSION() printGitVersion(__FILE__)

/**
 * @brief This macro prints the branch and the commit of the log_module
 * 
 */
#define GIT_VERSION_LOG() printGitVersionLOG()

/**
 * @brief These are the LOG colors supported for this version.
 *  They should be pased in CREATE_LOG_MACRO(name, color). 
 * 
 */
typedef enum
{
    TXT_BLUE,           
    TXT_GREEN,         
    TXT_YELLOW,        
    TXT_ORAGE,        
    TXT_RED,            
    TXT_TURQUOISE,      
    TXT_PURPLE, 
    TXT_L_TURQUOISE,        
    TXT_NAVY_BLUE,
    TXT_GREEN_DRK,     
    TXT_VINE,
    TXT_WHITE,
    TXT_PINK,
    TXT_PINKL,
    TXT_CYAN,
    TXT_BROWN,
    TXT_GRAY,
    TXT_BLACK,
    TXT_LILAC,
    TXT_L_LILAC         
}logTextColor_t;

#define TEXT_BLUE           "\033[38;2;0;195;250m"
#define TEXT_GREEN          "\033[38;2;74;252;210m"
#define TEXT_YELLOW         "\033[38;2;255;254;114m"
#define TEXT_ORAGE          "\033[38;2;255;153;0m"
#define TEXT_RED            "\033[38;2;252;96;96m"
#define TEXT_TURQUOISE      "\033[38;2;24;170;195m"
#define TEXT_PURPLE         "\033[38;2;110;99;247m"
#define TEXT_L_TURQUOISE    "\033[38;2;33;222;247m"
#define TEXT_NAVY_BLUE      "\033[38;2;0;120;255m"
#define TEXT_GREEN_DRK      "\033[38;2;3;201;154m"
#define TEXT_VINE           "\033[38;2;215;2;80m"
#define TEXT_WHITE          "\033[38;2;255;255;255m"
#define TEXT_PINK           "\033[38;2;246;18;154m"
#define TEXT_PINKL          "\033[38;2;250;114;244m"
#define TEXT_CYAN           "\033[38;2;2;240;240m"
#define TEXT_BROWN          "\033[38;2;201;128;99m"
#define TEXT_GRAY           "\033[38;2;180;180;180m"
#define TEXT_BLACK          "\033[38;2;0;0;0m"
#define TEXT_LILAC          "\033[38;2;205;98;248m"
#define TEXT_L_LILAC        "\033[38;2;218;187;253m"


#define BCKG_BLUE           "\033[1;48;2;33;222;247m"
#define BCKG_GREEN          "\033[1;48;2;74;252;210m"
#define BCKG_YELLOW         "\033[1;48;2;255;254;114m"
#define BCKG_ORAGE          "\033[1;48;2;255;153;0m"
#define BCKG_RED            "\033[1;48;2;252;96;96m"
#define BCKG_TURQUOISE      "\033[1;48;2;0;163;224m"
#define BCKG_PURPLE         "\033[1;48;2;110;99;247m"
#define BCKG_L_TURQUOISE    "\033[1;48;2;66;202;234m"
#define BCKG_NAVY_BLUE      "\033[1;48;2;0;16;110m"
#define BCKG_GREEN_DRK      "\033[1;48;2;3;201;154m"
#define BCKG_VINE           "\033[1;48;2;110;0;0m"
#define BCKG_WHITE          "\033[1;48;2;255;255;255m"
#define BCKG_PINK           "\033[1,48;2;246;18;154m"
#define BCKG_PINKL          "\033[1,48;2;250;114;244m"
#define BCKG_CYAN           "\033[1,48;2;2;240;240m"
#define BCKG_BROWN           "\033[1,48;2;201;128;99m"
#define BCKG_GRAY           "\033[1,48;2;180;180;180m"
#define BCKG_BLACK           "\033[1,48;0;0;0;0m"
#define BCKG_LILAC          "\033[1;48;2;205;98;248m"
#define BCKG_L_LILAC        "\033[1;48;2;218;187;253m"

#define END_COLOR           "\033[0m"

/**
 * @brief This array is used to link the color options and its corresponding color definitions.
 * 
 */
static const char *colors[] = {
    TEXT_BLUE,           
    TEXT_GREEN,         
    TEXT_YELLOW,        
    TEXT_ORAGE,        
    TEXT_RED,            
    TEXT_TURQUOISE,      
    TEXT_PURPLE,  
    TEXT_L_TURQUOISE,       
    TEXT_NAVY_BLUE,  
    TEXT_GREEN_DRK,    
    TEXT_VINE, 
    TEXT_WHITE,
    TEXT_PINK,
    TEXT_PINKL,
    TEXT_CYAN,
    TEXT_BROWN,
    TEXT_GRAY,
    TEXT_BLACK,
    TEXT_LILAC,
    TEXT_L_LILAC
    };

/**
 * @brief This is the abstraction function to generate the message for the differents LOGS.
 * 
 * @param logType is the LOG type and indicates the context to use the LOG particularities.
 * @param color is the log color.
 * @param label is the log name or label.
 * @param file  is the file name where the LOG was called.
 * @param line is the line number where the LOG was called.
 * @param fmt this is the string format to print the data or message.
 * @param ... these are the var parameters to be printed.
 */
//void log_message(logType_t logType, const char *file, int line, const char *fmt, ...);
void log_message(logType_t logType, logTextColor_t color, logLabel_t label, char *file, int line, const char *fmt, va_list args);

/**
 * @brief Gets the Conf Log object to know the LOG configuration.
 * 
 * @param logType is the LOG type whose LOG configuration is wanted to retrive.
 * @return uint8_t* returns the instance of the LOG configuration singleton.
 */
static uint8_t *getConfLog(logType_t logType);

/**
 * @brief This function sets the LOG configuration.
 * 
 * @param logType indicates the type of LOG to be configured.
 * @param config this parameter contains the desired flag configurations. 
 * You could make several OR combination to select the different LOG options (PATH_EN_T, NAME_FILE_EN_T, LINE_EN_T, DATE_EN_T)
 * 
 * Example to enable only the path and the name of the file where the LOG was called:
 * 
 * confLog(LOG_INFO_T, PATH_EN_T | NAME_FILE_EN_T | LOG_ENABLE_T);
 * 
 * To disable any configuration flag, it must be chossen the configuration flags again.
 * 
 * Example to disable path and name of the file:
 * 
 * confLog(LOG_INFO_T, PATH_EN_T | NAME_FILE_EN_T | LOG_ENABLE_T)
 * 
 * confLog(LOG_INFO_T, DATE_EN_T | LOG_ENABLE_T)
 * 
 * The line above only configurates the date when the LOG was called and it omits the rest of the flags. 
 * 
 * If you want to enable all configuration flags you have to use:
 * 
 * confLog(LOG_INFO_T, PATH_EN_T | NAME_FILE_EN_T | LINE_EN_T | DATE_EN_T | LOG_ENABLE_T);
 * 
 * or
 * 
 * confLog(LOG_INFO_T, ALL_ENABLED_T)
 * 
 * On the other hand, if a LOG is not configured, all configuration flags are disabled for this LOG except the LOG_ENABLE_T option.
 */
void confLog(logType_t logType, logFlagType_t config);

static char* execute_command(const char* command);

void printGitVersion(const char *file);
void printGitVersionLOG(void);

#endif //_LOG_MODULE_H