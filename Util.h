//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*********************************************************
// Util.h
//*********************************************************
// Purpose: Provides system-level helper functions such as
// startup, shutdown, and reset operations.
// July 20, 2025 Version 2 - All team members
//*********************************************************

#pragma once

#include <fstream>
#include <string>

class Util
{
public:
    // Default Constructor
    Util(); 

    // Initializes the system (e.g., opens data files)
    static void startup();  
    // Gracefully closes resources/files
    static void shutdown(); 
    // Resets system data (e.g., clears files)
    static void reset();    
    static bool truncate(const std::string &filename, 
                            std::streamoff newSize);

    // Shared static file handles
    static std::fstream vesselFile;
    static std::fstream sailingFile;
    static std::fstream reservationFile;
    static std::fstream vehicleFile;
};
