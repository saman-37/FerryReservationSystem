//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// TopDownTestDriver.cpp
//************************************************************
// Purpose: Top-down integration test for Ferry Reservation System.
// Simulates main operations like startup, creating vessels, sailings,
// reservations, and shutdown.
// July 25, 2025 Version 1 - Integration Test by Team
//************************************************************

#include "Util.h"
#include "OtherControls.h"
#include "SailingControl.h"
#include "Reservation.h"
#include "Vehicle.h"
#include "Vessel.h"
#include <iostream>
using namespace std;

int main() {
    cout << "=== Top-Down Integration Test Start ===" << endl;

    Util::startup();

    // Step 1: Create a Vessel
    string vesselName = "QueenOfVancouver";
    int hcll = 2000;
    int lcll = 1800;
    cout << "\nCreating vessel..." << endl;
    OtherControls::createVessel(vesselName, hcll, lcll);

    // Step 2: Create a Sailing for that Vessel
    string sailingId = "van-07-25";
    cout << "\nCreating sailing..." << endl;
    SailingControl::createSailing(sailingId, vesselName);

    // Step 3: Create a Reservation
    string licensePlate = "ABC1234";
    int dummyPhone = 7781234567; // Placeholder for unused phone number param
    cout << "\nCreating reservation..." << endl;
    //OtherControls::createReservation(dummyPhone, sailingId, licensePlate);

    // Step 4: Query that Sailing
    cout << "\nQuerying sailing..." << endl;
    SailingControl::querySailing(sailingId);

    // Step 5: Print all sailing reports
    cout << "\nGenerating sailing report..." << endl;
    SailingControl::printSailingReport();

    // Step 6: Check-in vehicle
    cout << "\nChecking in vehicle..." << endl;
    OtherControls::checkIn(licensePlate, sailingId);

    Util::shutdown();
    cout << "=== Top-Down Integration Test Complete ===" << endl;
    return 0;
}