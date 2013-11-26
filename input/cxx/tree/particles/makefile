root := ../../..

include $(root)/build/cxx/rules.make
include $(root)/build/xsd/tree-rules.make


# Build.
#
driver: driver.o InputParticles.o

InputParticles.o: InputParticles.cxx InputParticles.hxx
driver.o: driver.cxx InputParticles.hxx

InputParticles.cxx InputParticles.hxx: InputParticles.xsd


# Test.
#
.PHONY: test
test: driver InputParticles.xml
	./driver InputParticles.xml


# Clean.
#
.PHONY: clean
clean:
	rm -f InputParticles.o InputParticles.?xx driver.o driver

