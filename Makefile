# This is a makefile template


# Compiler
# --------
CC=g++
##CC=icpc

include files.mk

# Compiler flags
# -------------------------------------------------------------------------


CFLAGS=-g -O3 -DNDEBUG
#CFLAGS= -O3 -ip -ipo -fast

# Linker flags
# ------------
LDFLAGS= -lxerces-c -lcppunit -llog4cxx
 
INCLUDES= -I./src -I./libxsd -I./libxsd/xsd

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=MolSim

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ 
	
clean:
	rm $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
