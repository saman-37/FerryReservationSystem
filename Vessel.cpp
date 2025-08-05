//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*********************************************************
// Vessel.cpp
//*********************************************************
// Purpose: Represents a binary-stored vessel record with
// name, high-capacity lane length (HCLL), and low-capacity
// lane length (LCLL). Used for defining sailings in the
// reservation system.
// July 21, 2025 Version 2 - Darpandeep Kaur
//*********************************************************

#include "Vessel.h"
#include "Util.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sstream>
using namespace std;

//*********************************************************
// Default Constructor
// Initializes the vessel with default values
//*********************************************************
Vessel::Vessel()
{
    // Initialize vesselName to empty string
    strncpy(vesselName, "", NAME_LENGTH); 
    // Null-terminate the vessel name
    vesselName[NAME_LENGTH] = '\0';       
    // Default High Capacity Lane Length
    HCLL = 3600;                         
    // Default Low Capacity Lane Length 
    LCLL = 3600;                          
}

//*********************************************************
// Parameterized Constructor
// Initializes the vessel with provided values
// in: vesselName, HCLL, LCLL
//*********************************************************
Vessel::Vessel(const string &vesselName, int HCLL, int LCLL)
{
    // Copy vesselName string
    strncpy(this->vesselName, vesselName.c_str(), NAME_LENGTH); 
    // Null-terminate the vessel name
    this->vesselName[NAME_LENGTH] = '\0';                       
    // Set High Capacity Lane Length
    this->HCLL = HCLL;                     
    // Set Low Capacity Lane Length                     
    this->LCLL = LCLL;                                          
}

//*********************************************************
// Writes the vessel record to the binary file
//*********************************************************
void Vessel::writeToFile(fstream &file) const
{
    // Check if the file is open for writing
    if (file.is_open()) 
    {
        // Write vesselName, HCLL, LCLL to file
        file.write(vesselName, NAME_LENGTH + 1);                        
        file.write(reinterpret_cast<const char *>(&HCLL), 
                    sizeof(int)); 
        file.write(reinterpret_cast<const char *>(&LCLL), 
                    sizeof(int)); 
    }
    else
    {
        // Error message if file is not open
        cout << "Error opening file for writing." << endl; 
    }
}

//*********************************************************
// Reads a vessel record from the binary file
//*********************************************************
void Vessel::readFromFile(fstream &file)
{
    // Check if the file is open for reading
    if (file.is_open()) 
    {
        // Read vesselName, HCLL, LCLL from file
        file.read(vesselName, NAME_LENGTH + 1);                   
        file.read(reinterpret_cast<char *>(&HCLL), 
                    sizeof(int));
        file.read(reinterpret_cast<char *>(&LCLL), 
                    sizeof(int));
    }
}

//*********************************************************
// Checks if a vessel with the given name exists
// in: vesselName
// out: true if exists, false otherwise
//*********************************************************
bool Vessel::checkExist(const string &vesselName)
{
    // Check if the vessel file is open
    if (Util::vesselFile.is_open()) 
    {
        // Clear any error flags
        Util::vesselFile.clear();
        // Move to the beginning of the file
        Util::vesselFile.seekg(0, ios::beg); 

        // Create a Vessel instance to read records
        Vessel vessel; 

        // Loop through records
        while (Util::vesselFile.read(reinterpret_cast
                <char*>(&vessel), Vessel::RECORD_SIZE)) 
        {
            // Check if the vessel name matches
            if (strcmp(vessel.vesselName, 
                        vesselName.c_str()) == 0) 
            {
                // Vessel found, return true
                return true; 
            }
        }
        // Not found, return false
        return false; 
    }
    else
    {
        // Error message if file is not open
        cout << "Error opening vessel file." << endl; 
        // Return false indicating failure
        return false; 
    }
}

