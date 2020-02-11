TARGET = CNN_test.exe
DIRNAME = `basename $(PWD)`
SRCDIR = src
INCDIR = include
TESTDIR = test
OUTPUTDIR = output
DOCDIR = docs

ACTYPESDIR = $(LIB_CNN)/ac_types/include
ACMATHDIR = $(LIB_CNN)/ac_math/include


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
		@echo $(TARGET)" => generate executable file"
		@echo "docu => generate documentation"
		@echo "clean => clean up the .o .pgm files and docs folder"
		@echo "mrproper => clean up everything"

docu :
	$(DOXYGEN) Doxyfile


$(TARGET) : $(TESTDIR)/ioImage.o $(TESTDIR)/testbench.o $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $^
	mkdir -p $(OUTPUTDIR)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $^


.PHONY: clean mrproper

clean :
	$(RM) $(OUTPUTDIR)/*
	rm -rf $(DOCDIR)

mrproper :
	rm -rf $(OUTPUTDIR)
	$(RM) $(TARGET) $(OBJ) $(OBJTEST)
