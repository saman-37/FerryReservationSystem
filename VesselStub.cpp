//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//************************************************************
// VesselStub.cpp
//************************************************************
// Purpose: Stub Vessel class for Top-Down test on OtherControls to test createVessel function using stubbed Vessel class
// 23 July, 2025 Version 1 - Darpandeep Kaur
//************************************************************

#include "Vessel.h"
#include <iostream>
#include <fstream>

using namespace std;

Vessel vessel; // Global instance of Vessel to be used in createVessel function

const int Vessel::NAME_LENGTH; // Length of the vessel name
const int Vessel::RECORD_SIZE; // Size of the record in bytes

Vessel::Vessel() 
{
    cout << "[STUB] Default Vessel constructor called" << endl;
}

// Vessel::Vessel(const string &vesselName, double HCLL, double LCLL) 
// {
//     cout << "[STUB] Vessel created with name: " << vesselName << endl;
// }

// bool Vessel::writeVessel(const string &vesselName, double HCLL, double LCLL) 
// {
//     cout << "[STUB] Writing vessel with name: " << vesselName
//          << ", HCLL: " << HCLL << ", LCLL: " << LCLL << endl;
//     return true;
// }

bool Vessel::checkExist(const string &vesselName) 
{
    cout << "[STUB] Checking existence of vessel: " << vesselName << endl;
    return false; // Simulate not found
}

void Vessel::writeToFile(fstream& file) const {
    cout << "[STUB] Writing vessel to file (no-op)" << endl;
}