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
#include "Util.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>

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
    Util::sailingFile.write(reinterpret_cast<const char *>(this), RECORD_SIZE);
}

//************************************************************
// readFromFile()
// Reads the entire Sailing object from file as binary
// in: file - open binary stream
//************************************************************
void Sailing::readFromFile(fstream &file)
{
    Util::sailingFile.read(reinterpret_cast<char *>(this), RECORD_SIZE);
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
    if (!Util::sailingFile)
    {
        cout << "Could not open sailing.dat for reading." << endl;
        return false;
    }

    Sailing temp;
    while (Util::sailingFile.read(reinterpret_cast<char *>(&temp), sizeof(Sailing)))
    {
        if (strcmp(temp.sailingId, sailingId.c_str()) == 0)
        {
            foundSailing = temp; // Copy matched record
            return true;
        }
    }

    return false; // Not found
}

//************************************************************
// getSailingInfo()
// Returns a Sailing object for the given sailingId
//************************************************************
Sailing Sailing::getSailingInfo(const string& sailingId) {
    Sailing sailing;
    while (Util::sailingFile.read(reinterpret_cast<char *>(&sailing), RECORD_SIZE))
    {
        if (strcmp(sailing.sailingId, sailingId.c_str()) == 0)
        {
            Util::sailingFile.close();
            return sailing;
        }
    }
    return Sailing(); // Return empty/default sailing if not found
}

//************************************************************
// checkExist()
// Checks if a sailing record exists by ID
// in: sailingId
// out: true if found
//************************************************************
bool Sailing::checkExist(string sailingId) {
    Sailing sailing;
    while (Util::sailingFile.read(reinterpret_cast<char *>(&sailing), RECORD_SIZE))
    {
        if (strcmp(sailing.sailingId, sailingId.c_str()) == 0)
        {
            Util::sailingFile.close();
            return true;
        }
    }
    return false;
}

//************************************************************
// writeSailing()
// Appends a new sailing record to the sailing.dat file
//************************************************************
bool Sailing::writeSailing(std::string &sailingId, std::string &vesselName, double HRL, double LRL)
{
    if (!Util::sailingFile.is_open()) {
        return false;
    }
    Sailing s(sailingId.c_str(), vesselName.c_str(), HRL, LRL);
    Util::sailingFile.seekp(0, std::ios::end);
    s.writeToFile(Util::sailingFile);
    return true;
}

//************************************************************
// removeSailing()
// Removes a sailing record by copying all non-matching records
// to a temp file and replacing the original
//************************************************************
bool Sailing::removeSailing(string sailingId) {
    
    Util::sailingFile.clear();
    Util::sailingFile.seekg(0, ios::beg);

    vector<Sailing> sailings;
    Sailing temp;
    bool removed = false;

// Step 1: Read all records into memory except the one to remove
while (Util::sailingFile.read(reinterpret_cast<char*>(&temp), RECORD_SIZE)) {
    if (strcmp(temp.sailingId, sailingId.c_str()) != 0) {
        sailings.push_back(temp);
    }
    else {
        removed = true;
    }
}

    // Step 2: Truncate the file
    Util::sailingFile.close();
    Util::sailingFile.open("sailing.dat", ios::in | ios::out | ios::binary | ios::trunc);

    // Step 3: Write back the kept records
    for (const auto& s : sailings) {
        Util::sailingFile.write(reinterpret_cast<const char*>(&s), RECORD_SIZE);
    }

    Util::sailingFile.flush();
    return removed;
}

//************************************************************
// isSpaceAvailable()
// Checks whether a vehicle can be reserved on this sailing
// depending on height/length and lane space.
//************************************************************
bool Sailing::isSpaceAvailable(const string &sailingId, bool isSpecial, double vehicleLength, double vehicleHeight)
{
    Util::sailingFile.clear();
    Util::sailingFile.seekg(0, ios::beg);

    Sailing sailing;
    while (Util::sailingFile.read(reinterpret_cast<char*>(&sailing), RECORD_SIZE)) {
        if (strcmp(sailing.sailingId, sailingId.c_str()) == 0) {
            if (isSpecial) {
                return sailing.HRL >= vehicleLength;
            } else {
                return sailing.LRL >= vehicleLength;
            }
        }
    }

    return false;
}

//************************************************************
// reduceSpace()
// Deducts reserved vehicle length from LCLL or HRL
//************************************************************
void Sailing::reduceSpace(const string &sailingId, double vehicleLength, bool isSpecial)
{
    Util::sailingFile.clear();
    Util::sailingFile.seekg(0, ios::beg);

    Sailing sailing;
    streampos pos;

    while (Util::sailingFile.read(reinterpret_cast<char*>(&sailing), RECORD_SIZE)) {
        if (strcmp(sailing.sailingId, sailingId.c_str()) == 0) {
            // Calculate current position and go back to overwrite
            pos = Util::sailingFile.tellg();
            pos -= RECORD_SIZE;

            if (isSpecial) {
                sailing.HRL -= vehicleLength;
            } else {
                sailing.LRL -= vehicleLength;
            }

            Util::sailingFile.clear();
            Util::sailingFile.seekp(pos);
            Util::sailingFile.write(reinterpret_cast<const char*>(&sailing), RECORD_SIZE);
            Util::sailingFile.flush();
            break;
        }
    }
}
