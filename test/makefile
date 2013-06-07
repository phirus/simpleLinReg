WORKDIR = `pwd`

# general options
CC = clang
CXX = clang++
AR = ar
LD = g++
WINDRES = windres

INC = -I../../../gtest-1.6.0/include
CFLAGS =  -Wall
LIB = ../../../gtest-1.6.0/make/gtest_main.a
LDFLAGS = -lpthread

# release options
INC_RELEASE =  $(INC)
CFLAGS_RELEASE =  $(CFLAGS) -O3
RCFLAGS_RELEASE =  $(RCFLAGS)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE =  $(LDFLAGS)
OBJDIR_RELEASE = obj
BIN_RELEASE = bin
OUT_RELEASE = $(BIN_RELEASE)/linReg

# OBJ-Files
OBJ_RELEASE = $(OBJDIR_RELEASE)/linReg.o $(OBJDIR_RELEASE)/main.o

before_release: 
	test -d $(BIN_RELEASE) || mkdir -p $(BIN_RELEASE)
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/linReg.o: ../src/linReg.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ../src/linReg.cpp -o $(OBJDIR_RELEASE)/linReg.o
	
$(OBJDIR_RELEASE)/main.o: main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c main.cpp -o $(OBJDIR_RELEASE)/main.o

release: before_release out_release

clean: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf $(BIN_RELEASE)
	rm -rf $(OBJDIR_RELEASE)

cleanbuild: clean release
	
cleanrun: clean release
	./$(OUT_RELEASE)

