//
// Created by Kirill Zhukov on 28.12.2022.
//

#ifndef VM_WITH_HEAP_LOGGER_H
#define VM_WITH_HEAP_LOGGER_H
#include "loggerTime.h"
extern "C" {
    #include "err.h"
    #include "stdio.h"

    #define ANSI_COLOR_RED     "\x1b[31m"
    #define ANSI_COLOR_GREEN   "\x1b[32m"
    #define ANSI_COLOR_YELLOW  "\x1b[33m"
    #define ANSI_COLOR_BLUE    "\x1b[34m"
    #define ANSI_COLOR_MAGENTA "\x1b[35m"
    #define ANSI_COLOR_CYAN    "\x1b[36m"
    #define ANSI_COLOR_RESET   "\x1b[0m"

    #define BLUE_STRING(string) ANSI_COLOR_BLUE string ANSI_COLOR_RESET
    #define RED_STRING(string) ANSI_COLOR_RED string ANSI_COLOR_RESET
    #define GREEN_STRING(string) ANSI_COLOR_GREEN string ANSI_COLOR_RESET
    #define YELLOW_STRING(string) ANSI_COLOR_YELLOW string ANSI_COLOR_RESET
    #define MAGENTA_STRING(string) ANSI_COLOR_MAGENTA string ANSI_COLOR_RESET
    #define CYAN_STRING(string) ANSI_COLOR_CYAN string ANSI_COLOR_RESET

    /// used for setting up logging level through static types
    struct LoggingLevel {
        inline static char const  INFO[7] = " INFO\0";
        inline static char const  WARN[7] = " WARN\0";
        inline static char const ERROR[7] = "ERROR\0";
        inline static char const DEBUG[7] = "DEBUG\0";
        inline static char const TRACE[7] = "TRACE\0";
    };

    ///  puts data into stream depending on data stream type
    ///  @param [in] msg string. data will be written
    ///  @param [in] loggingType string. info/warn/error/debug
    ///  @param [in] streamType FILE*. stdin/stdout/stderr
    inline void log(const char *msg, const char *loggingType, FILE *stream) {

        #if COLORFUL_TERMINAL
            if (strlen(loggingType) > 7) {
                fprintf(stream, "%s [" RED_STRING("%s") "] --- %s%s\n", c_loggingTimeStr(), LoggingLevel::ERROR,
                        "invalid logging level: ", loggingType);
                return;
            }
            if (strncmp(loggingType, LoggingLevel::INFO, 6) == 0)
                fprintf(stream, "%s [" GREEN_STRING("%s") "] --- %s\n", c_loggingTimeStr(), loggingType, msg);
            else if (strncmp(loggingType, LoggingLevel::WARN, 6) == 0)
                fprintf(stream, "%s [" YELLOW_STRING("%s") "] --- %s\n", c_loggingTimeStr(), loggingType, msg);
            else if (strncmp(loggingType, LoggingLevel::ERROR, 6) == 0)
                fprintf(stream, "%s [" RED_STRING("%s") "] --- %s\n", c_loggingTimeStr(), loggingType, msg);
            else if (strncmp(loggingType, LoggingLevel::TRACE, 6) == 0)
                fprintf(stream, "%s [" CYAN_STRING("%s") "] --- %s\n", c_loggingTimeStr(), loggingType, msg);
            else
                fprintf(stream, "%s [" MAGENTA_STRING("%s") "] --- %s\n", c_loggingTimeStr(), loggingType, msg);
        #else
            fprintf(stream, "%s [%s] --- %s\n", c_loggingTimeStr(), loggingType, msg);
        #endif
    }
};

#endif //VM_WITH_HEAP_LOGGER_H

