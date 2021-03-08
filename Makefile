##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR                     := /usr/bin/ar rcu
CXX                    := /usr/bin/g++
# can be set in the env. vars, ie. export CC='ccccc'
CC                     := /usr/bin/gcc
CXXFLAGS               :=  -g -O0 -Wall -Werror
CFLAGS                 :=  -g -O0 -Wall -Werror -std=c89 -pedantic
ASFLAGS                := 
AS                     := /usr/bin/as
# can be set in the env. vars, ie. export TARGET_PATH='xxxxx'
TARGET_PATH            ?= 'bin'

SOBO_COMMON_INCLUDE_PATH        ?= '/usr/local/share'
SOBOUTILS_LIB_PATH              ?= '/usr/local/lib/soboutils'
SOBOLOGGER_INSTALL_INCLUDE_PATH ?= '/usr/local/share/sobologger'
SOBOLOGGER_LIB_PATH             ?= '/usr/local/lib/sobologger'

.PHONY: clean

all: loggerlib_static
alltest: loggerlib_static logtestdirs testlogger


logger: src/logger.c
	$(CC) $(CFLAGS) -fpic -o $(TARGET_PATH)/logger.o \
	-c src/logger.c \
	-I include \
	-I $(SOBO_COMMON_INCLUDE_PATH)

	chmod 777 $(TARGET_PATH)/logger.o


loggerlib_static: logger
	ar -x $(SOBOUTILS_LIB_PATH)/libsoboutils.a
	mv ./*.o ./bin/
	ar rcs $(TARGET_PATH)/libsobologger.a \
	$(TARGET_PATH)/*.o

	rm -f $(TARGET_PATH)/*.o


logtestdirs: 
	echo "TARGET PATH: $(TARGET_PATH)"
	mkdir -p $(TARGET_PATH)/logs

testlogger: src/test/test_logger.c
	$(CC) $(CFLAGS) -fpic -o bin/test_logger \
	src/test/test_logger.c \
	$(TARGET_PATH)/libsobologger.a \
	-I include \
	-I $(SOBO_COMMON_INCLUDE_PATH)


install:
	@echo "\nThis operation requires the SUDO access.\n"
	sudo mkdir -p $(SOBOLOGGER_LIB_PATH)
	sudo mkdir -p $(SOBOLOGGER_INSTALL_INCLUDE_PATH)
	sudo cp -rf $(TARGET_PATH)/libsobologger.a $(SOBOLOGGER_LIB_PATH)/
	sudo cp -rf include/sobologger/* $(SOBOLOGGER_INSTALL_INCLUDE_PATH)/

clean:
	rm -rf *.o
	rm -rf $(TARGET_PATH)/*
