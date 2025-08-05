//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//************************************************************
// VesselStub.cpp
//************************************************************
// Purpose: Stub Vessel class for Top-Down test on OtherControls to test createVessel function using stubbed Vessel class
// 23 July, 2025 Version 2 - Darpandeep Kaur
//************************************************************

#include "Vessel.h"
#include <iostream>
#include <fstream>

using namespace std;

static const int NAME_LENGTH = 25; // Length of the vessel name

//************************************************************
// Vessel class stub
//************************************************************
Vessel vessel; // Global instance of Vessel to be used in createVessel function

//************************************************************
// Default Constructor
//************************************************************
Vessel::Vessel() 
{
    cout << "[STUB] Default Vessel constructor called" << endl;
}

//************************************************************
// Parameterized Constructor
//************************************************************
Vessel::Vessel(const string &vesselName, int HCLL, int LCLL) 
{
    cout << "[STUB] Vessel created with name: " << vesselName << endl;
}

//************************************************************
// writeVessel
//************************************************************
bool Vessel::writeVessel(const string &vesselName, int HCLL, int LCLL) 
{
    cout << "[STUB] Writing vessel with name: " << vesselName
         << ", HCLL: " << HCLL << ", LCLL: " << LCLL << endl;
    return true;
}

//************************************************************
// checkExist
//************************************************************
bool Vessel::checkExist(const string &vesselName) 
{
    cout << "[STUB] Checking existence of vessel: " << vesselName << endl;
    return false; // Simulate not found
}

//************************************************************
// writeToFile
//************************************************************
void Vessel::writeToFile(fstream& file) const {
    cout << "[STUB] Writing vessel to file (no-op)" << endl;
}

//************************************************************
// readFromFile
//************************************************************
// Stub implementation for reading from file (not implemented)
//************************************************************
void Vessel::readFromFile(fstream& file) {
    cout << "[STUB] Reading vessel from file (no-op)" << endl;
}