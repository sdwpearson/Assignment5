CXX=g++
CXXFLAGS=-std=c++11 -g -O3 -march=native
CXXTESTFLAGS=-std=c++11 -g 
CXXFLAGS=-std=c++11 -g -O2 -march=native -ftree-vectorize -Wall

LDFLAGS=-g
LDLIBS=
LDBOOST = -lboost_unit_test_framework

all: MZA

clean: 
	\rm -f report.o MZA.o 

report.o: report.cc report.h
	${CXX} ${CXXFLAGS} -c -o $@ $<

MZA.o: MZA.cc report.h
	${CXX} ${CXXFLAGS} -c -o $@ $<

MZA: MZA.o report.o  
	${CXX} ${LDFLAGS} -o $@ $^ ${LDLIBS}

run: MZA
	./MZA

help:
	@echo Type:
	@echo " 'make all'                	to compile the MZA application;"
	@echo " 'make clean'            	to remove output files;"
	@echo " 'make report.o'            	to compile the reporting module;"
	@echo " 'make MZA.o'            	to compile the MZA linking files;"
	@echo " 'make MZA'            		to compile the MZA application;"
	@echo " 'make run'	            	to run the MZA application;"







