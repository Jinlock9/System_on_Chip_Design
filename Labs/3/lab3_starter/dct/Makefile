# ######################################################
# Define design information
# - assumes the design files are .c (update to .cpp for C++ and SystemC)
# - assumes test bench is <design>_test.c

DESIGN		 := dct
SOURCES		 := $(DESIGN).cpp $(DESIGN)_test.cpp
OBJECTS		 := $(SOURCES:.cpp=.o)
INCLUDES		 := $(DESIGN).h
CLEAN_FILES  := $(OBJECTS) $(DESIGN) $(DESIGN).exe
CLEAN_FILES  += test_data/output.dat
VITIS_HLS_CLEANUP := $(DESIGN)_prj $(DESIGN).log vitis_hls.log 
# Change to true if using ap[u]int in ISO-C project or ap_[u]int<> in C++
USE_ARBITRARY_PRECISION = false
# Change to true if using SystemC types or SC_MODULE, etc.
USE_SYSTEMC 				= false

# ######################################################
# Automatically setup the software paths
SHELL           := sh
KERNEL          := $(shell if [[ $$(uname -s) == Linux ]];then echo Linux; else echo Win; fi)
ARCH            := $(shell if [[ $$(uname -m) =~ 64$$ ]];then echo x86_64; else echo x86; fi)
OS              := $(KERNEL)_$(ARCH)
VITIS_HLS_EXE_FILENAME := vitis_hls
ifeq ($(KERNEL), Win)
APCC= $(VITIS_HLS_ROOT)/$(OS)/bin/apcc_bin.exe
else
APCC:= apcc
endif
VITIS_HLS_EXE   := $(shell which $(VITIS_HLS_EXE_FILENAME))
VITIS_HLS_ROOT  := $(VITIS_HLS_EXE:/bin/$(VITIS_HLS_EXE_FILENAME)=)
VITIS_HLS_INC_PATH := $(VITIS_HLS_ROOT)/include
SYSTEMC_INC_PATH := $(VITIS_HLS_ROOT)/$(OS)/tools/systemc/include
SYSTEMC_LIB_PATH := $(VITIS_HLS_ROOT)/$(OS)/tools/systemc/lib

# ######################################################
# Setup C compiler and options
#
# Use autocc for ISO-C projects that use ap[u]int types; gcc otherwise
ifeq ($(USE_ARBITRARY_PRECISION),true)
CC				:= $(APCC)
CFLAGS		+= -DBIT_ACCURATE
else
CC				:= gcc
endif
CXX			:= g++
# C compiler flags
CFLAGS		+= -ggdb
CFLAGS		+= -w
CFLAGS		+= -I$(VITIS_HLS_INC_PATH)
# C++ compiler flags
CXXFLAGS		+= -ggdb
CXXFLAGS		+= -I$(VITIS_HLS_INC_PATH)
# Linker flags
LDFLAGS		+= -lm -lstdc++
# # SystemC additional flags
ifeq ($(USE_SYSTEMC), true)
CXXFLAGS		+= -I$(SYSTEMC_INC_PATH)
LDFLAGS		+= -L$(SYSTEMC_LIB_PATH)
LDLIBS		+= -lsystemc
endif

# ######################################################
# Rules

all: sim

clean:
	rm -rf $(CLEAN_FILES) $(VITIS_HLS_CLEANUP)

VITIS_HLS: $(DESIGN).tcl
	VITIS_HLS $<

sim: $(DESIGN)
	./$(DESIGN)

$(DESIGN): $(OBJECTS)
# Uses implicit recipes, i.e.:
# $([CC|CXX]) $(CPPFLAGS) $([CFLAGS|CXXFLAGS]) -c # For each SOURCE
# $(CC) $(LDFLAGS) $(OBJECTS) $(LOADLIBES) $(LDLIBS) # To link OBJECTS

# TODO: add rule to rebuild OBJECT when its .h file changes
