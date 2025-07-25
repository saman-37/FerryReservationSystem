//************************************************************
// Util.h
//************************************************************
// Purpose: Provides system-level helper functions such as
// startup, shutdown, and reset operations.
// July 10, 2025 Revision 1 - All team members
//************************************************************

#pragma once

#include <fstream>
#include <string>

class Util
{
public:
    Util(); // Default Constructor

    void startup();  // Initializes the system (e.g., opens data files)
    void shutdown(); // Gracefully closes resources/files
    void reset();    // Resets system data (e.g., clears files)

    // Shared static file handles
    static std::fstream vesselFile;
    static std::fstream sailingFile;
    static std::fstream reservationFile;
    static std::fstream vehicleFile;
};
