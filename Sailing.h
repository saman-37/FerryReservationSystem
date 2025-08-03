//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//************************************************************
// Sailing.h
//************************************************************
// Purpose: Represents a ferry sailing with fixed-size binary fields.
// Supports lane management (HRL, LRL), file I/O, and lookup operations.
// July 23, 2025 Version 2 - Team 18
//************************************************************

#pragma once

#include <fstream>
#include <string>

using namespace std;

class Sailing
{
public:
    static const int SAILING_ID_LENGTH = 10;   // Length of sailing ID (9 chars + null terminator)
    static const int VESSEL_NAME_LENGTH = 25; // Length of vessel name (24 chars + null terminator)
    static const int RECORD_SIZE = SAILING_ID_LENGTH + VESSEL_NAME_LENGTH + sizeof(double) * 2;
    // Total size of binary record: ID, vesselName, HRL, LRL (plus padding if any)

    char sailingId[SAILING_ID_LENGTH + 1];   // +1 for null terminator
    char vesselName[VESSEL_NAME_LENGTH + 1]; // +1 for null terminator
    double HRL;                              // High-ceiling remaining lane length
    double LRL;                              // Low-ceiling remaining lane length

    Sailing(); // Default constructor

    //************************************************************
    // Parameterized constructor
    //************************************************************
    // in: sailingId, vesselName, HRL, LRL
    // Initializes a sailing record with given parameters.
    //************************************************************
    Sailing(const char *sailingId, const char *vesselName, double HRL, double LRL);

    //************************************************************
    // writeToFile
    //************************************************************
    // Writes this sailing object to the open binary file.
    // in-out: file - must be open in binary write mode
    //************************************************************
    void writeToFile(fstream &file) const;

    //************************************************************
    // readFromFile
    //************************************************************
    // Reads a full sailing object from binary file.
    // in-out: file - must be open in binary read mode
    //************************************************************
    void readFromFile(fstream &file);

    //************************************************************
    // searchForSailing
    //************************************************************
    // Searches the file for a sailing matching the given ID.
    // in: sailingId
    // out: foundSailing (by reference), true if found
    //************************************************************
    static bool searchForSailing(const string &sailingId, Sailing &foundSailing);

    //************************************************************
    // open
    //************************************************************
    // Initializes this sailing object with given values.
    // in: sailingId, vesselName, HRL, LRL
    //************************************************************
    void open(const string &sailingId, const string &vesselName, double HRL, double LRL);

    //************************************************************
    // getSailingInfo
    //************************************************************
    // Retrieves a sailing object for the given ID.
    // in: sailingId
    // out: Sailing object (copy)
    //************************************************************
    static Sailing getSailingInfo(const string &sailingId);

    //************************************************************
    // checkExist
    //************************************************************
    // Checks whether a sailing ID exists in the file.
    // in: sailingId
    // out: true if exists
    //************************************************************
    static bool checkExist(string sailingId);

    //************************************************************
    // writeSailing
    //************************************************************
    // Appends a new sailing record to the sailing.dat file.
    // in: sailingId, vesselName, HRL, LRL
    // out: true if write successful
    //************************************************************
    static bool writeSailing(string &sailingId, string &vesselName, double HRL, double LRL);

    //************************************************************
    // removeSailing
    //************************************************************
    // Deletes a sailing record by copying others to a temp file.
    // in: sailingId
    // out: true if successfully removed
    //************************************************************
    static bool removeSailing(string sailingId);

    //************************************************************
    // isSpaceAvailable
    //************************************************************
    // Alternate version to check if a sailing has space
    // in: sailingId, vehicleLength, isSpecial
    // out: true if there’s enough HRL or LRL for the vehicle
    //************************************************************
    static bool isSpaceAvailable(const string &sailingId, bool isSpecial, float vehicleLength, float vehicleHeight);

    //************************************************************
    // reduceSpace
    //************************************************************
    // Deducts reserved vehicle length from LRL or HRL
    // in-out: modifies sailing.dat
    //************************************************************
    static void reduceSpace(const string &sailingId, float vehicleLength, bool isSpecial);

    //************************************************************
    // addSpace
    //************************************************************
    // Adds back vehicle length (used when canceling reservation)
    // in-out: modifies sailing.dat
    //************************************************************
    static void addSpace(const string &sailingId, float vehicleLength);

    //************************************************************
    // getHRL
    //************************************************************
    // Getter for HRL of given sailingId
    // in: sailingId
    // out: HRL as double
    //************************************************************
    double getHRL(const string &sailingId) const;

    //************************************************************
    // getLRL
    //************************************************************
    // Getter for LRL of given sailingId
    // in: sailingId
    // out: LRL as double
    //************************************************************
    double getLRL(const string &sailingId) const;
};