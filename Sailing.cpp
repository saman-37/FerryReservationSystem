//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//************************************************************
// Sailing.cpp
//************************************************************
// Purpose: Implementation for Sailing class representing a ferry sailing.
// Provides support for reading, writing, searching, adding, and removing
// fixed-length binary records representing sailings.
// July 21, 2025 Version 1 - Team 18
//************************************************************

#include "Sailing.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

//************************************************************
// Default Constructor
// Initializes all fields to zero or empty string
//************************************************************
Sailing::Sailing()
{
    memset(sailingId, 0, sizeof(sailingId));
    memset(vesselName, 0, sizeof(vesselName));
    HRL = 0.0;
    LRL = 0.0;
}

//************************************************************
// Parameterized Constructor
// Initializes sailing with given ID, vessel name, and lane lengths
// in: sailingId, vesselName, HRL, LRL
//************************************************************
Sailing::Sailing(const char* sailingId, const char* vesselName, double HRL, double LRL) {
    strncpy(this->sailingId, sailingId, SAILING_ID_LENGTH - 1);
    this->sailingId[SAILING_ID_LENGTH - 1] = '\0';

    strncpy(this->vesselName, vesselName, VESSEL_NAME_LENGTH - 1);
    this->vesselName[VESSEL_NAME_LENGTH - 1] = '\0';

    this->HRL = HRL;
    this->LRL = LRL;
}

//************************************************************
// open()
// Sets the sailing fields from parameters, used to update object
// in: id, vName, hrl, lrl
//************************************************************
void Sailing::open(const string& id, const string& vName, double hrl, double lrl) {
    strncpy(sailingId, id.c_str(), SAILING_ID_LENGTH);
    sailingId[SAILING_ID_LENGTH] = '\0';

    strncpy(vesselName, vName.c_str(), VESSEL_NAME_LENGTH);
    vesselName[VESSEL_NAME_LENGTH] = '\0';

    HRL = hrl;
    LRL = lrl;
}

//************************************************************
// writeToFile()
// Writes the entire Sailing object to file as binary
// in: file - open binary stream
//************************************************************
void Sailing::writeToFile(fstream &file) const
{
    file.write(reinterpret_cast<const char *>(this), RECORD_SIZE);
}

//************************************************************
// readFromFile()
// Reads the entire Sailing object from file as binary
// in: file - open binary stream
//************************************************************
void Sailing::readFromFile(fstream &file)
{
    file.read(reinterpret_cast<char *>(this), RECORD_SIZE);
}

#include "Sailing.h"
#include <fstream>
#include <cstring> // for strcmp if needed

//************************************************************
// searchForSailing()
// Searches for a sailing record by ID
// in: sailingId
// out: fills foundSailing and returns true if match found
//************************************************************
bool Sailing::searchForSailing(const string &sailingId, Sailing &foundSailing)
{
    ifstream file("sailing.dat", ios::in | ios::binary);
    if (!file)
    {
        cerr << "Could not open sailing.dat for reading." << endl;
        return false;
    }

    Sailing temp;
    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Sailing)))
    {
        if (strcmp(temp.sailingId, sailingId.c_str()) == 0)
        {
            foundSailing = temp; // Copy matched record
            file.close();
            return true;
        }
    }

    file.close();
    return false; // Not found
}

//************************************************************
// getSailingInfo()
// Returns a Sailing object for the given sailingId
//************************************************************
Sailing Sailing::getSailingInfo(const string& sailingId) {
    fstream file("sailing.dat", ios::in | ios::binary);
    Sailing sailing;
    while (file.read(reinterpret_cast<char *>(&sailing), RECORD_SIZE))
    {
        if (strcmp(sailing.sailingId, sailingId.c_str()) == 0)
        {
            file.close();
            return sailing;
        }
    }
    file.close();
    return Sailing(); // Return empty/default sailing if not found
}

//************************************************************
// checkExist()
// Checks if a sailing record exists by ID
// in: sailingId
// out: true if found
//************************************************************
bool Sailing::checkExist(string sailingId) {
    fstream file("sailing.dat", ios::in | ios::binary);
    Sailing sailing;
    while (file.read(reinterpret_cast<char *>(&sailing), RECORD_SIZE))
    {
        if (strcmp(sailing.sailingId, sailingId.c_str()) == 0)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

//************************************************************
// writeSailing()
// Appends a new sailing record to the sailing.dat file
//************************************************************
bool Sailing::writeSailing(std::string &sailingId, std::string &vesselName, double HRL, double LRL)
{
    std::fstream file("sailing.dat", std::ios::out | std::ios::app | std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    Sailing s(sailingId.c_str(), vesselName.c_str(), HRL, LRL);
    s.writeToFile(file);
    file.close();
    return true;
}

//************************************************************
// removeSailing()
// Removes a sailing record by copying all non-matching records
// to a temp file and replacing the original
//************************************************************
bool Sailing::removeSailing(string sailingId) {
    fstream file("sailing.dat", ios::in | ios::binary);
    fstream temp("temp.dat", ios::out | ios::binary);
    Sailing s;
    bool removed = false;

    while (file.read(reinterpret_cast<char *>(&s), RECORD_SIZE))
    {
        if (strcmp(s.sailingId, sailingId.c_str()) != 0)
        {
            temp.write(reinterpret_cast<char *>(&s), RECORD_SIZE);
        }
        else
        {
            removed = true; // Skip writing matched sailing
        }
    }

    file.close();
    temp.close();
    remove("sailing.dat");
    rename("temp.dat", "sailing.dat");
    return removed;
}