//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*********************************************************
// ReservationTestDriver.cpp
//*********************************************************
// Purpose: Unit test for the Reservation class. This program 
// tests the functionality of writing a reservation, checking 
// for its existence, and reading from the reservation file.
// 
// July 24, 2025 - Version 2 - Samanpreet Kaur
//*********************************************************

#include "Reservation.h"
#include <iostream>
#include "Util.h"
#include "Vehicle.h"
#include "UI.h"

using namespace std;

int main()
{
    // Create a Reservation object
    Reservation r;

    // Step 1: Write a reservation
    r.writeReservation("NAVIX3", "van-07-07");

    // Step 2: Check if the reservation exists
    bool exists = Reservation::checkExist("NAVIX3", "van-07-07");
    cout << "Reservation exists: " << (exists ? "Yes" : "No") << endl;

    // Step 3: Read the reservation from the file
    r.readFromFile(Util::reservationFile);

    // Return 0 to indicate successful execution
    return 0; 
}
