PRODUCT=QueueTest

CPPFLAGS=-Iproduct -Itest -I../mystack/product
CXXFLAGS=-Wall -Werror -Wextra -pedantic -ggdb -O0 $(CPPFLAGS) -fPIC

SOURCES=$(wildcard product/*.cpp) \
        $(wildcard test/*.cpp)

HEADERS=$(wildcard product/*.h) \
        $(wildcard test/*.h) \

STACK_SRC = $(wildcard ../mystack/product/*.cpp)
STACK_OBJS = $(STACK_SRC:.cpp=.o)
TEST_OBJS = $(SOURCES:.cpp=.o)

STACKLIB = libmystack.so

LDFLAGS=-L. -lmystack -lgtest -lgmock_main -lpthread -lgmock 
LD_SHARE_FLAGS = -shared  

CXX=g++
LD=g++

.PHONY: all clean test

all: $(PRODUCT) 

$(STACKLIB): $(STACK_OBJS)
	$(LD) $(LD_SHARE_FLAGS) -o $@ $^

$(PRODUCT): $(STACKLIB) $(TEST_OBJS) $(HEADERS)
	$(LD) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	@rm -rf $(PRODUCT)
	@rm ../mystack/product/*.o
	@rm  $(STACKLIB)
	@rm -rf kwinject.out .kwlp .kwps

klocwork:
	@kwcheck run

klocwork_after_makefile_change: clean
	@/opt/klocwork/kwenv.sh
	@kwcheck run

test: $(PRODUCT)
	@./$(PRODUCT)
