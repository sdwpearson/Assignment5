CXX=g++
CXXFLAGS=-std=c++11 -g -O3 -march=native
CXXTESTFLAGS=-std=c++11 -g 
CXXFLAGS=-std=c++11 -g -O2 -march=native -ftree-vectorize -Wall

# netCDF includes and libraries for it to function
NETCDF_INC = /scinet/teach/software/2018a/opt/gcc-7.3.0/netcdf/4.6.1/include
NETCDF_LIB = /scinet/teach/software/2018a/opt/gcc-7.3.0/netcdf/4.6.1/lib

LDFLAGS=-g
LDLIBS= -lnetcdf_c++4
LDBOOST = -lboost_unit_test_framework

all: MZA

clean: 
	\rm -f report.o MZA.o MZA.nc

report.o: report.cc report.h
	${CXX} ${CXXFLAGS} -I${NETCDF_INC} -c -o $@ $<

MZA.o: MZA.cc report.h
	${CXX} ${CXXFLAGS} -c -o $@ $<

MZA: MZA.o report.o
	${CXX} ${LDFLAGS} -L${NETCDF_LIB} -o $@ $^ ${LDLIBS}

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







