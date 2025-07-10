//************************************************************
// sailing.h
//************************************************************
// Purpose: Represents a ferry sailing with fixed-size binary fields
// and supports lane management (HRL, LRL), file operations, and info retrieval.
//************************************************************

#pragma once

using namespace std;

#include <fstream>
#include <string>

class Sailing{
    public:
    static const int SAILING_ID_LENGTH = 15; // Length of the sailing ID
    static const int VESSEL_NAME_LENGTH = 25; // Length of the vessel name
    static const int RECORD_SIZE = SAILING_ID_LENGTH + VESSEL_NAME_LENGTH + sizeof(double) * 3; // Size of each record in bytes


    char sailingId[SAILING_ID_LENGTH + 1]; // Unique identifier for the sailing
    char vesselName[VESSEL_NAME_LENGTH + 1]; // Name of the vessel
    double HRL; // High Remaining Length in meters
    double LRL; // Low Remaining Length in meters
    
    Sailing(); // Default Constructor
    Sailing(const std::string& sailingId, const std::string& vesselName, double HRL, double LRL); // Parametrised Constructor

    void writeToFile(std::fstream& file) const; // Write sailing information to a file
    void readFromFile(std::fstream& file); // Read sailing information from a file

    std::string toString() const; // Convert sailing data to string for display

    void initialize(const std::string& sailingId, const std::string& vesselName, double HRL, double LRL); // Initialize sailing data
    
    static Sailing getSailingInfo(const std::string& sailingId); // returns sailing information as a string
    
    static bool checkExists(std::string& SailingId);
    static bool writeSailing(std::string& SailingId, std::string& vesselName, double HRL, double LRL);
    static bool removeSailing(std::string& SailingId);
    static bool isSpaceAvailable(const std::string& SailingId, double vehicleLength, bool isSpecial);
    
    static void reduceSpace(const std::string& SailingId, double vehicleLength, bool isSpecial);
    static void addSpace(const std::string& SailingId, double vehicleLength);

    double getHRL(const std::string& SailingId) const; // getter for HRL (High Remaining Length)
    double getLRL(const std::string& SailingId) const; // getter for LRL (Low Remaining Length)
};
