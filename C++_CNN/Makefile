TARGET = CNN_test
DIRNAME = `basename $(PWD)`
SRCDIR = src
INCDIR = include
TESTDIR = test

ACTYPESDIR = ../ac_types/include
ACMATHDIR = ../ac_math/include


CXX = `which g++`
RM = `which rm` -f
DOXYGEN = `which doxygen`
CXXFLAGS =  -std=c++11 -Wall

INCLUDE =  -I$(INCDIR) -I$(ACTYPESDIR) -I$(ACMATHDIR)
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)
TEST = $(wildcard $(TESTDIR)/*.cpp)
OBJTEST = $(TEST:.cpp=.o)

all :
		@echo "in " $(DIRNAME)
		@echo ""
		@echo "Usage:"
		@echo "CNN_test => generate executable file"
		@echo "clean => clean up the .o .pgm files"
		@echo "mrproper => clean up everything"


$(TARGET) : $(OBJTEST) $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $^

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $^


.PHONY: clean mrproper

clean :
	$(RM)  gen_pic/*

mrproper :
	make clean
	$(RM) test.exe $(OBJ) $(OBJTEST)
