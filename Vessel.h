//************************************************************
// Vessel.h
//************************************************************
// Purpose: Represents a ferry vessel that holds capacity values
// used to initialize new sailings. Stored as binary data.
// July 20, 2025 Version 3 - All team members
//************************************************************

#pragma once

#include <fstream>
#include <string>

using namespace std;

//************************************************************
// Constants
//************************************************************
static const int NAME_LENGTH = 25; // Length of the vessel name

class Vessel
{
public:
    //************************************************************
    // RECORD_SIZE
    //************************************************************
    // Size of the record in bytes: 
    // vesselName + null terminator + HCLL + LCLL
    //************************************************************
    static const int RECORD_SIZE = NAME_LENGTH + 1 + (sizeof(int) * 2); // Size of the record in bytes

    char vesselName[NAME_LENGTH + 1]; // Array to store vessel name, +1 for null terminator
    int HCLL; // High Capacity Lane Length
    int LCLL; // Low Capacity Lane Length

    //************************************************************
    // Default Constructor
    //************************************************************
    Vessel(); // Initializes a vessel with default values

    //************************************************************
    // Parameterized Constructor
    //************************************************************
    // Initializes a vessel with provided values.
    // in: vesselName, HCLL, LCLL
    //************************************************************
    Vessel(const string &vesselName, int HCLL, int LCLL);

    //************************************************************
    // writeToFile
    //************************************************************
    // Writes the vessel record to a binary file.
    // in-out: file - binary stream to write into
    //************************************************************
    void writeToFile(fstream &file) const;

    //************************************************************
    // readFromFile
    //************************************************************
    // Reads a vessel record from a binary file.
    // in-out: file - binary stream to read from
    //************************************************************
    void readFromFile(fstream &file);

    //************************************************************
    // checkExist
    //************************************************************
    // Checks if a vessel with the given name exists.
    // in: vesselName
    // out: true if exists, false otherwise
    //************************************************************
    static bool checkExist(const string &vesselName);

    //************************************************************
    // writeVessel
    //************************************************************
    // Writes a new vessel record to the binary file.
    // in: vesselName, HCLL, LCLL
    // out: true if written successfully, false otherwise
    //************************************************************
    static bool writeVessel(const string &VesselName, int HCLL, int LCLL);

    //************************************************************
    // toString
    //************************************************************
    // Converts the vessel data into a formatted string.
    // out: formatted string
    //************************************************************
    string toString() const;

    //************************************************************
    // getName
    //************************************************************
    // Getter for vessel name.
    // out: vesselName as string
    //************************************************************
    string getName() const;

    //************************************************************
    // getHCLL
    //************************************************************
    // Getter for HCLL based on vessel name.
    // in: vesselName
    // out: HCLL as integer, or -1 if not found
    //************************************************************
    static int getHCLL(const std::string &vesselName);

    //************************************************************
    // getLCLL
    //************************************************************
    // Getter for LCLL based on vessel name.
    // in: vesselName
    // out: LCLL as integer, or -1 if not found
    //************************************************************
    static int getLCLL(const std::string &vesselName);

    //************************************************************
    // getCapacity
    //************************************************************
    // Calculates and returns total capacity (HCLL + LCLL).
    // in: vesselName
    // out: total capacity as integer
    //************************************************************
    static int getCapacity(const std::string &vesselName); // Returns the sum of HCLL and LCLL as capacity of the vessel
};