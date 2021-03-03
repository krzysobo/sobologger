/*  
*  Copyright (c) 2020-2021 Krzysztof Sobolewski <krzysztof.sobolewski@gmail.com>
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:

*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.

*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include "soboutils/utils_time.h"
#include "soboutils/utils_file.h"
#include "sobologger/logger.h"

char logger_name[20];
char logger_file_path[1024];

/* http://zetcode.com/articles/cdatetime/
* %F: %Y-%m-%d, %T: %H:%M:%S
*/
const char *time_format = "%F %T"; 


/**
 * @brief  setup the logger system
 * @note   
 * @param  *name: logger name, max. 20 chars
 * @param  *file_path: file path, max. 1024 chars
 * @retval None
 */
void setup_logger(char *name, char *file_path)
{
    memset(&logger_name, 0, sizeof(logger_name));
    memset(&logger_file_path, 0, sizeof(logger_file_path));
    memcpy(logger_name, name, strlen(name));
    memcpy(logger_file_path, file_path, strlen(file_path));
}


void remove_log_file_if_exists()
{
    if (file_exists(logger_file_path)) {
        remove(logger_file_path);
    }    
}


/**
 * @brief  writes to the log file
 * @note   
 * @param  *text: 
 * @retval 
 */
int write_to_log_file(char *text)
{
    FILE *fp;
    int res;

    fp = fopen(logger_file_path, "ab");
    res = fprintf(fp, "%s", text);
    fclose(fp);
    /* should be non-negative to be OK */
    return (res >= 0)? 0:1;
}


/**
 * @brief  main logger function
 * @note   
 * @param  *msg: 
 * @param  errorlevel: 
 * @retval None
 */
void logger(char *msg, int errorlevel, ...)
{
    char out_level_txt[10];
    char tmp_msg[16384];
    char out_msg[17000];
    char formatted_time[20];
    
    va_list args;
    va_start(args, errorlevel);
    vsprintf(tmp_msg, msg, args);
    va_end(args);

    #ifndef DEBUG_MODE
    if (errorlevel == LOG_DEBUG) {
        return;
    }
    #endif

    if (strlen(logger_name) == 0) {
        sprintf(logger_name, "LOG");
    }

    switch(errorlevel) {
        case LOG_EMERGENCY:
            sprintf(out_level_txt, "EMERGENCY");
            break;
        case LOG_ALERT:
            sprintf(out_level_txt, "ALERT");
            break;
        case LOG_ERROR:
            sprintf(out_level_txt, "ERROR");
            break;
        case LOG_WARNING:
            sprintf(out_level_txt, "WARNING");
            break;
        case LOG_NOTICE:
            sprintf(out_level_txt, "NOTICE");
            break;
        case LOG_INFO:
            sprintf(out_level_txt, "INFO");
            break;
        case LOG_DEBUG:
            sprintf(out_level_txt, "DEBUG");
            break;
    }

    get_formatted_local_time(formatted_time, sizeof(formatted_time), 
        time_format);

    sprintf(out_msg, "%s\t%s[%s]: %s\n", formatted_time, logger_name, 
            out_level_txt, tmp_msg);

    if (strlen(logger_file_path) > 0) {
        write_to_log_file(out_msg);
    }
}
