root := ../../..

include $(root)/build/cxx/rules.make
include $(root)/build/xsd/tree-rules.make


# Build.
#
driver: driver.o InputSetting.o

InputSetting.o: InputSetting.cxx InputSetting.hxx
driver.o: driver.cxx InputSetting.hxx

InputSetting.cxx InputSetting.hxx: InputSetting.xsd


# Test.
#
.PHONY: test
test: driver InputSetting.xml
	./driver InputSetting.xml


# Clean.
#
.PHONY: clean
clean:
	rm -f InputSetting.o InputSetting.?xx driver.o driver

