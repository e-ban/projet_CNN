DIRNAME = `basename $(PWD)`
SRCDIR = src
INCDIR = include
ACTYPESDIR = ../ac_types/include
ACMATHDIR = ../ac_math/include
INC =  -I$(INCDIR)
CXX = g++
CPPFLAGS =   -Wall -std=c++11 $(INC) -I$(ACTYPESDIR) -I$(ACMATHDIR)
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

test : $(OBJ)
			$(CXX) $^ $(CPPFLAGS) -o test

clean :
	rm *.o mytest
