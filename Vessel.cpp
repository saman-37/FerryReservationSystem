//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// Vessel.cpp
//************************************************************
// Purpose: Represents a binary-stored vessel record with name,
// high-capacity lane length (HCLL), and low-capacity lane length (LCLL).
// Used for defining sailings in the reservation system.
// July 21, 2025 Version 2 - Darpandeep Kaur
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
    vesselName[NAME_LENGTH] = '\0';       // Null-terminate the vessel name
    HCLL = 3600;                          // Default High Capacity Lane Length
    LCLL = 3600;                          // Default Low Capacity Lane Length
}

//************************************************************
// Parameterized Constructor
// Initializes the vessel with provided values
// in: vesselName, HCLL, LCLL
//************************************************************
Vessel::Vessel(const string &vesselName, int HCLL, int LCLL)
{
    strncpy(this->vesselName, vesselName.c_str(), NAME_LENGTH); // Copy vesselName string
    this->vesselName[NAME_LENGTH] = '\0';                       // Null-terminate the vessel name
    this->HCLL = HCLL;                                          // Set High Capacity Lane Length
    this->LCLL = LCLL;                                          // Set Low Capacity Lane Length
}

//************************************************************
// Writes the vessel record to the binary file
//************************************************************
void Vessel::writeToFile(fstream &file) const
{
    if (file.is_open()) // Check if the file is open for writing
    {
        file.write(vesselName, NAME_LENGTH + 1);                        // Write vesselName to file
        file.write(reinterpret_cast<const char *>(&HCLL), sizeof(int)); // Write HCLL to file
        file.write(reinterpret_cast<const char *>(&LCLL), sizeof(int)); // Write LCLL to file
    }
    else
    {
        cout << "Error opening file for writing." << endl; // Error message if file is not open
    }
}

//************************************************************
// Reads a vessel record from the binary file
//************************************************************
void Vessel::readFromFile(fstream &file)
{
    if (file.is_open()) // Check if the file is open for reading
    {
        file.read(vesselName, NAME_LENGTH + 1);                   // Read vesselName from file
        file.read(reinterpret_cast<char *>(&HCLL), sizeof(int)); // Read HCLL from file
        file.read(reinterpret_cast<char *>(&LCLL), sizeof(int)); // Read LCLL from file
    }
}

//************************************************************
// Checks if a vessel with the given name exists
// in: vesselName
// out: true if exists, false otherwise
//************************************************************
bool Vessel::checkExist(const string &vesselName)
{
    if (Util::vesselFile.is_open()) // Check if the vessel file is open
    {
        Util::vesselFile.clear(); // Clear any error flags
        Util::vesselFile.seekg(0, ios::beg); // Move to the beginning of the file

        Vessel vessel; // Create a Vessel instance to read records
        while (Util::vesselFile.read(reinterpret_cast<char*>(&vessel), Vessel::RECORD_SIZE)) // Loop through records
        {
            if (strcmp(vessel.vesselName, vesselName.c_str()) == 0) // Check if the vessel name matches
            {
                return true; // Vessel found, return true
            }
        }
        return false; // Not found, return false
    }
    else
    {
        cout << "Error opening vessel file." << endl; // Error message if file is not open
        return false; // Return false indicating failure
    }
}

//************************************************************
// Writes a new vessel record to the binary file
// in: vesselName, HCLL, LCLL
// out: true if written successfully, false otherwise
//************************************************************
bool Vessel::writeVessel(const string &VesselName, int HCLL, int LCLL)
{
    Vessel vessel(VesselName, HCLL, LCLL); // Create a Vessel instance with provided values
    Util::vesselFile.clear();             // Clear file flags
    Util::vesselFile.seekg(0, ios::end);  // Move to the end of the file
    vessel.writeToFile(Util::vesselFile); // Write the vessel record to the file
    cout << vessel.toString() << endl;     // Output vessel details
    Util::vesselFile.flush();             // Save to disk
    return true; // Return true indicating success
}

//************************************************************
// Converts the vessel data into a formatted string
// out: formatted string
//************************************************************
string Vessel::toString() const
{
    stringstream ss; // Create a string stream for formatting
    ss << " Vessel Name: " << vesselName // Format the string with vessel details
       << "\n High Capacity Lane Length (HCLL): " << HCLL << "m"
       << "\n Low Capacity Lane Length (LCLL): " << LCLL << "m"
       << "\n Total Capacity: " << HCLL + LCLL << "m";
    return ss.str(); // Return the formatted string
}

//************************************************************
// Getter for vessel name
// out: vessel name as string
//************************************************************
string Vessel::getName() const
{
    return string(vesselName); // Return the vessel name as a string
}

//************************************************************
// Getter for HCLL based on vessel name
// in: vesselName
// out: HCLL as integer, or -1 if not found
//************************************************************
int Vessel::getHCLL(const string &vesselName) 
{
    if (!Util::vesselFile.is_open()) // Check if the vessel file is open
    {
        cout << "Error: vessel file not open.\n"; // Error message if file is not open
        return -1; // Return -1 to indicate error
    }

    Util::vesselFile.clear(); // Clear any error flags
    Util::vesselFile.seekg(0, ios::beg); // Move to the beginning of the file

    Vessel v; // Create a Vessel instance to read records
    while (true) // Loop indefinitely until a break condition is met
    {
        v.readFromFile(Util::vesselFile); // Read a vessel record
        if (Util::vesselFile.eof() || Util::vesselFile.gcount() == 0) break; // Break if end of file is reached
        
        if (strcmp(v.vesselName, vesselName.c_str()) == 0) // Check if the vessel name matches
        {
            cout << "\nFound vessel: " << v.vesselName; // Output found vessel name
            cout << "\nHCLL: " << v.HCLL << endl; // Output HCLL
            return v.HCLL; // Return the HCLL if found
        }
    }
    return -1; // Return -1 if not found
}

//************************************************************
// Getter for LCLL based on vessel name
// in: vesselName
// out: LCLL as integer, or -1 if not found
//************************************************************
int Vessel::getLCLL(const string &vesselName) 
{
    Util::vesselFile.clear(); // Clear any error flags
    Util::vesselFile.seekg(0, ios::beg); // Move to the beginning of the file

    Vessel v; // Create a Vessel instance to read records
    while (true) // Loop indefinitely until a break condition is met
    {
        v.readFromFile(Util::vesselFile); // Read a vessel record

        if (Util::vesselFile.eof() || Util::vesselFile.gcount() == 0) break; // Break if end of file is reached

        if (strcmp(v.vesselName, vesselName.c_str()) == 0) // Check if the vessel name matches
        {
            cout << "\nFound vessel: " << v.vesselName; // Output found vessel name
            cout << "\nLCLL: " << v.LCLL << endl; // Output LCLL
            return v.LCLL; // Return the LCLL if found
        }
    }
    return -1; // Return -1 if not found
}

//************************************************************
// Calculates and returns total capacity (HCLL + LCLL)
// out: total capacity as integer
//************************************************************
int Vessel::getCapacity(const string &vesselName) 
{
    return getHCLL(vesselName) + getLCLL(vesselName); // Return the total capacity
}