//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// Vessel.cpp
//************************************************************
// Purpose: Represents a binary-stored vehicle record with license,
// phone, height, and length data. Used in reservations.
// July 21, 2025 Revision 1 - Darpandeep Kaur
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
    HCLL = 3600.0;                        // Initialize High Capacity Lane Length to 0.0
    LCLL = 3600.0;                        // Initialize Low Capacity Lane Length to 0.0
}

//************************************************************
// Parameterized Constructor
// Initializes the vessel with provided values
// in: vesselName, HCLL, LCLL
//************************************************************
Vessel::Vessel(const string &vesselName, double HCLL, double LCLL)
{
    strncpy(this->vesselName, vesselName.c_str(), NAME_LENGTH); // Copy vesselName string
    this->vesselName[NAME_LENGTH] = '\0';                       // Null-terminate
    this->HCLL = HCLL; // Set High Capacity Lane Length
    this->LCLL = LCLL; // Set Low Capacity Lane Length
}

//************************************************************
// Writes the vessel record to a binary file
// in-out: file - binary file stream
//************************************************************
void Vessel::writeToFile(fstream &file) const
{
    if (file.is_open())
    {
        file.write(vesselName, NAME_LENGTH + 1);                         // Write vesselName
        file.write(reinterpret_cast<const char *>(&HCLL), sizeof(HCLL)); // Write High Capacity Lane Length
        file.write(reinterpret_cast<const char *>(&LCLL), sizeof(LCLL)); // Write Low Capacity Lane Length
    }
    else
    {
        cout << "Error opening file for writing." << endl; // Error message if file is not open
    }
}

//************************************************************
// Reads the vessel record from a binary file
// in-out: file - binary file stream
//************************************************************
void Vessel::readFromFile(fstream &file)
{
    if (file.is_open())
    {
        file.read(vesselName, NAME_LENGTH + 1);                   // Read vesselName
        file.read(reinterpret_cast<char *>(&HCLL), sizeof(HCLL)); // Read High Capacity Lane Length
        file.read(reinterpret_cast<char *>(&LCLL), sizeof(LCLL)); // Read Low Capacity Lane Length
    }
}

//************************************************************
// Checks if a vessel with the given ID exists
// in: vesselId
// out: true if exists, false otherwise
//************************************************************
bool Vessel::checkExist(const string &vesselName)
{
    fstream file;
    file.open("vessel.dat", ios::in | ios::binary); // Open vessel file for reading
    if (!file.is_open())
    {
        cout << "Error opening vessel file." << endl;
        return false; // File could not be opened
    }
    Vessel vessel; // Create a Vessel object to read records
    while (Util::vesselFile.read(reinterpret_cast<char *>(&vessel), RECORD_SIZE))
    { // Read each record
        if (strcmp(vessel.vesselName, vesselName.c_str()) == 0)
        {                // Compare vesselId
            return true; // Vessel with the given ID exists
        }
    }
    return false; // Vessel with the given ID does not exist
}

//************************************************************
// Writes a new vessel record to the file
// in: vesselName, vesselId, HCLL, LCLL
// out: true if written successfully, false otherwise
//************************************************************
bool Vessel::writeVessel(const string &VesselName, double HCLL, double LCLL)
{
    if (checkExist(vesselName))
    {
        cout << "Vessel with Name " << vesselName << " already exists." << endl;
        return false; // Vessel already exists
    }

    Vessel vessel(vesselName, HCLL, LCLL); // Create a Vessel object with provided values
    Util::vesselFile.clear();                        // Clear any existing flags
    Util::vesselFile.seekg(0, ios::end);             // Move to the end of the file
    vessel.writeToFile(Util::vesselFile);            // Write the vessel record to the file
    Util::vesselFile.flush();                        // Ensure data is written to disk
}

//************************************************************
// Converts the vessel record to a formatted string
// out: formatted string representation of the vessel
//************************************************************
string Vessel::toString() const
{
    stringstream ss; // Create a string stream to format the output
    ss << "Vessel Name: " << vesselName << ", "
       << "High Capacity Lane Legth (HCLL): " << HCLL << "m, "
       << "Low Capacity Lane Length (LCLL): " << LCLL << "m. ";
    return ss.str(); // Return the formatted string
}

//************************************************************
// Getters
//************************************************************
string Vessel::getName() const
{
    return string(vesselName); // Return vesselName as a string
}

double Vessel::getHCLL() const
{
    return HCLL; // Return High Capacity Lane Length
}

double Vessel::getLCLL() const
{
    return LCLL; // Return Low Capacity Lane Length
}

//************************************************************
// Returns the capacity of the vessel
// out: capacity of the vessel
//************************************************************
int Vessel::getCapacity() const
{
    return std::round((HCLL + LCLL) * 100.0) / 100.0; // Return the sum of HCLL and LCLL as capacity with two decimal places
}
