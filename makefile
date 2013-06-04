WORKDIR = `pwd`

# general options
CC = clang
CXX = clang++
AR = ar
LD = g++
WINDRES = windres

INC = -I../../gtest-1.6.0/include
CFLAGS =  -Wall
LIB = ../../gtest-1.6.0/make/gtest_main.a
LDFLAGS = -lpthread

# debug options
INC_DEBUG =  $(INC)
CFLAGS_DEBUG =  $(CFLAGS) -g
RCFLAGS_DEBUG =  $(RCFLAGS)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG =  $(LDFLAGS) 
OBJDIR_DEBUG = obj/Debug
OUT_DEBUG = bin/Debug/linReg

# release options
INC_RELEASE =  $(INC)
CFLAGS_RELEASE =  $(CFLAGS) -O3
RCFLAGS_RELEASE =  $(RCFLAGS)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE =  $(LDFLAGS)
OBJDIR_RELEASE = obj/Release
OUT_RELEASE = bin/Release/linReg

# OBJ-Files
OBJ_DEBUG = $(OBJDIR_DEBUG)/linReg.o $(OBJDIR_DEBUG)/main.o
OBJ_RELEASE = $(OBJDIR_RELEASE)/linReg.o $(OBJDIR_RELEASE)/main.o

run: release
	./$(OUT_RELEASE)

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

debug: before_debug out_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/linReg.o: linReg.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c linReg.cpp -o $(OBJDIR_DEBUG)/linReg.o

$(OBJDIR_DEBUG)/main.o: main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c main.cpp -o $(OBJDIR_DEBUG)/main.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

release: before_release out_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/linReg.o: linReg.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c linReg.cpp -o $(OBJDIR_RELEASE)/linReg.o
	
$(OBJDIR_RELEASE)/main.o: main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c main.cpp -o $(OBJDIR_RELEASE)/main.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)