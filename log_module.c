#include "log_module.h"

void log_message(logType_t logType, logTextColor_t color, logLabel_t label, char *file, int line, const char *fmt, va_list args) {

    uint8_t *auxconf = getConfLog(logType);
    flgLog_t configLogs = {.flag = *auxconf};
    
    if(!configLogs.f.enable)
        return;

    char time_buffer[26] = {'\0'};
    if(configLogs.f.date)
    {
        //To get the date 
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        //To get the format: YYYY-MM-DD HH:MM:SS
        strftime(time_buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);  
    }

    //char *labelType[] = {"[INFO]", "[DBG]", "[WRN]", "[ERR]", "[FATAL]"};
    //char *labelColors[] = {"38;2;33;222;247m", "38;2;74;252;210m", "38;2;255;254;114m", "38;2;255;153;0m", "38;2;252;96;96m"}; //34 32 33 - 31

    //To get the actual path
    char cwd[1024] = {'\0'};

    if(configLogs.f.path)
        if (getcwd(cwd, sizeof(cwd)) == NULL) 
            perror("getcwd() error");

    //To make and print in LOG format
    // va_list args;
    // va_start(args, fmt);
    
        printf("\033[%s[%s]\033[0m ", colors[color], label);
        
        if(configLogs.f.path)
        printf("%s/", cwd);
        
        if(configLogs.f.nameFile)
        printf("\033[44;48;2;110;99;247m%s\033[0m ", file);
        
        if(configLogs.f.line)
        printf("\033[1;48;2;205;98;248m(Line %d)\033[0m ", line);   

        if(configLogs.f.date)  
        printf("[%s]", time_buffer);   

        printf(": ");  

        //To print the message or event in a desired format
        printf("\033[1;%s",colors[color]);
        vprintf(fmt, args);
        printf("\033[0m\n");

    va_end(args);
    
}

static uint8_t *getConfLog(logType_t logType)
{
    static uint8_t configLogs[LOG_UNSUPPORTED] = { [0 ... LOG_UNSUPPORTED - 1] = 0x10 };

    return &configLogs[logType];
}

void confLog(logType_t logType, logFlagType_t config)
{
    uint8_t *configLog = getConfLog(logType);
    *configLog = config;
}

static char* execute_command(const char* command) {
    static char result[128];  // Buffer para almacenar la salida
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen failed");
        return NULL;
    }
    fgets(result, sizeof(result), fp);
    result[strcspn(result, "\n")] = 0;  // Eliminar el salto de línea al final
    fclose(fp);
    return result;
}

void printGitVersionLOG(void)
{
    const char* branch = execute_command("cd log_module && git rev-parse --abbrev-ref HEAD");
    char branch_aux[120];
    strcpy(branch_aux, branch);

    const char* commit_hash = execute_command("cd log_module && git rev-parse HEAD");
    char commit_hash_aux[120];
    strcpy(commit_hash_aux, commit_hash);

    printf(TEXT_TURQUOISE"====================================================\n"END_COLOR);
    printf(TEXT_TURQUOISE"\t\t\033[1mMODULE: %s\t\t   \n"END_COLOR\
    TEXT_TURQUOISE"====================================================\n"END_COLOR\
    "\n[" BCKG_VINE"Branch"END_COLOR\
    ": %s]\n["BCKG_NAVY_BLUE"Commit"END_COLOR": %s]\n",\
            "log_module", (branch_aux ? branch_aux : "Unknown"), (commit_hash_aux ? commit_hash_aux : "Unknown"));
    printf(TEXT_TURQUOISE"\n====================================================\n\n"END_COLOR);
}


void printGitVersion(const char *file)
{
    const char* branch = execute_command("git rev-parse --abbrev-ref HEAD"); 
    char branch_aux[120];
    strcpy(branch_aux, branch);

    const char* commit_hash = execute_command("git rev-parse HEAD");
    char commit_hash_aux[120];
    strcpy(commit_hash_aux, commit_hash);

    printf(TEXT_PURPLE"====================================================\n"END_COLOR);
    printf(TEXT_PURPLE"\t\t\033[1mMODULE: %s\t\t   \n"END_COLOR\
    TEXT_PURPLE"====================================================\n"END_COLOR\
    "\n[" BCKG_VINE"Branch"END_COLOR\
    ": %s]\n["BCKG_NAVY_BLUE"Commit"END_COLOR": %s]\n",\
            file, branch_aux ? branch_aux : "Unknown", commit_hash_aux ? commit_hash_aux : "Unknown");
    printf(TEXT_PURPLE"\n====================================================\n\n"END_COLOR);
}