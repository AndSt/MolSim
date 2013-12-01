root := ../../..

include $(root)/build/cxx/rules.make
include $(root)/build/xsd/tree-rules.make


# Build.
#
driver: driver.o InputSpheres.o

InputSpheres.o: InputSpheres.cxx InputSpheres.hxx
driver.o: driver.cxx InputSpheres.hxx

InputSpheres.cxx InputSpheres.hxx: InputSpheres.xsd


# Test.
#
.PHONY: test
test: driver InputSpheres.xml
	./driver InputSpheres.xml


# Clean.
#
.PHONY: clean
clean:
	rm -f InputSpheres.o InputSpheres.?xx driver.o driver

