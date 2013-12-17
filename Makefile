# This is a makefile template


# Compiler
# --------
CC=g++
#CC=icpc

include files.mk

LIB_SET = "input/cxx/tree/setting"
LIB_PAR = "input/cxx/tree/particles"
LIB_CUB = "input/cxx/tree/cuboids"
LIB_SPH = "input/cxx/tree/spheres"
UTILS = "src/utils"

INP_SET_XML = "InputSetting.xml"
INP_SET_XSD = "InputSetting.xsd"
INP_PAR_XML = "InputParticles.xml"
INP_PAR_XSD = "InputParticles.xsd"
INP_CUB_XML = "InputCuboids.xml"
INP_CUB_XSD = "InputCuboids.xsd"
INP_SPH_XML = "InputSpheres.xml"
INP_SPH_XSD = "InputSpheres.xsd"


# Compiler flags
# -------------------------------------------------------------------------
CFLAGS=-g -O3

# Linker flags
# ------------
LDFLAGS= -lxerces-c -lcppunit -llog4cxx
 
INCLUDES= -I./src -I./libxsd -I./libxsd/xsd -I./input/cxx/tree

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=MolSim
MY_TARGETS = $(LIB_SET) $(LIB_PAR) $(LIB_CUB) $(LIB_SPH)
MY_INP_SET = $(INP_SET_XML) $(INP_SET_XSD)
MY_INP_PAR = $(INP_PAR_XML) $(INP_PAR_XSD)
MY_INP_CUB = $(INP_CUB_XML) $(INP_CUB_XSD)
MY_INP_SPH = $(INP_SPH_XML) $(INP_SPH_XSD)

.PHONY: $(MY_TARGETS)
all: replacing $(SOURCES) $(EXECUTABLE)

.PHONY: replacing
replacing: cloning
	sed -i 's/InputSetting.hxx/InputSetting.h/g' $(UTILS)/InputSetting.cpp
	sed -i 's/InputParticles.hxx/InputParticles.h/g' $(UTILS)/InputParticles.cpp
	sed -i 's/InputCuboids.hxx/InputCuboids.h/g' $(UTILS)/InputCuboids.cpp
	sed -i 's/InputSpheres.hxx/InputSpheres.h/g' $(UTILS)/InputSpheres.cpp

.PHONY: cloning
cloning: $(MY_TARGETS)
	cp $(LIB_SET)/InputSetting.hxx $(UTILS)/InputSetting.h
	cp $(LIB_SET)/InputSetting.cxx $(UTILS)/InputSetting.cpp
	cp $(LIB_PAR)/InputParticles.hxx $(UTILS)/InputParticles.h
	cp $(LIB_PAR)/InputParticles.cxx $(UTILS)/InputParticles.cpp
	cp $(LIB_CUB)/InputCuboids.hxx $(UTILS)/InputCuboids.h
	cp $(LIB_CUB)/InputCuboids.cxx $(UTILS)/InputCuboids.cpp
	cp $(LIB_SPH)/InputSpheres.hxx $(UTILS)/InputSpheres.h
	cp $(LIB_SPH)/InputSpheres.cxx $(UTILS)/InputSpheres.cpp

$(MY_TARGETS):
	cp $(MY_INP_SET) $(LIB_SET)
	cp $(MY_INP_PAR) $(LIB_PAR)
	cp $(MY_INP_CUB) $(LIB_CUB)
	cp $(MY_INP_SPH) $(LIB_SPH)
	@$(MAKE) -C $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ -pg
	
clean:
	rm $(OBJECTS)
	cd $(LIB_SET); rm -f InputSetting.o InputSetting.?xx driver.o driver InputSetting.xml InputSetting.xsd
	cd $(LIB_PAR); rm -f InputParticles.o InputParticles.?xx driver.o driver InputParticles.xml InputParticles.xsd
	cd $(LIB_CUB); rm -f InputCuboids.o InputCuboids.?xx driver.o driver InputCuboids.xml InputCuboids.xsd
	cd $(LIB_SPH); rm -f InputSpheres.o InputSpheres.?xx driver.o driver InputSpheres.xml InputSpheres.xsd
	
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -pg
