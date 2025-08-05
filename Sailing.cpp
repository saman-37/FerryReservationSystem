//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*********************************************************
// Sailing.cpp
//*********************************************************
// Purpose: Implementation for Sailing class representing a
// ferry sailing.
// Provides support for reading, writing, searching, adding,
// and removing
// fixed-length binary records representing sailings.
// July 21, 2025 Version 2 - Team 18
//*********************************************************

#include "Sailing.h"
#include "Util.h"
#include "Vehicle.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>

using namespace std;

//*********************************************************
// Default Constructor
// Initializes all fields to zero or empty string
//*********************************************************
Sailing::Sailing()
{
    memset(sailingId, 0, sizeof(sailingId));
    memset(vesselName, 0, sizeof(vesselName));
    HRL = 0.0;
    LRL = 0.0;
}

//*********************************************************
// Parameterized Constructor
// Initializes sailing with given ID, vessel name, and lane
// lengths
// in: sailingId, vesselName, HRL, LRL
//*********************************************************
Sailing::Sailing(const char *sailingId, 
                const char *vesselName, 
                double HRL, double LRL)
{
    strncpy(this->sailingId, sailingId, 
            SAILING_ID_LENGTH);
    this->sailingId[SAILING_ID_LENGTH] = '\0';

    strncpy(this->vesselName, vesselName, 
            VESSEL_NAME_LENGTH);
    this->vesselName[VESSEL_NAME_LENGTH] = '\0';

    this->HRL = HRL;
    this->LRL = LRL;
}

//*********************************************************
// open()
// Sets the sailing fields from parameters, used to update
// object
// in: id, vName, hrl, lrl
//*********************************************************
void Sailing::open(const string &id, 
                const string &vName, 
                double hrl, double lrl)
{
    strncpy(sailingId, id.c_str(), SAILING_ID_LENGTH);
    sailingId[SAILING_ID_LENGTH] = '\0';

    strncpy(vesselName, vName.c_str(), VESSEL_NAME_LENGTH);
    vesselName[VESSEL_NAME_LENGTH] = '\0';

    HRL = hrl;
    LRL = lrl;
}

//*********************************************************
// writeToFile()
// Writes the entire Sailing object to file as binary
// in: file - open binary stream
//*********************************************************
void Sailing::writeToFile(fstream &file) const
{
    if (file.is_open())
    {
        // Write SailingId, vesselName, HRL and LRL
        file.write(sailingId, SAILING_ID_LENGTH + 1);                  
        file.write(vesselName, VESSEL_NAME_LENGTH + 1);              
        file.write(reinterpret_cast<const char *>(&HRL),
                    sizeof(double)); 
        file.write(reinterpret_cast<const char *>(&LRL),
                    sizeof(double)); 
    }
    else
    {
        cout << "Error opening file for writing." 
            << endl;
    }
}

//*********************************************************
// readFromFile()
// Reads the entire Sailing object from file as binary
// in: file - open binary stream
//*********************************************************
void Sailing::readFromFile(fstream &file)
{
    if (file.is_open())
    {
        // Read sailingID, vesselName, HRL, LRL
        file.read(sailingId, sizeof(sailingId));            
        file.read(vesselName, sizeof(vesselName)); 
        file.read(reinterpret_cast<char *>(&HRL), 
                    sizeof(double));
        file.read(reinterpret_cast<char *>(&LRL), 
                    sizeof(double));
    }
    else
    {
        cout << "Error opening file." << endl;
    }
}

