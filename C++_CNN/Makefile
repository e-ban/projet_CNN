DIRNAME = `basename $(PWD)`
SRCDIR = src
INCDIR = include
ACTYPESDIR = ../ac_types/include

INC =  $(INCDIR)
CXX = g++
CPPFLAGS =  -Wall -std=c++11 -I$(INC) -I$(ACTYPESDIR)
SRC = $(wildcard $(SRCDIR)/*.cpp)

all :
		@echo "in " $(DIRNAME)
		@echo ""
		@echo "Usage:"
		@echo ""
		@echo "build ===> compile toutes les sources"

%.o : %.cpp
		$(CXX) $< $(CPPFLAGS) -c -o $(basename $<).o
