####################################################################################################
#
#	Help
#
#	1. Configuring
#		This make-file is configured for Windows mingw compiler.
#		If you want to use this make-file to build the library on your
#		machine you only need to redefine platform-specific variables.
#
#	2. Targets
#		- debug
#		- release
#		- test
#		- clean
#
####################################################################################################



####################################################################################################
#
#	Variables
#
####################################################################################################


#	Standard variables
COMPILE=$(COMPILER) $(PROJECT_STANDARD) $(COMPILER_COMPILE_OPTIONS)
COMPILE_DEBUG=$(COMPILE) $(COMPILER_DEBUG_OPTIONS)
COMPILE_RELEASE=$(COMPILE) $(COMPILER_RELEASE_OPTIONS)
LINK=$(COMPILER) $(PROJECT_STANDARD) $(COMPILER_LINK_OPTIONS)
LINK_DEBUG=$(LINK) $(COMPILER_DEBUG_OPTIONS)
LINK_RELEASE=$(LINK) $(COMPILER_RELEASE_OPTIONS)
ARCHIVE=$(ARCHIVER) $(ARCHIVER_OPTIONS)
INDEX=$(INDEXER) $(INDEXER_OPTIONS)
DELETE=$(DELETER) $(DELETER_OPTIONS)
PROJECT_OBJECT_DIR=obj$(_)
PROJECT_LIBRARY_DIR=lib$(_)
PROJECT_HEADER_FILE=$(PROJECT_NAME).hpp
PROJECT_SOURCE_FILE=$(PROJECT_NAME).cpp
PROJECT_OBJECT_FILE=$(PROJECT_OBJECT_DIR)$(PROJECT_NAME)$(EXTENSION_OBJ)
PROJECT_LIBRARY_FILE=$(PROJECT_LIBRARY_DIR)$(PROJECT_NAME)$(EXTENSION_LIB)
TEST_SOURCE_DIR=test$(_)src$(_)
TEST_BINARY_DIR=test$(_)bin$(_)
TEST_SOURCE_FILE=$(TEST_SOURCE_DIR)test.cpp
TEST_BINARY_FILE=$(TEST_BINARY_DIR)test$(EXTENSION_BIN)


#	Platform-specific variables
COMPILER=mingw32-g++
COMPILER_OUTPUT_OPTION=-o
COMPILER_COMPILE_OPTIONS=-c
COMPILER_LINK_OPTIONS=-Wall
COMPILER_DEBUG_OPTIONS=
COMPILER_RELEASE_OPTIONS=-O2 -s -DNDEBUG
MAKE=mingw32-make
MAKE_CHANGE_DIRECTORY=-C
ARCHIVER=ar
ARCHIVER_OPTIONS=cr
INDEXER=ranlib
INDEXER_OPTIONS=
DELETER=del
DELETER_OPTIONS=/f /q
EXTENSION_OBJ=.obj
EXTENSION_LIB=.lib
EXTENSION_BIN=.exe
FILE_MASK_ANY=*
FILE_RUN=
_=\\


#	Project-specific variables
PROJECT_STANDARD=-std=c++03
PROJECT_NAME=Random



####################################################################################################
#
#	Targets
#
####################################################################################################


debug: $(PROJECT_HEADER_FILE) $(PROJECT_SOURCE_FILE)
	$(COMPILE_DEBUG) $(PROJECT_SOURCE_FILE) $(COMPILER_OUTPUT_OPTION) $(PROJECT_OBJECT_FILE)
	$(ARCHIVE) $(PROJECT_LIBRARY_FILE) $(PROJECT_OBJECT_FILE)
	$(INDEX) $(PROJECT_LIBRARY_FILE)

release: $(PROJECT_HEADER_FILE) $(PROJECT_SOURCE_FILE)
	$(COMPILE_RELEASE) $(PROJECT_SOURCE_FILE) $(COMPILER_OUTPUT_OPTION) $(PROJECT_OBJECT_FILE)
	$(ARCHIVE) $(PROJECT_LIBRARY_FILE) $(PROJECT_OBJECT_FILE)
	$(INDEX) $(PROJECT_LIBRARY_FILE)

test: debug $(TEST_SOURCE_FILE)
	$(LINK_DEBUG) $(TEST_SOURCE_FILE) $(PROJECT_LIBRARY_FILE) $(COMPILER_OUTPUT_OPTION) $(TEST_BINARY_FILE)
	$(FILE_RUN)$(TEST_BINARY_FILE)


clean:
	$(DELETE) $(PROJECT_OBJECT_DIR)$(FILE_MASK_ANY)$(EXTENSION_OBJ)
	$(DELETE) $(PROJECT_LIBRARY_DIR)$(FILE_MASK_ANY)$(EXTENSION_LIB)
	$(DELETE) $(TEST_BINARY_DIR)$(FILE_MASK_ANY)$(EXTENSION_BIN)