PRODUCT=StateTest

GTEST_VER=1.14.0
GTEST_INC_DIR= ../gtest/googletest-$(GTEST_VER)/googlemock/include
GTEST_LIB_DIR=../gtest/googletest-$(GTEST_VER)/lib

CPPFLAGS=-Iproduct -Itest
CXXFLAGS=-Wall -Werror -Wextra -pedantic -ggdb -O0 $(CPPFLAGS)

SOURCES=$(wildcard product/*.cpp) \
        $(wildcard test/*.cpp)

HEADERS=$(wildcard product/*.h) \
        $(wildcard test/*.h)

LDFLAGS=-lgtest -lgtest_main -lgmock -lgmock_main -lpthread

INC_DIR=$(GTEST_INC_DIR)
INC_LIB_DIR=$(GTEST_LIB_DIR)

CXX=g++

.PHONY: all clean test

all: $(PRODUCT)

$(PRODUCT): $(SOURCES) $(HEADERS)
	$(CXX) -L$(INC_LIB_DIR) -I$(INC_DIR) $(CXXFLAGS) $(SOURCES) -o $@ $(LDFLAGS)

clean:
	@rm -rf $(PRODUCT)

test: $(PRODUCT)
	@./$(PRODUCT)
