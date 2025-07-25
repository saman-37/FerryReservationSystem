//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ReservationUnitTest.cpp
// Unit test for Reservation.cpp - Version 1
// Version History:
// July 24, 2025 - Created for Assignment 4 Unit Testing

#include <iostream>
#include <fstream>
#include <cstring>
#include "Reservation.h"

using namespace std;

int main()
{
    cout << "UNIT TEST: Reservation Binary File I/O Write and Read \n";

    // Create test reservation and write to file
    Reservation r1("7786651002", "van-07-06", true);

    fstream outFile("test_reservation.dat", ios::out | ios::binary);
    if (!outFile)
    {
        cout << "Error opening file for writing.\n";
        return 1;
    }

    r1.writeToFile(outFile); // also closes the file

    // Read back into a new object
    Reservation r2;
    fstream inFile("test_reservation.dat", ios::in | ios::binary);
    if (!inFile)
    {
        cout << "Error opening file for reading.\n";
        return 1;
    }

    r2.readFromFile(inFile);
    inFile.close();

    // Compare the two reservations
    bool pass = true;

    if (strcmp(r1.sailingId, r2.sailingId) != 0)
    {
        cout << "sailingId mismatch\n";
        pass = false;
    }

    if (strcmp(r1.license, r2.license) != 0)
    {
        cout << "license mismatch\n";
        pass = false;
    }

    if (r1.onBoard != r2.onBoard)
    {
        cout << "onBoard mismatch\n";
        pass = false;
    }

    // --- Output result ---
    if (pass)
    {
        cout << "Reservation file write and read back test: Passed!\n";
        cout << r2.toString();
    }
    else
    {
        cout << "Reservation file write and read back test: Failed!\n";
    }

    return 0;
}
