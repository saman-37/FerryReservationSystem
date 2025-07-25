//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//************************************************************
// testOtherControls.cpp
//************************************************************
// Purpose: Top-Down test on OtherControls to test createVessel function using stubbed Vessel class
// 23 July, 2025 Revision 1 - Darpandeep Kaur
//************************************************************

#include "OtherControls.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "UNIT TEST: OtherControls - createVessel function\n";

    OtherControls vessel1; // Create an instance of OtherControl to access createVessel function

    // Test data for creating vessel 1
    string vesselName = "Test Vessel 1.0";
    string vesselId = "TV001";
    double HCLL = 3000.0; // High Clearance Length Limit
    double LCLL = 2500.0; // Low Clearance Length Limit

    // Call the createVessel function with test data

    bool result = vessel1.createVessel(vesselName, vesselId, HCLL, LCLL);

    if (result)
    {
        cout << " PASS: Vessel created successfully.\n";
    }
    else
    {
        cout << " FAIL: Vessel creation failed with error code: " << endl;
    }

    return 0;
}
