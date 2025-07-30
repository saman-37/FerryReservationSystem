//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// Vessel.cpp
//************************************************************
// Purpose: Represents a binary-stored vessel record with name,
// high-capacity lane length (HCLL), and low-capacity lane length (LCLL).
// Used for defining sailings in the reservation system.
// July 21, 2025 Version 1 - Darpandeep Kaur
//************************************************************

#include "Vessel.h"
#include "Util.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sstream>
using namespace std;

//************************************************************
// Default Constructor
// Initializes the vessel with default values
//************************************************************
Vessel::Vessel()
{
    strncpy(vesselName, "", NAME_LENGTH); // Initialize vesselName to empty string
    vesselName[NAME_LENGTH] = '\0';       // Null-terminate
    HCLL = 3600;                        // Default High Capacity Lane Length
    LCLL = 3600;                        // Default Low Capacity Lane Length
}

//************************************************************
// Parameterized Constructor
// Initializes the vessel with provided values
// in: vesselName, HCLL, LCLL
//************************************************************
Vessel::Vessel(const string &vesselName, int HCLL, int LCLL)
{
    strncpy(this->vesselName, vesselName.c_str(), NAME_LENGTH); // Copy vesselName string
    this->vesselName[NAME_LENGTH] = '\0';                       // Null-terminate
    this->HCLL = HCLL;                                          // Set High Capacity Lane Length
    this->LCLL = LCLL;                                          // Set Low Capacity Lane Length
}

//************************************************************
// Writes the vessel record to the binary file
//************************************************************
void Vessel::writeToFile(fstream &file) const
{
    if (file.is_open())
    {
        file.write(vesselName, NAME_LENGTH + 1);                        // Write vesselName
        file.write(reinterpret_cast<const char *>(&HCLL), sizeof(int)); // Write HCLL
        file.write(reinterpret_cast<const char *>(&LCLL), sizeof(int)); // Write LCLL
    }
    else
    {
        cout << "Error opening file for writing." << endl;
    }
}

//************************************************************
// Reads a vessel record from the binary file
//************************************************************
void Vessel::readFromFile(fstream &file)
{
    if (file.is_open())
    {
        file.read(vesselName, NAME_LENGTH + 1);                   // Read vesselName
        file.read(reinterpret_cast<char *>(&HCLL), sizeof(int)); // Read HCLL
        file.read(reinterpret_cast<char *>(&LCLL), sizeof(int)); // Read LCLL
        
    }
}

//************************************************************
// Checks if a vessel with the given name exists
// in: vesselName
// out: true if exists, false otherwise
//************************************************************
bool Vessel::checkExist(const string &vesselName)
{
    if (Util::vesselFile.is_open())
    {
        Util::vesselFile.clear();
        Util::vesselFile.seekg(0, ios::beg);

        Vessel vessel;
        while (!Util::vesselFile.eof())
        {
            vessel.readFromFile(Util::vesselFile);
            if (strcmp(vessel.vesselName, vesselName.c_str()) == 0)
            {
                cout << "Vessel existing: " << vessel.vesselName << endl;
                return true; // Vessel found end here
            }
        }
        return false; // Not found, safe to create new vessel

    } else {
        cout << "Error opening vessel file." << endl;
        return false;
    }

}

//************************************************************
// Writes a new vessel record to the binary file
// in: vesselName, HCLL, LCLL
// out: true if written successfully, false otherwise
//************************************************************
bool Vessel::writeVessel(const string &VesselName, int HCLL, int LCLL)
{
    Vessel vessel(VesselName, HCLL, LCLL);
    Util::vesselFile.clear();             // Clear file flags
    Util::vesselFile.seekg(0, ios::end);  // Move to end
    vessel.writeToFile(Util::vesselFile); // Write vessel
    Util::vesselFile.flush();             // Save to disk
    return true;
}

//************************************************************
// Converts the vessel data into a formatted string
//************************************************************
string Vessel::toString() const
{
    stringstream ss;
    ss << "Vessel Name: " << vesselName
       << ", High Capacity Lane Length (HCLL): " << HCLL << "m"
       << ", Low Capacity Lane Length (LCLL): " << LCLL << "m";
    return ss.str();
}

//************************************************************
// Getter for vessel name
//************************************************************
string Vessel::getName() const
{
    return string(vesselName);
}

//************************************************************
// Getter for HCLL based on vessel name
//************************************************************
int Vessel::getHCLL(const string &vesselName) const
{
    Util::vesselFile.clear();
    Util::vesselFile.seekg(0, ios::beg);

    Vessel v;
    while (Util::vesselFile.eof())
    {
        v.readFromFile(Util::vesselFile);
        if (strcmp(v.vesselName, vesselName.c_str()) == 0)
        {
            cout <<"\n HCLL printed: " << v.HCLL << endl;
            return v.HCLL;

        }
    }

    return -1; // Not found
}

//************************************************************
// Getter for LCLL based on vessel name
//************************************************************
int Vessel::getLCLL(const string &vesselName) const
{
    Util::vesselFile.clear();
    Util::vesselFile.seekg(0, ios::beg);

    Vessel v;
    while (Util::vesselFile.read(reinterpret_cast<char *>(&v), RECORD_SIZE))
    {
        if (strcmp(v.vesselName, vesselName.c_str()) == 0)
        {
            cout <<"\n LCLL printed: " << v.LCLL << endl;
            return v.LCLL;
        }
    }
    return -1; // Not found
}

//************************************************************
// Calculates and returns total capacity (HCLL + LCLL)
//************************************************************
int Vessel::getCapacity() const
{
    return HCLL + LCLL;
}
