####### Compiler, tools and options
CXX           = g++
CXXFLAGS      = -pthread -std=c++11 -pedantic -Wall -Wextra
LFLAGS        = -Wall -pthread
INCPATH       = -I. -I/usr/local/include
LIBS	      = -L/usr/local/lib -lre2
DEL_FILE      = rm -f

####### Files

SOURCES       = src/main.cpp \
		src/master/Master.cpp \
		src/htmlfile/HtmlFile.cpp \
		src/cssfile/CssFile.cpp \
		src/Globals.cpp 
OBJECTS       = main.o \
		Master.o \
		HtmlFile.o \
		CssFile.o \
		Globals.o
TARGET        = xht2html



first: all

####### Build rules

all: $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(CXX) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

clean:
	-$(DEL_FILE) $(OBJECTS) $(TARGET)
	-$(DEL_FILE) *~ core *.core

####### Compile

main.o: src/main.cpp src/master/Master.hpp \
		src/htmlfile/HtmlFile.hpp \
		src/cssfile/CssFile.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o src/main.cpp

Master.o: src/master/Master.cpp src/master/Master.hpp \
		src/htmlfile/HtmlFile.hpp \
		src/cssfile/CssFile.hpp \
		src/Globals.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Master.o src/master/Master.cpp

HtmlFile.o: src/htmlfile/HtmlFile.cpp src/htmlfile/HtmlFile.hpp \
		src/Globals.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o HtmlFile.o src/htmlfile/HtmlFile.cpp

CssFile.o: src/cssfile/CssFile.cpp src/cssfile/CssFile.hpp \
		src/Globals.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CssFile.o src/cssfile/CssFile.cpp

Globals.o: src/Globals.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Globals.o src/Globals.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:


