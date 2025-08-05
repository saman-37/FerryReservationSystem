//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*********************************************************
// Util.cpp
//*********************************************************
// Purpose: Provides system-level helper functions such as
// startup, shutdown, and reset operations.
// July 20, 2025 Version 1 - Darpandeep Kaur
//*********************************************************

#include "Util.h"

#include <iostream>
#include <cstdio> 
using namespace std;

fstream Util::vesselFile;
fstream Util::sailingFile;
fstream Util::reservationFile;
fstream Util::vehicleFile;

//*********************************************************
// Default Constructor
//*********************************************************
Util::Util()
{
    // Placeholder for initialization if needed
}

//*********************************************************
// Initializes the system by opening necessary data files
//*********************************************************
void Util::startup()
{

    cout << "Starting up the system..." << endl;

    // Open vessel file for reading and writing
    vesselFile.open("vessel.dat", ios::in 
                                | ios::out 
                                | ios::binary); 

    // Check if the file is open
    if (!vesselFile.is_open())
    {                          
        // Clear any error flags
        vesselFile.clear();                
        // Open for writing                              
        vesselFile.open("vessel.dat", ios::out 
                                    | ios::binary);           
        vesselFile.close();            
        // Reopen for reading and writing                                  
        vesselFile.open("vessel.dat", ios::in 
                                    | ios::out 
                                    | ios::binary); 
    }

    sailingFile.open("sailing.dat", ios::in 
                                  | ios::out 
                                  | ios::binary); 

    // Check if the file is open
    if (!sailingFile.is_open())
    {                    
        // Clear any error flags                                                  
        sailingFile.clear();         
        // Open for writing                                      
        sailingFile.open("sailing.dat", ios::out 
                                    | ios::binary);   
        // Close the file after writing        
        sailingFile.close();                                        
        // Reopen for reading and writing       
        sailingFile.open("sailing.dat", ios::in 
                                      | ios::out 
                                      | ios::binary); 
    }

    // Open reservation file
    reservationFile.open("reservation.dat", ios::in 
                                          | ios::out 
                                          | ios::binary); 
    
    // Check if the file is open
    if (!reservationFile.is_open())
    {                               
        // Clear any error flags                                               
        reservationFile.clear();        
        // Open for writing                                           
        reservationFile.open("reservation.dat", ios::out 
                                              | ios::binary);  
        // Close the file after writing         
        reservationFile.close();                                                 
        // Reopen for reading and writing  
        reservationFile.open("reservation.dat", ios::in 
                                              | ios::out 
                                              | ios::binary); 
    }

    // Open vehicle file
    vehicleFile.open("vehicle.dat", ios::in 
                                  | ios::out 
                                  | ios::binary); 
    // Check if the file is open
    if (!vehicleFile.is_open())
    {                          
        // Clear any error flags                                            
        vehicleFile.clear();                    
        // Open for writing                           
        vehicleFile.open("vehicle.dat", ios::out 
                                      | ios::binary);      
        // Close the file after writing     
        vehicleFile.close();             
        // Reopen for reading and writing                                  
        vehicleFile.open("vehicle.dat", ios::in 
                                      | ios::out 
                                      | ios::binary); 
    }

    cout << "Startup complete." << endl;
}

//*********************************************************
// Gracefully closes all open resources/files
//*********************************************************
void Util::shutdown()
{
    cout << "Shutting down the system..." << endl;

    if (vesselFile.is_open())
    {
        // Close vessel file only if it is open
        vesselFile.close(); 
    }

    if (sailingFile.is_open())
    {
        // Close sailing file only if it is open
        sailingFile.close(); 
    }

    if (reservationFile.is_open())
    {
        // Close reservation file only if it is open
        reservationFile.close(); 
    }

    if (vehicleFile.is_open())
    {
        // Close vehicle file only if it is open
        vehicleFile.close(); 
    }
    cout << "Shutdown complete." << endl;
}

//*********************************************************
// Resets system data by clearing all files
//*********************************************************
void Util::reset()
{
    cout << "Reseting system data..." << endl;

    ofstream ofs;

    // Open vessel file for truncating to reset the data in
    // the file without deleting the file
    ofs.open("vesse.dat", ios::trunc 
                        | ios::binary); 
    ofs.close();

    // Open sailing file for truncating to reset the data
    // in the file without deleting the file
    ofs.open("sailing.dat", ios::trunc 
                          | ios::binary); 
    ofs.close();

    // Open reservation file for truncating to reset the
    // data in the file without deleting the file
    ofs.open("reservaiton.dat", ios::trunc 
                              | ios::binary); 
    ofs.close();

    // Open vehicle file for truncating to reset the data
    // in the file without deleting the file
    ofs.open("vehicle.dat", ios::trunc 
                          | ios::binary); 
    ofs.close();

    cout << "System data reset compelete." << endl;
}

bool Util::truncate(const std::string& filename, 
                    std::streamoff newSize)
{
    std::fstream file(filename, std::ios::in 
                              | std::ios::out 
                              | std::ios::binary);
    if (!file)
    {
        std::cerr << "Failed to open file: " 
                    << filename << std::endl;
        return false;
    }

    // Read only up to newSize bytes
    std::string buffer(newSize, '\0');
    file.read(&buffer[0], newSize);
    file.close();

    // Overwrite file with only the portion we want 
    std::ofstream out(filename, std::ios::binary 
                              | std::ios::trunc);
    if (!out)
    {
        std::cerr << "Failed to truncate file: " 
                    << filename << std::endl;
        return false;
    }

    out.write(buffer.c_str(), newSize);
    out.close();

    return true;
}

