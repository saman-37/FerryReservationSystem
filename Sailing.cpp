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
#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>

using namespace std;

//PLEASE ADD "addSpace" !!
void addSpace(const string &sailingId, float vehicleLength)
{
    //here added space back
    cout << "Adding space back to sailing: " 
        << sailingId << endl;
}


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
        cout << "sailing id: " << sailingId 
            << " vesselName: " << vesselName 
            << " HRL: " << HRL 
            << " LRL: " << LRL << endl;
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
        cout << "sailing id: " << sailingId 
            << " vesselName: " << vesselName 
            << " HRL: " << HRL 
            << " LRL: " << LRL << endl;
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

    // Step 1: Read all records into memory except the one
    // to remove
    while (Util::sailingFile.read(reinterpret_cast
                        <char *>(&temp), RECORD_SIZE))
    {
        if (strcmp(temp.sailingId, sailingId.c_str()) != 0)
        {
            sailings.push_back(temp);
        }
        else
        {
            removed = true;
        }
    }

    // Step 2: Truncate the file
    Util::sailingFile.close();
    Util::sailingFile.open("sailing.dat", ios::in 
                                        | ios::out 
                                        | ios::binary 
                                        | ios::trunc);

    // Step 3: Write back the kept records
    for (const auto &s : sailings)
    {
        Util::sailingFile.write(reinterpret_cast
                        <const char *>(&s), RECORD_SIZE);
    }

    Util::sailingFile.flush();
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
    Util::sailingFile.clear();
    Util::sailingFile.seekg(0, ios::beg);

    Sailing sailing;
    while (Util::sailingFile.read(reinterpret_cast
                    <char *>(&sailing), RECORD_SIZE))
    {
        if (strcmp(sailing.sailingId, 
                    sailingId.c_str()) == 0)
        {
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
    Util::sailingFile.clear();
    Util::sailingFile.seekg(0, ios::beg);

    Sailing sailing;
    streampos pos;

    while (Util::sailingFile.read(reinterpret_cast
                        <char *>(&sailing), RECORD_SIZE))
    {
        if (strcmp(sailing.sailingId, 
                    sailingId.c_str()) == 0)
        {
    // Calculate current position and go back to overwrite
            pos = Util::sailingFile.tellg();
            pos -= RECORD_SIZE;

            if (isSpecial)
            {
                sailing.HRL -= vehicleLength;
            }
            else
            {
                sailing.LRL -= vehicleLength;
            }

            Util::sailingFile.clear();
            Util::sailingFile.seekp(pos);
            Util::sailingFile.write(reinterpret_cast
                    <const char *>(&sailing), RECORD_SIZE);
            Util::sailingFile.flush();
            break;
        }
    }
}

//*********************************************************
// addSpace
//*********************************************************
// Adds back vehicle length (used when canceling
// reservation)
// in-out: modifies sailing.dat
//*********************************************************
void Sailing::addSpace(const string &sailingId, 
                        float vehicleLength)
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
            
            sailing.LRL += vehicleLength / 2;
            sailing.HRL += vehicleLength / 2;

            // Seek back to start of this record
            Util::sailingFile.seekp(pos);

            Util::sailingFile.write(sailing.sailingId, 
                                SAILING_ID_LENGTH + 1);
            Util::sailingFile.write(sailing.vesselName, 
                                VESSEL_NAME_LENGTH + 1);
            Util::sailingFile.write(reinterpret_cast
            <const char *>(&sailing.HRL), sizeof(double));

            Util::sailingFile.write(reinterpret_cast
            <const char *>(&sailing.LRL), sizeof(double));

            Util::sailingFile.flush();
            return;
        }
    }

    cout << "Sailing ID " << sailingId 
        << " not found to add space." << endl;
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