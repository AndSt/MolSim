root := ../../..

include $(root)/build/cxx/rules.make
include $(root)/build/xsd/tree-rules.make


# Build.
#
driver: driver.o InputCuboids.o

InputCuboids.o: InputCuboids.cxx InputCuboids.hxx
driver.o: driver.cxx InputCuboids.hxx

InputCuboids.cxx InputCuboids.hxx: InputCuboids.xsd


# Test.
#
.PHONY: test
test: driver InputCuboids.xml
	./driver InputCuboids.xml


# Clean.
#
.PHONY: clean
clean:
	rm -f InputCuboids.o InputCuboids.?xx driver.o driver

