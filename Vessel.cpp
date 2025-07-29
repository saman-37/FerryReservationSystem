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
    HCLL = 3600.0;                        // Default High Capacity Lane Length
    LCLL = 3600.0;                        // Default Low Capacity Lane Length
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
    if (Util::vesselFile.is_open())
    {
        Util::vesselFile.write(vesselName, NAME_LENGTH + 1);                        // Write vesselName
        Util::vesselFile.write(reinterpret_cast<const char *>(&HCLL), sizeof(int)); // Write HCLL
        Util::vesselFile.write(reinterpret_cast<const char *>(&LCLL), sizeof(int)); // Write LCLL
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
    if (Util::vesselFile.is_open())
    {
        Util::vesselFile.read(vesselName, NAME_LENGTH + 1);                   // Read vesselName
        Util::vesselFile.read(reinterpret_cast<char *>(&HCLL), sizeof(int)); // Read HCLL
        Util::vesselFile.read(reinterpret_cast<char *>(&LCLL), sizeof(int)); // Read LCLL
    }
}

//************************************************************
// Checks if a vessel with the given name exists
// in: vesselName
// out: true if exists, false otherwise
//************************************************************
bool Vessel::checkExist(const string &vesselName)
{
    Util::vesselFile.open("vessel.dat", ios::in | ios::binary); // Open vessel file for reading
    if (!Util::vesselFile.is_open())
    {
        cout << "Error opening vessel file." << endl;
        return false;
    }

    Vessel vessel;
    while (Util::vesselFile.read(reinterpret_cast<char *>(&vessel), RECORD_SIZE))
    {
        if (strcmp(vessel.vesselName, vesselName.c_str()) == 0)
        {
            return true; // Vessel found
        }
    }
    return false; // Not found
}

//************************************************************
// Writes a new vessel record to the binary file
// in: vesselName, HCLL, LCLL
// out: true if written successfully, false otherwise
//************************************************************
bool Vessel::writeVessel(const string &VesselName, double HCLL, double LCLL)
{
    if (checkExist(vesselName)) // Should be VesselName here; fix this in code logic
    {
        cout << "Vessel with Name " << vesselName << " already exists." << endl;
        return false;
    }

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
double Vessel::getHCLL(const string &vesselName) const
{
    Util::vesselFile.clear();
    Util::vesselFile.seekg(0, ios::beg);

    Vessel v;
    while (Util::vesselFile.read(reinterpret_cast<char *>(&v), RECORD_SIZE))
    {
        if (strcmp(v.vesselName, vesselName.c_str()) == 0)
        {
            return v.HCLL;
        }
    }
    return -1; // Not found
}

//************************************************************
// Getter for LCLL based on vessel name
//************************************************************
double Vessel::getLCLL(const string &vesselName) const
{
    Util::vesselFile.clear();
    Util::vesselFile.seekg(0, ios::beg);

    Vessel v;
    while (Util::vesselFile.read(reinterpret_cast<char *>(&v), RECORD_SIZE))
    {
        if (strcmp(v.vesselName, vesselName.c_str()) == 0)
        {
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
    return std::round((HCLL + LCLL) * 100.0) / 100.0;
}
