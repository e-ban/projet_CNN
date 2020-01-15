DIRNAME = `basename $(PWD)`
SRCDIR = src
INCDIR = include
ACTYPESDIR = ../ac_types/include

INC =  -I$(INCDIR)
CXX = g++
CPPFLAGS =  -Wall -std=c++11 $(INC) -I$(ACTYPESDIR)
SRC = $(wildcard $(SRCDIR)/*.cpp)

OBJ=$(SRC:.c=.o)
all :
		@echo "in " $(DIRNAME)
		@echo ""
		@echo "Usage:"
		@echo ""
		@echo "build ===> compile toutes les sources"

%.o : %.cpp
		$(CXX) $< $(CPPFLAGS) -c -o $(basename $<).o

testinput : $(SRCDIR)/loadPicture.cpp
						$(CXX) $(SRCDIR)/loadPicture.cpp $(CPPFLAGS) -o mytest

testConvol : $(OBJ)
						$(CXX) $^ $(CPPFLAGS) -o testConv

clean :
	rm *.o mytest
