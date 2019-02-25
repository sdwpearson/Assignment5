// report.cc
// Author: Stewart Pearson
// Date: February 23, 2019
// PHY1610 Assignment 5
//
// Description: This file reports the current state of the time, Regular people, Zombie killers, and Zombies in
// a netCDF file. On the first iteration it creates the file and on subsequent ones it appends to the existing
// file. For each different value of Z0 it will create a new variable.

#include <rarray>
#include <netcdf>
#include <iostream>
#include <vector>
#include "report.h"

using namespace netCDF;
using namespace netCDF::exceptions;

void report_state(const rarray<double,1>& x, const char* filename, int length, const double t, const double INITIAL_Z0){ 

    // Each different Z0 array will have a different name 
    // ex. for Z0 = 3, the variable name will be "MZA_Z0_3"
    std::string array_name = "MZA_Z0_";
    int array_number = (int)x[3];
    array_name += std::to_string(array_number);

    if(t <= 0.00001){
        try
        {  
            if(array_number == INITIAL_Z0){
                // Create/Overwrite a new file. 
                NcFile dataFile(filename, NcFile::replace);

                // Create netCDF dimensions
                NcDim timeDim = dataFile.addDim("time"+std::to_string(array_number));
                NcDim stateDim = dataFile.addDim("state", length+1);
              
                // Define the variable. The type of the variable in this case is
                // ncDouble (64-bit float).
                std::vector<NcDim> dims;
                dims.push_back(timeDim);
                dims.push_back(stateDim);
                NcVar data = dataFile.addVar(array_name, ncDouble, dims);
           
                // create an index vector to select the data
                std::vector<size_t> startp;
                startp.push_back(0);
                startp.push_back(0);

                // copy the data from the state array into the netCDF variable               
                data.putVar(startp, t);
                for(int i = 0; i < length; i++){
                    startp[1] = i+1;  
                    data.putVar(startp, x[i]);
                }
            } 
            else {
                // Create the file. 
                NcFile dataFile(filename, NcFile::write);

                // See if the variable was successfully created
                if(dataFile.isNull()) {
                    std::cout << "file named: " << filename << " can not be accessed. Exiting..." << std::endl;
                    return;
                }

                // Create netCDF dimensions
                NcDim timeDim = dataFile.addDim("time"+std::to_string(array_number));
                NcDim stateDim = dataFile.getDim("state");
              
                // Define the variable. The type of the variable in this case is
                // ncDouble (64-bit float).
                std::vector<NcDim> dims;
                dims.push_back(timeDim);
                dims.push_back(stateDim);
                NcVar data = dataFile.addVar(array_name, ncDouble, dims);

                // See if the variable was successfully created
                if(data.isNull()) {
                    std::cout << "Variable named: " << array_name << " can not be created. Exiting..." << std::endl;
                    return;
                }
           
                // create an index vector to select the data
                std::vector<size_t> startp;
                startp.push_back(0);
                startp.push_back(0);

                // copy the data from the state array into the netCDF variable                
                data.putVar(startp, t);
                for(int i = 0; i < length; i++){
                    startp[1] = i+1;  
                    data.putVar(startp, x[i]);
                }
            }
        }
        catch(NcException& e){
            std::cout << "Exception caught: " << e.what() << std::endl;
            e.what();
        }
    } 
    else {
        try
        {  
            // Create the file. The Write parameter allows us to edit the 
            // netCDF file.
            NcFile dataFile(filename, NcFile::write);

            // Get the variable for the MZA array to append to
            NcVar data = dataFile.getVar(array_name);

            // See if the variable was successfully retrieved
            if(data.isNull()) {
                std::cout << "No variable named: " << array_name << " exiting..." << std::endl;
                return;
            }

            // Get the current time iteration to write to the next line in the array
            size_t time_index = data.getDim(0).getSize();

            // create an index vector to select the data            
            std::vector<size_t> indexp;
            indexp.push_back(time_index); 
            indexp.push_back(0);

            // copy the data from the state array into the netCDF variable               
            data.putVar(indexp, t);
            for(int i = 0; i < length; i++){
                indexp[1] = i+1;  
                data.putVar(indexp, x[i]);
            }
        }
        catch(NcException& e){
            std::cout << "Exception caught: " << e.what() << std::endl;
            e.what();
        }
    }
            
    // The file will be automatically closed when the NcFile object goes
    // out of scope. This frees up any internal netCDF resources
    // associated with the file, and flushes any buffers.
}