//*********************************************************
// searchForSailing()
// Searches for a sailing record by ID
// in: sailingId
// out: fills foundSailing and returns true if match found
//*********************************************************
bool Sailing::searchForSailing(const string &sailingId, 
                                Sailing &foundSailing)
{
    Util::sailingFile.clear();
    Util::sailingFile.seekg(0, ios::beg);

    Sailing sailing;

    while (true)
    {
        if (!Util::sailingFile.read(sailing.sailingId, 
                        SAILING_ID_LENGTH + 1)) break;

        if (!Util::sailingFile.read(sailing.vesselName, 
                        VESSEL_NAME_LENGTH + 1)) break;

        if (!Util::sailingFile.read(reinterpret_cast
        <char *>(&sailing.HRL), sizeof(double))) break;
        
        if (!Util::sailingFile.read(reinterpret_cast
        <char *>(&sailing.LRL), sizeof(double))) break;

        if (strcmp(sailing.sailingId, 
            sailingId.c_str()) == 0)
        {
            foundSailing = sailing;
            return true;
        }
    }

    return false;
}

//*********************************************************
// getSailingInfo()
// Returns a Sailing object for the given sailingId
//*********************************************************
Sailing Sailing::getSailingInfo(const string &sailingId)
{
    if (!Util::sailingFile.is_open())
    {
        Util::sailingFile.open("sailing.dat", ios::in 
                                            | ios::binary);
        if (!Util::sailingFile.is_open()) {
            cout << "Could not open sailing.dat\n";
            return Sailing();
        }
    }

    Util::sailingFile.clear();
    Util::sailingFile.seekg(0, ios::beg);

    Sailing sailing;

    while (true)
    {
        if (!Util::sailingFile.read(sailing.sailingId, 
                        SAILING_ID_LENGTH + 1)) break;
        if (!Util::sailingFile.read(sailing.vesselName, 
                        VESSEL_NAME_LENGTH + 1)) break;
        if (!Util::sailingFile.read(reinterpret_cast
        <char*>(&sailing.HRL), sizeof(double))) break;
        
        if (!Util::sailingFile.read(reinterpret_cast
        <char*>(&sailing.LRL), sizeof(double))) break;

        if (strcmp(sailing.sailingId, 
                sailingId.c_str()) == 0)
        {
            return sailing;
        }
    }

    return Sailing(); // Not found
}

bool Sailing::checkExist(string sailingId)
{
    if (Util::sailingFile.is_open())
    {
        Util::sailingFile.clear();
        Util::sailingFile.seekg(0, ios::beg);

        Sailing sailing;

        while (true)
        {
            // Read each field safely
            if (!Util::sailingFile.read(sailing.sailingId, 
                            SAILING_ID_LENGTH + 1)) break;
            if (!Util::sailingFile.read(sailing.vesselName, 
                            VESSEL_NAME_LENGTH + 1)) break;
            if (!Util::sailingFile.read(reinterpret_cast
            <char*>(&sailing.HRL), sizeof(double))) break;
            
            if (!Util::sailingFile.read(reinterpret_cast
            <char*>(&sailing.LRL), sizeof(double))) break;

            if (strcmp(sailing.sailingId, 
                        sailingId.c_str()) == 0)
            {
                return true;
            }
        }

        return false;
    }
    else
    {
        cout << "Error opening sailing file." << endl;
        return false;
    }
}

//*********************************************************
// writeSailing()
// Appends a new sailing record to the sailing.dat file
//*********************************************************
bool Sailing::writeSailing(std::string &sailingId, 
                            std::string &vesselName, 
                            double HRL, double LRL)
{
    const char *sId = sailingId.c_str();
    const char *vName = vesselName.c_str();
    Sailing sailing(sId, vName, HRL, LRL);
    Util::sailingFile.clear();
    Util::sailingFile.seekg(0, ios::end);
    sailing.writeToFile(Util::sailingFile);
    Util::sailingFile.flush(); // Save to disk
    return true;
}

