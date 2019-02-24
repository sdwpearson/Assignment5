// report.cc
// Author: Stewart Pearson
// Date: February 23, 2019
// PHY1610 Assignment 5
//
// Description: This file reports the current state of the Regular people, Zombie killers, and Zombies 

#include <rarray>
#include <netcdf>
#include <iostream>
#include <vector>
#include "report.h"

using namespace netCDF;
using namespace netCDF::exceptions;

void report_state(const rarray<double,1>& x, const char* filename, int length, const double t){ 

    // Each different Z0 array will have a different name
    std::string array_name = "MZA_Z0_";
    array_name += std::to_string(x[3]);

    if(t == 0){
        try
        {  
            if(x[3] == 5){
                // Create/Overwrite a new file. 
                NcFile dataFile(filename, NcFile::replace);
                
                // Create netCDF dimensions
                NcDim timeDim = dataFile.addDim("time");
                NcDim stateDim = dataFile.addDim("state", length);
              
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
                for(int i = 0; i < length; i++){
                    startp[1] = i;  
                    data.putVar(startp, x[i]);
                }
            } 
            else {
                // Create the file. 
                NcFile dataFile(filename, NcFile::write);

                // Create netCDF dimensions
                NcDim timeDim = dataFile.addDim("time");
                NcDim stateDim = dataFile.addDim("state", length);
              
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
                for(int i = 0; i < length; i++){
                    startp[1] = i;  
                    data.putVar(startp, x[i]);
                }
            }
        }
        catch(NcException& e){
            e.what();
        }
    } 
    else {
        try
        {  
            // Create the file. The Write parameter allows us to edit the 
            // netCDF file.
            NcFile dataFile(filename, NcFile::write);

            // Get the variable for the ants array
            NcVar data = dataFile.getVar(array_name);
            // See if the variable was successfully retrieved
            if(data.isNull()) {
                std::cout << "No variable named: " << array_name << " exiting...";
                return;
            }

            // create an index vector to select the data            
            std::vector<size_t> indexp;
            indexp.push_back(t);
            indexp.push_back(0);

            // copy the data from the state array into the netCDF variable
            for(int i = 0; i < length; i++){
                indexp[1] = i;
                data.putVar(indexp, x[i]);
            }
        }
        catch(NcException& e){
            e.what();
        }
    }
            
    // The file will be automatically closed when the NcFile object goes
    // out of scope. This frees up any internal netCDF resources
    // associated with the file, and flushes any buffers.
}