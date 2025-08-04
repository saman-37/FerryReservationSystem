//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ReservationTestDriver.cpp
//************************************************************
// Unit test for Reservation.cpp
// Purpose: Tests binary file I/O operations (write/read) for Reservation records
// July 24, 2025 - Version 2 - Samanpreet Kaur
//************************************************************
#include <iostream>
#include <fstream>
#include "Reservation.h"
#include "Util.h"

using namespace std;

void printAllReservations()
{
    Util::reservationFile.clear();
    Util::reservationFile.seekg(0, ios::beg);

    Reservation r;
    cout << "\n--- All Reservations ---\n";

    while (Util::reservationFile.peek() != EOF)
    {
        r.readFromFile(Util::reservationFile);
        cout << r.toString();
    }
    cout << "------------------------\n";
}

int main()
{
    cout << "Total reservations on bur-07-07 are " << Reservation::getTotalReservationsOnSailing("bur-07-07");

    // Open reservation file
    Util::reservationFile.open("reservation.dat", ios::out | ios::binary | ios::trunc);
    Util::reservationFile.close(); // close so next open is clean
    Util::reservationFile.open("reservation.dat", ios::in | ios::out | ios::binary);
    if (!Util::reservationFile.is_open())
    {
        cerr << "Failed to open reservation.dat\n";
        return 1;
    }

    // Step 1: Add 10 reservations
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

    // Step 2: Print all reservations
    printAllReservations();

    // Step 3: Delete specific reservation (DARPX3, bur-07-07)
    cout << "\nDeleting reservation with license: DARPX3, sailing: bur-07-07\n";
    Reservation::removeReservation("DARPX3", "bur-07-07");

    // Step 4: Delete all reservations with sailing ID "bur-07-07"
    cout << "\nDeleting all reservations for sailing: bur-07-07\n";
    Reservation::removeReservationsOnSailing("bur-07-07");

    // Step 5: Print all reservations after deletions
    printAllReservations();

    Util::reservationFile.close();
    return 0;
}
