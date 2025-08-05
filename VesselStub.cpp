//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*********************************************************
// VesselStub.cpp
//*********************************************************
// Purpose: Stub implementation of the Vessel class for 
// Top-Down testing of the OtherControls module. This 
// stub is used to test the createVessel function using 
// a simplified version of the Vessel class.
// 
// July 23, 2025 - Version 2 - Darpandeep Kaur
//*********************************************************

#include "Vessel.h"
#include <iostream>
#include <fstream>

using namespace std;

// Length of the vessel name
static const int NAME_LENGTH = 25; 

//*********************************************************
// Vessel class stub
//*********************************************************
// Global instance of Vessel to be used in createVessel
// function for testing purposes.
Vessel vessel; 

//*********************************************************
// Default Constructor
//*********************************************************
Vessel::Vessel() 
{
    cout << "[STUB] Default Vessel constructor called" << endl;
}

//*********************************************************
// Parameterized Constructor
//*********************************************************
Vessel::Vessel(const string &vesselName, int HCLL, int LCLL) 
{
    cout << "[STUB] Vessel created with name: " << vesselName
             << endl;
}

//*********************************************************
// writeVessel
//*********************************************************
// Purpose: Simulates writing a vessel record. 
// Returns true to indicate success.
//*********************************************************
bool Vessel::writeVessel(const string &vesselName, 
                            int HCLL, int LCLL) 
{
    cout << "[STUB] Writing vessel with name: " 
         << vesselName << ", HCLL: " << HCLL 
         << ", LCLL: " << LCLL << endl;
    
    // Simulate successful write
    return true; 
}

//*********************************************************
// checkExist
//*********************************************************
// Purpose: Simulates checking for the existence of a 
// vessel by name. Always returns false to indicate 
// that the vessel does not exist.
//*********************************************************
bool Vessel::checkExist(const string &vesselName) 
{
    cout << "[STUB] Checking existence of vessel: " 
         << vesselName << endl;
    
    // Simulate not found
    return false; 
}

//*********************************************************
// writeToFile
//*********************************************************
// Purpose: Stub implementation for writing the vessel 
// to a file. This is a no-op in the stub version.
//*********************************************************
void Vessel::writeToFile(fstream& file) const {
    cout << "[STUB] Writing vessel to file (no-op)" << endl;
}

//*********************************************************
// readFromFile
//*********************************************************
// Purpose: Stub implementation for reading a vessel 
// from a file. This is a no-op in the stub version.
//*********************************************************
void Vessel::readFromFile(fstream& file) {
    cout << "[STUB] Reading vessel from file (no-op)" << endl;
}