//*********************************************************
// removeSailing()
// Removes a sailing record by copying all non-matching
// records
// to a temp file and replacing the original
//*********************************************************
bool Sailing::removeSailing(string sailingId)
{
    Util::sailingFile.clear();
    Util::sailingFile.seekg(0, ios::beg);

    vector<Sailing> sailings;
    Sailing temp;
    bool removed = false;

    // Step 1: Read all records using readFromFile
    while (!Util::sailingFile.eof())
    {
        temp.readFromFile(Util::sailingFile);

        if (Util::sailingFile.eof()) break;

        if (strcmp(temp.sailingId, sailingId.c_str()) != 0)
        {
            sailings.push_back(temp);
        }
        else
        {
            removed = true;
        }
    }

    // Step 2: Truncate file
    Util::sailingFile.close();
    Util::sailingFile.open("sailing.dat", ios::out 
                                        | ios::binary 
                                        | ios::trunc);

    // Step 3: Write back valid records using writeToFile
    for (const auto &s : sailings)
    {
        s.writeToFile(Util::sailingFile);
    }

    Util::sailingFile.flush();
    Util::sailingFile.close();

    // Step 4: Reopen the file in read/write mode
    Util::sailingFile.open("sailing.dat", ios::in 
                                        | ios::out 
                                        | ios::binary);

    return removed;
}

//*********************************************************
// isSpaceAvailable()
// Checks whether a vehicle can be reserved on this sailing
// depending on height/length and lane space.
//*********************************************************
bool Sailing::isSpaceAvailable(const string &sailingId, 
                                bool isSpecial, 
                                float vehicleLength, 
                                float vehicleHeight)
{
    if (!Util::sailingFile.is_open())
    {
        cout << "sailing.dat not open." << endl;
        return false;
    }

    Util::sailingFile.clear();
    Util::sailingFile.seekg(0, ios::beg);

    Sailing sailing;

    while (!Util::sailingFile.eof())
    {
        sailing.readFromFile(Util::sailingFile);

        if (strcmp(sailing.sailingId, sailingId.c_str()) == 0)
        {
            cout << "Checking space on: " 
                << sailing.sailingId << " HRL: " 
                << sailing.HRL << " LRL: " 
                << sailing.LRL << endl;

            if (isSpecial)
            {
                return sailing.HRL >= vehicleLength;
            }
            else
            {
                return sailing.LRL >= vehicleLength;
            }
        }
    }

    return false;
}

//*********************************************************
// reduceSpace()
// Deducts reserved vehicle length from LCLL or HRL
//*********************************************************
void Sailing::reduceSpace(const string &sailingId, 
                            float vehicleLength, 
                            bool isSpecial)
{
    if (!Util::sailingFile.is_open())
    {
        cout << "sailing.dat not open for reducing space." 
                << endl;
        return;
    }

    Util::sailingFile.clear();
    Util::sailingFile.seekg(0, ios::beg);

    Sailing sailing;
    streampos pos;

    while (true)
    {
        pos = Util::sailingFile.tellg();

        // Try reading record using your structured format
        sailing.readFromFile(Util::sailingFile);

        // If read failed, exit loop
        if (Util::sailingFile.eof()) break;

        if (strcmp(sailing.sailingId, 
                            sailingId.c_str()) == 0)
        {
            if (isSpecial)
                sailing.HRL -= (vehicleLength + 0.5);
            else
                sailing.LRL -= (vehicleLength + 0.5);

            Util::sailingFile.clear();
            Util::sailingFile.seekp(pos);
            sailing.writeToFile(Util::sailingFile);
            Util::sailingFile.flush();

            return;
        }
    }

    cout << "Sailing ID " << sailingId 
            << " not found in reduceSpace()." << endl;
}

