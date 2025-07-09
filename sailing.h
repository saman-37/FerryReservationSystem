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
    double vehicleLength; // Length of the vehicle in meters
    double HRL; // High Road Length in meters
    double LRL; // Low Road Lengths in meters
    
    sailing();
    Sailing(const std::string& sailingId, const std::string& vesselName, double HRL, double LRL); 

    void writeToFile(std::fstream& file) const; // Write sailing information to a file
    void readFromFile(std::fstream& file); // Read sailing information from a file

    std::string toString() const; // Convert sailing data to string for display

    static Sailing getSailingInfo(const std::string& sailingId); // returns sailing information as a string
    
    bool checkExists(std::string& SailingId);
    bool writeSailing(std::string& SailingId, std::string& vesselName, double HRL, double LRL);
    bool removeSailing(std::string& SailingId);
    bool isSpaceAvailable(const std::string& SailingId, double vehicleLength, bool isSpecial);
    
    void reduceSpace(const std::string& SailingId, double vehicleLength, bool isSpecial);
    void addSpace(const std::string& SailingId, double vehicleLength);
    
    double getHRL(const std::string& SailingId) const; // getter for HRL (High Road Length)
    double getLRL(const std::string& SailingId) const; // getter for LRL (Low Road Length)
};
