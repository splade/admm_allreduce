
#OPT ?= -O2 -DNDEBUG       # (A) Production use (optimized mode)
#OPT ?= -g2  # (B) Debug mode, w/ full line-level debugging symbols
#OPT ?= -O2 -g2 -DNDEBUG # (C) Symbol mode: opt, but w/debugging symbols
OPT ?= -O3 -g2 -DNDEBUG # (D) Symbol mode: aggressive opt, but w/debugging symbols

CC=gcc
CXX=g++

CFLAGS += -I./ -I./include -I./src -Wall $(OPT) -pthread -fPIC 
CXXFLAGS += -std=c++0x -I. -I./include -I./src -Wall $(OPT) -pthread -fPIC 
             
LDFLAGS += -rdynamic -L./lib -L/usr/local/lib 
  
LIBS += -lpthread -lgflags -lglog \
        -ltcmalloc_minimal -lunwind \
        -llbfgs -lallreduce

LIBOBJECTS = src/sample_set.o \
			 src/admm_optimizer.o \
			 src/lr/admm_lrl2.o

TESTS = 

TESTOBJECTS = $(TESTS:.cc=.o)

all: program

check: all_test
	LD_LIBRARY_PATH=./lib:/usr/local/lib ./all_test

clean:
	rm -rf $(TESTOBJECTS) $(LIBOBJECTS) all_test admm_main

lint:
	python cpplint.py  src/*.h src/*.cc src/*.cpp

program: $(LIBOBJECTS) src/admm_main.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIBOBJECTS) src/admm_main.cpp -o admm_main $(LIBS)

all_test: $(LIBOBJECTS) $(TESTOBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIBOBJECTS) $(TESTOBJECTS) -o all_test test/gtest-all.cc test/gtest_main.cc $(LIBS)

.cc.o: 
	$(CXX) $(CXXFLAGS) -c $< -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@