//*********************************************************
// addSpace
//*********************************************************
// Adds back vehicle length (used when canceling
// reservation)
// in-out: modifies sailing.dat
//*********************************************************
void Sailing::addSpace(const string &sailingId, 
                        float vehicleLength, bool isSpecial)
{
    if (!Util::sailingFile.is_open())
    {
        cout << "Error: sailing.dat is not open." << endl;
        return;
    }

    Util::sailingFile.clear();
    Util::sailingFile.seekg(0, ios::beg);

    Sailing sailing;
    streampos pos;

    while (true)
    {
        pos = Util::sailingFile.tellg();

        sailing.readFromFile(Util::sailingFile);

        if (Util::sailingFile.eof()) break;

        if (strcmp(sailing.sailingId, 
                                sailingId.c_str()) == 0)
        {
            // Add back to appropriate lane
            if (isSpecial)
                sailing.HRL += (vehicleLength + 0.5);
            else
                sailing.LRL += (vehicleLength + 0.5);

            // Overwrite the current record
            Util::sailingFile.clear();
            Util::sailingFile.seekp(pos);
            sailing.writeToFile(Util::sailingFile);
            Util::sailingFile.flush();

            cout << "Space restored in " 
                    << (isSpecial ? "HRL" : "LRL")
                    << ". Updated: HRL=" << sailing.HRL 
                    << ", LRL=" << sailing.LRL << endl;
            return;
        }
    }

    cout << "Sailing ID " << sailingId 
            << " not found in addSpace()." << endl;
}

//************************************************************
// isValidSailingId()
//************************************************************
// Validates that a sailing ID is in format: aaa-dd-hh
// where aaa = 3 letters, dd = day 01-31, hh = hour 01-23
// in: sailingId
// out: true if valid, false otherwise
//************************************************************
bool Sailing::isValidSailingId(const string &sailingId)
{
    if (sailingId.length() != 9 
        || sailingId[3] != '-' 
        || sailingId[6] != '-')
        return false;

    // Check first 3 characters are letters
    for (int i = 0; i < 3; ++i)
    {
        if (!isalpha(sailingId[i]))
            return false;
    }

    // Extract and validate day and hour
    string dayStr = sailingId.substr(4, 2);
    string hourStr = sailingId.substr(7, 2);

    int day = stoi(dayStr);
    int hour = stoi(hourStr);

    if (day < 1 || day > 31 || hour < 0 || hour > 23)
        return false;

    return true;
}

double Sailing::getHRL(const string &sailingId) const
{
    if (!Util::sailingFile.is_open())
    {
        cout << "Error: sailing.dat is not open." << endl;
        return -1;
    }

    Util::sailingFile.clear();
    Util::sailingFile.seekg(0, ios::beg);

    Sailing sailing;

    while (true)
    {
        if (!Util::sailingFile.read(sailing.sailingId, 
                        SAILING_ID_LENGTH + 1)) break;
        if (!Util::sailingFile.read(sailing.vesselName, 
                        VESSEL_NAME_LENGTH + 1)) break;
        if (!Util::sailingFile.read(reinterpret_cast
        <char *>(&sailing.HRL), sizeof(double))) break;

        if (!Util::sailingFile.read(reinterpret_cast
        <char *>(&sailing.LRL), sizeof(double))) break;

        if (strcmp(sailing.sailingId, 
                    sailingId.c_str()) == 0)
        {
            return sailing.HRL;
        }
    }

    return -1;
}

double Sailing::getLRL(const string &sailingId) const
{
    if (!Util::sailingFile.is_open())
    {
        cout << "Error: sailing.dat is not open." << endl;
        return -1;
    }

    Util::sailingFile.clear();
    Util::sailingFile.seekg(0, ios::beg);

    Sailing sailing;

    while (true)
    {
        if (!Util::sailingFile.read(sailing.sailingId, 
                        SAILING_ID_LENGTH + 1)) break;
        if (!Util::sailingFile.read(sailing.vesselName, 
                        VESSEL_NAME_LENGTH + 1)) break;
        if (!Util::sailingFile.read(reinterpret_cast
        <char *>(&sailing.HRL), sizeof(double))) break;

        if (!Util::sailingFile.read(reinterpret_cast
        <char *>(&sailing.LRL), sizeof(double))) break;

        if (strcmp(sailing.sailingId, 
                    sailingId.c_str()) == 0)
        {
            return sailing.LRL;
        }
    }

    return -1;
}