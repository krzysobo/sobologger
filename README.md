# SoboLogger
SoboLogger is a simple logging system that allows for writing logs into a text file.

# Copyright
© Copyright by Krzysztof Sobolewski 2020-2021.
SoboLogger is Open Source software, licensed under the MIT license available here:
https://opensource.org/licenses/mit-license.php

# Contact
You can contact the author using the email:
<krzysztof.sobolewski@gmail.com>
I'm looking for cooperation in the further development of this software.

# Compilation and Installation
The SoboLogger library requires the SoboUtils library to be properly installed.
You can get the SoboUtils here:
https://github.com/krzysobo/soboutils

GIT: 
git@github.com:krzysobo/soboutils.git 
or
https://github.com/krzysobo/soboutils.git

Please remember to call:
```make``` (or ```make alltest``` to build the SoboUtils tests as well) and ```make install``` in the root directory of SoboUtils. 
```make install``` requires the sudo access.

After you have the working SoboUtils placed in the directories:
*/usr/local/share/soboutils* (includes)
and
*/usr/local/lib/soboutils* (library bin.)
Please go on with installation of SoboLogger.

## Build SoboLogger without tests:
```make``` or ```make all```
In the root directory of the project. 
The binaries will be built into ./bin. 
The binaries are:
```sobologger.o```

## Build SoboLogger with tests:
```make alltest```
In the same directory will do the same + build tests. 
The binaries will be built into ./bin.
The binaries are:
```sobologger.o```
```test_logger```

## Install in the common paths:
After ```make```, ```make all```  or ```make alltest``` has been done, call:
```make install```
in the root directory of the project.
**WARNING: requires the sudo access**.

The library (sobologger.o) and the header file will be put in the target common directories, defined into the makefile in the variables:
```SOBOLOGGER_INCLUDE_PATH ?= '/usr/local/share/sobologger'```
```SOBOLOGGER_LIB_PATH     ?= '/usr/local/lib/sobologger'```

You may change those paths to conform with your system configuration. 


# Usage in your projects
In order to setup the logger type:  
    ```setup_logger("<<name_of_your_logger>>", "<<log_file_path>>")```

In order to write the log, please use the "logger" function:
    ```logger("<<message>>", <<LOG_LEVEL>>, [comma-separated-sprintf-params]);```

The following log levels are available:
    LOG_EMERGENCY 0
    LOG_ALERT 1
    LOG_CRIT 2  
    LOG_ERROR 3
    LOG_WARNING 4
    LOG_NOTICE 5
    LOG_INFO 6
    LOG_DEBUG 7


# Tested and tests passing on:
```ArchLinux 5.10.7-arch1-1```
```MacOS Catalina 10.15.6```
