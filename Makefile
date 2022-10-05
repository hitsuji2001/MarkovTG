### Source: https://www.youtube.com/watch?v=DtGrdB8wQ_8&t

EXEC			:= main
SOURCE_DIRECTORIES	:= ./src
HEADER_DIRECTORIES	:= ./header

CC                      := gcc
CXX			:= g++
OPT			:= -O0
# Generate files that encode make rules for the .h and .hpp dependencies
DEPFLAGS		:= -MP -MD
DEBUG_FLAGS             := -g -ggdb
# Automatically add -I flag to include directory
INCL_FLAGS		:= $(foreach D, $(HEADER_DIRECTORIES), -I$(D))
LINK_FLAGS		:= 

CXXFLAGS		:= -Wall -Werror -Wextra $(INCL_FLAGS) $(OPT) $(DEPFLAGS) $(DEBUG_FLAG)
CFLAGS                  := $(CXXFLAGS) -lstdc++

CPP_FILES		:= $(foreach D, $(SOURCE_DIRECTORIES), $(wildcard $(D)/*.cpp))
C_FILES                 := $(foreach D, $(SOURCE_DIRECTORIES), $(wildcard $(D)/*.c))

OBJ_FILES		:= $(patsubst %.cpp, %.o, $(CPP_FILES)) $(patsubst %.c, %.o, $(C_FILES))
DEP_FILES		:= $(patsubst %.cpp, %.d, $(CPP_FILES)) $(patsubst %.c, %.d, $(C_FILES))

all : $(EXEC)

$(EXEC) : $(OBJ_FILES)
	$(CXX) -o $@ $^ $(LINK_FLAGS)

%.o : %.c %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(EXEC) $(OBJ_FILES) $(DEP_FILES)
