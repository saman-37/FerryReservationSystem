//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//************************************************************
// VesselStub.cpp
//************************************************************
// Purpose: Stub Vessel class for Top-Down test on OtherControls to test createVessel function using stubbed Vessel class
// 23 July, 2025 Revision 1 - Darpandeep Kaur
//************************************************************

#include "Vessel.h"
#include <iostream>
#include <fstream>

using namespace std;

Vessel vessel; // Global instance of Vessel to be used in createVessel function

const int Vessel::NAME_LENGTH; // Length of the vessel name
const int Vessel::RECORD_SIZE; // Size of the record in bytes

Vessel::Vessel(const string &vesselName, double HCLL, double LCLL)
{
    // Stub constructor does not initialize any member variables
    cout << "[STUB] Vessel created with name: " << vesselName << endl;
}

bool Vessel::writeVessel(const string &vesselName, double HCLL, double LCLL)
{
    cout << "[STUB] Writing vessel with name: " << vesselName <<  ", HCLL: " << HCLL << ", LCLL: " << LCLL << endl;
    // Stub simulates successful write
    return true;
}