# C Makefile using gcc, gdb and valgrind. 
# Modified version of Makefile using g++ & gdb by Roberto Nicolas Savinelli <rsavinelli@est.frba.utn.edu.ar>
# Tomas Agustin Sanchez <tosanchez@est.frba.utn.edu.ar>

# Build directory
BUILD_DIR=build
# Log directory
LOG_DIR=log
# Shared Library directory
LIB_DIR=lib
# Shared object directory
OBJ_DIR=shared
# Commons name
COMMONS=so-commons-library

# Modules directories - with their own makefile
SERVER_DIR=server
CLIENT_DIR=client

# Directories list
DIRS = $(SERVER_DIR) $(CLIENT_DIR)

# Compile script
MAKE_COMPILE = $(MAKE) compile --no-print-directory
# Test script
MAKE_TEST = $(MAKE) test --no-print-directory

# Test Scrpt for each application
TEST_ALL=$(foreach dir, $(DIRS), cd $(dir) && $(MAKE_TEST) && cd .. &&)

# Todas las aplicaciones
all: server client

.PHONY: server client clean install test install-commons

compile: all

install:
	@echo Installing dependencies...
# Install required libraries here.
	@echo "\nInstalling readline"
	apt-get install libreadline-dev
	@echo "\nReadline installed!\n"
	@echo "\nInstalling commons libraries...\n" 
	@echo $(PWD)
	rm -rf $(COMMONS)
	git clone "https://github.com/sisoputnfrba/$(COMMONS).git" $(COMMONS)
	cd $(COMMONS) && sudo make uninstall --no-print-directory && sudo make install --no-print-directory && cd ..
	rm -rf $(COMMONS)
	@echo "\nCommons installed\n"
	@echo "Building shared libraries...\n" 
	rm -fr $(OBJ_DIR)
	cd $(LIB_DIR) && $(MAKE_COMPILE) && cd ..
	@echo "Shared libraries built!\n" 
	@echo Completed

test:
	$(TEST_ALL) true

server:
	cd $(SERVER_DIR) && $(MAKE_COMPILE)

client:
	cd $(CLIENT_DIR) && $(MAKE_COMPILE)

clean:
	rm -fr $(BUILD_DIR)

	