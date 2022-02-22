# C Makefile using gcc, gdb and valgrind. 
# Modified version of Makefile using g++ & gdb by Roberto Nicolas Savinelli <rsavinelli@est.frba.utn.edu.ar>
# Tomas Agustin Sanchez <tosanchez@est.frba.utn.edu.ar>

# Build directory
BUILD_DIR=build
# Log directory
LOG_DIR=log


# Modules directories - with their own makefile
SERVER_DIR=server

# Directories list
DIRS = $(SERVER_DIR)

# Compile script
MAKE_COMPILE = $(MAKE) compile --no-print-directory
# Test script
MAKE_TEST = $(MAKE) test --no-print-directory

# Test Scrpt for each application
TEST_ALL=$(foreach dir, $(DIRS), cd $(dir) && $(MAKE_TEST) && cd .. &&)

# Todas las aplicaciones
all: server

.PHONY: server clean install test

compile: all

install:
	@echo Installing dependencies...
# Install required libraries here.
	@echo Installed

test:
	$(TEST_ALL) true

server:
	cd $(SERVER_DIR) && $(MAKE_COMPILE)

clean:
	rm -fr $(BUILD_DIR)
