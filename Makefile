# This is a makefile template


# Compiler
# --------
CC=g++
#CC=icpc

include files.mk

LIB_A = "input/cxx/tree/setting"
LIB_B = "input/cxx/tree/cuboids"
LIB_C = "input/cxx/tree/particles"

# Compiler flags
# -------------------------------------------------------------------------
CFLAGS=-g -O3

# Linker flags
# ------------
LDFLAGS= -lxerces-c -lcppunit -llog4cxx
 
INCLUDES= -I./src -I./libxsd -I./libxsd/xsd -I./input/cxx/tree -I./input/cxx/tree/cuboids

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=MolSim
MY_TARGETS = $(LIB_A) $(LIB_B) $(LIB_C)

.PHONY: all $(MY_TARGETS)
all: $(MY_TARGETS) $(SOURCES) $(EXECUTABLE)

$(MY_TARGETS):
	@$(MAKE) -C $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ 
	
clean:
	rm $(OBJECTS)
	cd "input/cxx/tree/setting"; rm -f InputSetting.o InputSetting.?xx driver.o driver
	cd "input/cxx/tree/cuboids"; rm -f InputCuboids.o InputCuboids.?xx driver.o driver
	cd "input/cxx/tree/particles"; rm -f InputParticles.o InputParticles.?xx driver.o driver
	

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
