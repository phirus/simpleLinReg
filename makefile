WORKDIR = `pwd`

# general options
CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

# release options
CFLAGS =  -Wall -O3
RCFLAGS_RELEASE =  $(RCFLAGS)
OBJDIR_RELEASE = obj
BINDIR = bin
OUT_RELEASE = $(BINDIR)/linReg

# OBJ-Files
OBJ = $(OBJDIR_RELEASE)/linReg.o $(OBJDIR_RELEASE)/main.o

before_release: 
	test -d $(BINDIR) || mkdir -p $(BINDIR)
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

out_release: before_release $(OBJ) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ)

$(OBJDIR_RELEASE)/linReg.o: src/linReg.cpp
	$(CXX) $(CFLAGS) -c src/linReg.cpp -o $(OBJDIR_RELEASE)/linReg.o
	
$(OBJDIR_RELEASE)/main.o: src/main.cpp
	$(CXX) $(CFLAGS) -c src/main.cpp -o $(OBJDIR_RELEASE)/main.o

release: before_release out_release

clean: 
	rm -f $(OBJ) $(OUT_RELEASE)
	rm -rf $(BINDIR)
	rm -rf $(OBJDIR_RELEASE)

cleanbuild: clean release
	
cleanrun: clean release
	./$(OUT_RELEASE)