//*********************************************************
// Writes a new vessel record to the binary file
// in: vesselName, HCLL, LCLL
// out: true if written successfully, false otherwise
//*********************************************************
bool Vessel::writeVessel(const string &VesselName, 
                            int HCLL, int LCLL)
{
    // Create a Vessel instance with provided values
    Vessel vessel(VesselName, HCLL, LCLL); 
    // Clear file flags
    Util::vesselFile.clear();             
    // Move to the end of the file
    Util::vesselFile.seekg(0, ios::end);  
    // Write the vessel record to the file
    vessel.writeToFile(Util::vesselFile); 
    // Output vessel details
    cout << vessel.toString() << endl;     
    // Save to disk
    Util::vesselFile.flush();    
    // Return true indicating success         
    return true; 
}

//*********************************************************
// Converts the vessel data into a formatted string
// out: formatted string
//*********************************************************
string Vessel::toString() const
{
    // Create a string stream for formatting
    stringstream ss; 
    // Format the string with vessel details
    ss << " Vessel Name: " << vesselName 
       << "\n High Capacity Lane Length (HCLL): " 
       << HCLL << "m"
       << "\n Low Capacity Lane Length (LCLL): " 
       << LCLL << "m"
       << "\n Total Capacity: " << HCLL + LCLL << "m";
    return ss.str(); // Return the formatted string
}

//*********************************************************
// Getter for vessel name
// out: vessel name as string
//*********************************************************
string Vessel::getName() const
{
    // Return the vessel name as a string
    return string(vesselName); 
}

//*********************************************************
// Getter for HCLL based on vessel name
// in: vesselName
// out: HCLL as integer, or -1 if not found
//*********************************************************
int Vessel::getHCLL(const string &vesselName) 
{
    // Check if the vessel file is open
    if (!Util::vesselFile.is_open()) 
    {
        // Error message if file is not open
        cout << "Error: vessel file not open.\n"; 
        // Return -1 to indicate error
        return -1; 
    }

    // Clear any error flags
    Util::vesselFile.clear(); 
    // Move to the beginning of the file
    Util::vesselFile.seekg(0, ios::beg); 

    // Create a Vessel instance to read records
    Vessel v; 
    // Loop indefinitely until a break condition is met
    while (true) 
    {
        // Read a vessel record
        v.readFromFile(Util::vesselFile); 
        // Break if end of file is reached
        if (Util::vesselFile.eof() 
            || Util::vesselFile.gcount() == 0) break; 

        // Check if the vessel name matches
        if (strcmp(v.vesselName, vesselName.c_str()) == 0) 
        {
            // Output found vessel name and return HCLL
            cout << "\nFound vessel: " << v.vesselName; 
            cout << "\nHCLL: " << v.HCLL << endl; 
            return v.HCLL; 
        }
    }
    // Return -1 if not found
    return -1; 
}

//*********************************************************
// Getter for LCLL based on vessel name
// in: vesselName
// out: LCLL as integer, or -1 if not found
//*********************************************************
int Vessel::getLCLL(const string &vesselName) 
{
    // Clear any error flags
    Util::vesselFile.clear(); 
    // Move to the beginning of the file
    Util::vesselFile.seekg(0, ios::beg); 

    // Create a Vessel instance to read records
    Vessel v; 
    // Loop indefinitely until a break condition is met
    while (true) 
    {
        // Read a vessel record
        v.readFromFile(Util::vesselFile); 

        // Break if end of file is reached
        if (Util::vesselFile.eof() 
            || Util::vesselFile.gcount() == 0) break; 

        // Check if the vessel name matches
        if (strcmp(v.vesselName, vesselName.c_str()) == 0) 
        {
            // Output found vessel name and return LCLL
            cout << "\nFound vessel: " << v.vesselName; 
            cout << "\nLCLL: " << v.LCLL << endl; 
            return v.LCLL; 
        }
    }
    // Return -1 if not found
    return -1; 
}

//*********************************************************
// Calculates and returns total capacity (HCLL + LCLL)
// out: total capacity as integer
//*********************************************************
int Vessel::getCapacity(const string &vesselName) 
{
    // Return the total capacity
    return getHCLL(vesselName) + getLCLL(vesselName); 
}