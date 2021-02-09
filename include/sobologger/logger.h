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


#ifndef LOGGER_H
#define LOGGER_H

void logger(char *msg, int errorlevel, ...);
void setup_logger(char *name, char *file_path);
void remove_log_file_if_exists();

#endif /* LOGGER_H */

#define LOG_EMERGENCY 0
#define LOG_ALERT 1
#define LOG_CRIT  2
#define LOG_ERROR 3
#define LOG_WARNING 4
#define LOG_NOTICE 5
#define LOG_INFO 6
#define LOG_DEBUG 7



