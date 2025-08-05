//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*********************************************************
// ReservationTestDriver.cpp
//*********************************************************
// Purpose: Unit test for the Reservation class. This
// program tests binary file I/O operations (write/read)
// for Reservation records, including adding, deleting, and 
// printing reservations.
// 
// July 24, 2025 - Version 2 - Samanpreet Kaur
//*********************************************************

#include <iostream>
#include <fstream>
#include "Reservation.h"
#include "Util.h"

using namespace std;

//**********************************************************
// printAllReservations()
//**********************************************************
// Purpose: Prints all reservations currently stored in the 
// reservation file. It reads each reservation and outputs 
// its details to the console.
//**********************************************************
void printAllReservations()
{
    // Clear any error flags
    Util::reservationFile.clear(); 
    // Move to the beginning of the file
    Util::reservationFile.seekg(0, ios::beg); 

    // Create a Reservation object
    Reservation r; 
    cout << "\n--- All Reservations ---\n";

    // Read and print each reservation until the end of file
    while (Util::reservationFile.peek() != EOF)
    {
        // Read reservation from file
        r.readFromFile(Util::reservationFile); 
        // Print reservation details
        cout << r.toString(); 
    }
    cout << "------------------------\n";
}

int main()
{
    // Step 1: Open reservation file for writing and reading
    // Clear any error flags
    Util::reservationFile.clear(); 
    // Open for writing
    Util::reservationFile.open("reservation.dat", 
                                ios::out 
                              | ios::binary); 

    // Close the file after writing
    Util::reservationFile.close(); 
    // Open for reading and writing
    Util::reservationFile.open("reservation.dat", 
                                ios::in 
                              | ios::out 
                              | ios::binary); 

    // Check if the reservation file opened successfully
    if (!Util::reservationFile.is_open())
    {
        // Error message
        cout << "Failed to open reservation.dat\n" << endl; 
        // Exit with error code
        return 1; 
    }

    // Step 2: Add 10 reservations
    Reservation::writeReservation("NAVIX3", "van-07-07");
    Reservation::writeReservation("NAVIX3", "van-07-07");
    Reservation::writeReservation("NAVIX3", "van-07-07");
    Reservation::writeReservation("NAVIX3", "van-07-07");
    Reservation::writeReservation("YADHUX3", "sur-07-07");
    Reservation::writeReservation("YADHX3", "sur-07-07");
    Reservation::writeReservation("SAMNX3", "bur-07-07");
    Reservation::writeReservation("NOBLX3", "bur-07-07");
    Reservation::writeReservation("NAVIX3", "bur-07-07");
    Reservation::writeReservation("DARPX3", "bur-07-07");

    // Step 3: Print all reservations
    printAllReservations();

    // Step 4: Delete specific reservation(DARPX3, bur-07-07)
    cout << "\nDeleting reservation with license: DARPX3, "
            << "sailing: bur-07-07\n";
    Reservation::removeReservation("DARPX3", "bur-07-07");

    // Step 5: Delete all reservations with sailing ID 
    // "bur-07-07"
    cout << "\nDeleting all reservations for sailing: "
            << "bur-07-07\n";
    Reservation::removeReservationsOnSailing("bur-07-07");

    // Step 6: Print all reservations after deletions
    printAllReservations();

    // Close the reservation file
    Util::reservationFile.close();
    // Return 0 to indicate successful execution
    return 0; 
}
