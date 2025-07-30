//************************************************************
// Vessel.h
//************************************************************
// Purpose: Represents a ferry vessel that holds capacity values
// used to initialize new sailings. Stored as binary data.
// July 20, 2025 Version 2 - All team members
//************************************************************

#pragma once

using namespace std;

#include <fstream>
#include <string>

class Vessel
{
public:
    static const int NAME_LENGTH = 25;                            // Length of the vessel name
    static const int RECORD_SIZE = NAME_LENGTH + 1 + (sizeof(int) * 2); // Size of the record in bytes

    char vesselName[NAME_LENGTH + 1]; // +1 for null terminator
    int HCLL;                      // High Capacity Lane Length
    int LCLL;                      // Low Capacity Lane Length

    Vessel();                                             // Default Constructor
    Vessel(const string &vesselName, int HCLL, int LCLL); // in: vesselName, HCLL, LCLL

    void writeToFile(fstream &file) const; // in-out: file
    void readFromFile(fstream &file);      // in-out: file

    static bool checkExist(const string &vesselName);                      // in: vesselName
    static bool writeVessel(const string &VesselName, int HCLL, int LCLL); // in: vesselName, vesselId, HCLL, LCLL
    string toString() const;                                        // out: string

    string getName() const;                              // out: vesselName
    int getHCLL(const std::string &vesselName) const; // out: HCLL
    int getLCLL(const std::string &vesselName) const; // out: LCLL

    int getCapacity(const std::string &vesselName) const; // returns the ssum of HCLL and LCLL as capacity of the vessel
};
