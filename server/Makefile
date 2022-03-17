# C Makefile using gcc, gdb and valgrind. 
# Modified version of Makefile using g++ & gdb by Roberto Nicolas Savinelli <rsavinelli@est.frba.utn.edu.ar>
# Tomas Agustin Sanchez <tosanchez@est.frba.utn.edu.ar>

# C Compiler
CC = gcc
# Compiler Flags
CFLAGS = -Wall -Wextra -g3
# Test Compiler flags
TCFLAGS = -Wall -Wextra -Wshadow -Wno-unused-variable -Wno-unused-function -Wno-unused-result -Wno-unused-variable -Wno-pragmas -O3 -g3
# Used libraries
LIBS = -lcommons -pthread
#Log Folder
LOG_FOLDER=../log
# Build Folder
BUILD_FOLDER=../build
# Include directory
INCLUDE_DIRECTORY=./include/ ../lib/inc/
# Source directory
SOURCE_DIRECTORY=./src
# Test Directory
TEST_DIRECTORY=./test
# The main file path
MAIN_FILE= ./src/app/main.c
# The shared library source directory
LIB_DIRECTORY= ../lib/src
# Inlcude folder
INCLUDES = $(foreach dir, $(shell find $(INCLUDE_DIRECTORY) -type d -print), $(addprefix -I , $(dir)))
# The shared library source files
LIB_SOURCES = ../shared/*.o
# Source files
SOURCES = $(filter-out $(MAIN_FILE), $(shell find $(SOURCE_DIRECTORY) -name '*.c')) $(LIB_SOURCES)
# Test cases files
TESTS = $(shell find $(TEST_DIRECTORY) -name '*.c')
# Application name
APPNAME = server
# Output file name
OUTPUT = $(BUILD_FOLDER)/$(APPNAME).out
# Test Output file
TEST_OUTPUT = $(BUILD_FOLDER)/$(APPNAME)_test.out
# Leaks log file
LEAKS = log/leaks.log
# Thread chek log file
HELGRIND = log/threads.log


all : compile run

.PHONY: all

install:
	@echo Installing dependencies...
# Install required libraries here.
	@echo Installed

compile:
	@mkdir -p $(BUILD_FOLDER)
	@echo Building module: [$(APPNAME)]... 
	$(CC) $(CFLAGS) $(MAIN_FILE) $(SOURCES) $(INCLUDES) $(LIBS) -o $(OUTPUT)
	@echo Build completed.

run: compile
	./$(OUTPUT)

test-build:
	@mkdir -p $(BUILD_FOLDER)
	@echo Preparing tests...
	$(CC) $(TCFLAGS) $(TESTS) $(SOURCES) $(INCLUDES) $(LIBS) -o $(TEST_OUTPUT)
	@echo Test builds!

test: test-build
	@echo Running test cases...
	./$(TEST_OUTPUT)
	@echo Tests completed.
	
leaks: compile
	@mkdir -p log
	valgrind --leak-check=yes --log-file="$(LEAKS)" --track-origins=yes ./$(OUTPUT)

threads: compile
	@mkdir -p log
	valgrind --tool=helgrind --log-file="$(HELGRIND)" ./$(OUTPUT)

clean:
	$(RM) ./$(OUTPUT)

cleanLogs:
	$(RM) -r log || true

remove: clean cleanLogs