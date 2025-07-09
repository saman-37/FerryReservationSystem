//************************************************************
// vessel.h
//************************************************************
// Purpose: Represents a ferry vessel that holds capacity values
// used to initialize new sailings. Stored as binary data.
//************************************************************

#pragma once

using namespace std;

#include <fstream>
#include <string>

class Vessel {
    public:
        static const int NAME_LENGTH = 25; // Length of the vessel name
        static const int ID_LENGTH = 10; // Length of the vessel ID
        static const int RECORD_SIZE = NAME_LENGTH + ID_LENGTH + sizeof(double) * 2; // Size of the record in bytes

        char vesselName[NAME_LENGTH + 1]; // +1 for null terminator
        char vesselId[ID_LENGTH + 1]; // +1 for null terminator 
        double HCLL; // High Capacity Lane Length
        double LCLL; // Low Capacity Lane Length


        Vessel(); // Default Constructor
        Vessel(const std::string& vesselName, const std::string& vesselId, double HCLL, double LCLL); // Parameterized Constructor

        void writeToFile(std::fstream& file) const; // write vessel data to file
        void readFromFile(std::fstream& file); // read vessel data from file

        std::string toString() const; // convert vessel data to string for display

        bool checkExists(const std::string& vesselId);
        bool writeVessel(const std::string& VesselName, const std::string& vesselId, double HCLL, double LCLL);

        std::string getName() const; // getter for name
        std::string getVesselID() const; // getter for vessel_ID
        double getHCLL() const; // getter for HCLL(High Capacity Lane Length)
        double getLCLL() const; // getter for LCLL(Low Capacity Lane Length)

        int getCapacity() const; // returns the capacity of the vessel

    };
