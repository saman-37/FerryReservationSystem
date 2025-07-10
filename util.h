//************************************************************
// util.h
//************************************************************
// Purpose: Provides system-level helper functions such as
// startup, shutdown, and reset operations.
//************************************************************

#pragma once

#include <fstream>
#include <string>

class Util {
    public:
        Util(); // Default Constructor

        void startup(); // Initializes the system (e.g., opens data files)
        void shutdown(); // Gracefully closes resources/files
        void reset(); // Resets system data (e.g., clears files)
        void initialize(); // Initializes the system (e.g., sets up initial data)
};
