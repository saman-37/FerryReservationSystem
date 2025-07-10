//************************************************************
// sailing.h
//************************************************************
// Purpose: Represents a ferry sailing with fixed-size binary fields
// and supports lane management (HRL, LRL), file operations, and info retrieval.
// July 10, 2025 Revision 1
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
    Sailing(const std::string& sailingId, const std::string& vesselName, double HRL, double LRL); // in: sailingId, vesselName, HRL, LRL

    void writeToFile(std::fstream& file) const; // Write sailing information to a file, in-out: file
    void readFromFile(std::fstream& file); // Read sailing information from a file, in-out: file

    std::string toString() const; // Convert sailing data to string for display, out: string

    void initialize(const std::string& sailingId, const std::string& vesselName, double HRL, double LRL); // in: sailingID, vesselName, HRL, LRL
    
    static Sailing getSailingInfo(const std::string& sailingId); // returns sailing information as a string, in: sailingId
    
    static bool checkExist(std::string& sailingId); // in: sailingId
    static bool writeSailing(std::string& sailingId, std::string& vesselName, double HRL, double LRL); // in: sailingId, vesselName, HRL, LRL
    static bool removeSailing(std::string& sailingId); // in: sailingId
    static bool isSpaceAvailable(const std::string& sailingId, double vehicleLength, bool isSpecial); // in: sailingId, vehicleLength, isSpecial
    
    static void reduceSpace(const std::string& sailingId, double vehicleLength, bool isSpecial); // in-out: modifies storage file
    static void addSpace(const std::string& sailingId, double vehicleLength); // in-out: modifies storage file

    double getHRL(const std::string& sailingId) const; // getter for HRL (High Remaining Length), in: sailingId, out: HRL
    double getLRL(const std::string& sailingId) const; // getter for LRL (Low Remaining Length), in: sailingId, out: LRL
};
