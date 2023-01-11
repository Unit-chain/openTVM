//
// Created by Kirill Zhukov on 28.12.2022.
//

#ifndef VM_WITH_HEAP_LOGGERTIME_H
#define VM_WITH_HEAP_LOGGERTIME_H

#include <c++/v1/string>
#include <cassert>
#include <globalDefenitions.h>

extern "C" {
    #include <time.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    /// @return tm* from <time.h>
    inline tm* getTime() {
        time_t timer;
        struct tm* tm_info;
        timer = time(NULL);
        tm_info = localtime(&timer);
        return tm_info;
    }

    ///  writing into buffer time in format: "%Y-%m-%d %H:%M:%S"
    ///  @param [in] buffer string. data will be written
    ///  @param [in] buffer_size size_t. buffer size
    ///  @return -1 if error, otherwise return value > 0.
    inline int toLoggingTime(char *buffer) {
        tm* time = getTime();
        size_t buffer_len = strlen(buffer);
        if (buffer_len > 26)
            return -1;
        strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", getTime());
        free(time);
        return 1;
    }

    ///  @return c_string representing current time in format: "%Y-%m-%d %H:%M:%S ###"
    inline char *c_loggingTimeStr() {
        char *buff = (char*)malloc(26 * sizeof(char*));
        assert(toLoggingTime(buff) == 1);
        return buff;
    }
};

///  @return string representing current time in format: "%Y-%m-%d %H:%M:%S ###"
std::string loggingTimeStr() {
    char *buff = (char*)malloc(26 * sizeof(char*));
    assert(toLoggingTime(buff) == 1);
    return {buff};
}
#endif //VM_WITH_HEAP_LOGGERTIME_H