//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ReservationTestDriver.cpp
//************************************************************
// Unit test for Reservation.cpp
// Purpose: Tests binary file I/O operations (write/read) for Reservation records
// July 24, 2025 - Version 1 - Darpandeep Kaur
//************************************************************

#include <iostream>
#include <fstream>
#include <cstring>
#include "Reservation.h"

using namespace std;

int main()
{
    cout << "UNIT TEST: Reservation Binary File I/O Write and Read \n";

    //************************************************************
    // Step 1: Create test reservation and write to file
    //************************************************************
    Reservation r1("7786651002", "van-07-06", true); // Create test reservation

    fstream outFile("test_reservation.dat", ios::out | ios::binary);
    if (!outFile)
    {
        cout << "Error opening file for writing.\n";
        return 1;
    }

    r1.writeToFile(outFile); // Write record to file (function closes the file internally)

    //************************************************************
    // Step 2: Read back the reservation from file into a new object
    //************************************************************
    Reservation r2; // Empty object for comparison

    fstream inFile("test_reservation.dat", ios::in | ios::binary);
    if (!inFile)
    {
        cout << "Error opening file for reading.\n";
        return 1;
    }

    r2.readFromFile(inFile); // Load data from binary file
    inFile.close();          // Close file after read

    //************************************************************
    // Step 3: Compare all fields between written and read record
    //************************************************************
    bool pass = true; // Flag for pass/fail result

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

    //************************************************************
    // Step 4: Output unit test result to console
    //************************************************************
    if (pass)
    {
        cout << "Reservation file write and read back test: Passed!\n";
        cout << r2.toString(); // Display read-back data
    }
    else
    {
        cout << "Reservation file write and read back test: Failed!\n";
    }

    return 0;
}