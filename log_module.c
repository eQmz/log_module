#include "log_module.h"

void log_message(logType_t logType, const char *file, int line, const char *fmt, ...) {

    uint8_t *auxconf = getConfLog(logType);
    flgLog_t configLogs = {.flag = *auxconf};
    
    char time_buffer[26] = {'\0'};
    if(configLogs.f.date)
    {
        //To get the date 
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        //To get the format: YYYY-MM-DD HH:MM:SS
        strftime(time_buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);  
    }

    char *labelType[] = {"[INFO]", "[DBG]", "[WRN]", "[ERR]", "[FATAL]"};
    char *labelColors[] = {"38;2;15;230;241m", "38;2;26;230;206m", "33m", "38;2;255;165;0m", "38;2;243;13;68m"}; //34 32 33 - 31

    //To get the actual path
    char cwd[1024] = {'\0'};

    if(configLogs.f.path)
        if (getcwd(cwd, sizeof(cwd)) == NULL) 
            perror("getcwd() error");

    //To make and print in LOG format
    va_list args;
    va_start(args, fmt);
    
        printf("\033[%s%s\033[0m ", labelColors[logType], labelType[logType]);
        
        if(configLogs.f.path)
        printf("%s\\", cwd);
        
        if(configLogs.f.nameFile)
        printf("\033[44;1m%s\033[0m ", file);
        
        if(configLogs.f.line)
        printf("\033[1;106m(Line %d)\033[0m ", line);   

        if(configLogs.f.date)  
        printf("[%s]", time_buffer);   

        printf(": ");  

        //To print the message or event in a desired format
        printf("\033[1;%s",labelColors[logType]);
        vprintf(fmt, args);
        printf("\033[0m\n");

    va_end(args);
    
}


static uint8_t *getConfLog(logType_t logType)
{
    static uint8_t configLogs[LOG_UNSUPPORTED] = {0};

    return &configLogs[logType];
}

void confLog(logType_t logType, logFlagType_t config)
{
    uint8_t *configLog = getConfLog(logType);
    *configLog = config;
}