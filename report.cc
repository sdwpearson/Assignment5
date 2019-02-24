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
    int array_number = (int)x[3];
    array_name += std::to_string(array_number);


    std::cout << "writing to netCDF file with " << array_number << std::endl;

    if(t <= 0.00001){
        try
        {  
            std::cout << "trying ..." << std::endl;
            if(array_number == 7){
                // Create/Overwrite a new file. 
                NcFile dataFile(filename, NcFile::replace);

                // Create netCDF dimensions
                NcDim timeDim = dataFile.addDim("time"+std::to_string(array_number));
                NcDim stateDim = dataFile.addDim("state"+std::to_string(array_number), length+1);
              
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
                std::cout << "inside the else statement" << std::endl;
                // Create the file. 
                NcFile dataFile(filename, NcFile::write);

                // See if the variable was successfully created
                if(dataFile.isNull()) {
                    std::cout << "file named: " << filename << " can not be accessed. Exiting..." << std::endl;
                    return;
                }

                std::cout << "creating Dimensions" << std::endl;
                // Create netCDF dimensions
                NcDim timeDim = dataFile.addDim("time"+std::to_string(array_number));
                NcDim stateDim = dataFile.addDim("state"+std::to_string(array_number), length+1);
              
                // Define the variable. The type of the variable in this case is
                // ncDouble (64-bit float).
                std::vector<NcDim> dims;
                dims.push_back(timeDim);
                dims.push_back(stateDim);
                std::cout << "creating " << array_name << std::endl;
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