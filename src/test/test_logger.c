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
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <limits.h>
#include "sobologger/logger.h"
#include "soboutils/utils_file.h"

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif


int main(int argc, char **argv)
{
    int status = 0;
    char cur_path[PATH_MAX];
    char *log_path = "logs/test.log";

    getcwd(cur_path, sizeof(cur_path));
    printf("\ntest_logger testing has been started...\n\n");
    printf("\n\nCURRENT PATH: %s\n\n", cur_path);

    /* preparation test */
    setup_logger("SRV", log_path);
    printf("\nCleanup - removing the log file if it exists\n");
    remove_log_file_if_exists();
    printf("\nChecking whether the log file is absent...");
    assert(!file_exists(log_path));
    printf("\n -- OK!");

    /* writing test - writing */
    printf("\nWriting to log...\n");
    logger("Testing logger - first line.", LOG_INFO);
    logger("Testing logger - second line: %s-%d.", LOG_INFO, "A", 1);

    /* writing test - checking if the file exists */
    printf("\nChecking whether the log file exists...");
    assert(file_exists(log_path));
    printf(" -- OK!\n");

    /* writing test - checking if the file is not empty */
    printf("\nChecking whether the file is not empty...");
    assert(get_file_size(log_path) > 0);
    printf(" -- OK!\n");

    printf("\nChecking whether the file contains the first line...");
    assert(check_file_contains(log_path, "Testing logger - first line."));
    printf(" -- OK!\n");

    printf("\nChecking whether the file contains the second line...");
    assert(check_file_contains(log_path, "Testing logger - second line: A-1."));
    printf(" -- OK!\n");

    /* removing test - final cleanup */
    printf("\nRemoving log file...");
    remove_log_file_if_exists();
    printf("\nChecking whether the log file is properly removed...");
    assert(!file_exists(log_path));
    printf(" -- OK!\n");

    printf("\ntest_logger testing has been finished...\n\n");

    return status;
}
