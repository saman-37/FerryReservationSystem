//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// reservation.h
//************************************************************
// Purpose: Represents a binary-storable reservation record with
// check-in status and provides all file-level operations for 
// managing ferry reservations in a fixed-length format.
// July 24, 2025 - ver. 3 - Created by all team members
//************************************************************

#pragma once

#include <string>
#include <fstream>
#include "Sailing.h"

using namespace std;

class Reservation
{
public:
    //************************************************************
    // Constants for binary fixed-length record layout
    //************************************************************
    static const int SAILING_ID_LENGTH = 9;       // Fixed sailing ID length
    static const int LICENSE_LENGTH = 10;         // Fixed license length
    static const int RECORD_SIZE = LICENSE_LENGTH + 1 + SAILING_ID_LENGTH + 1 + sizeof(bool); 
    // Total size of one binary reservation record (+2 for null terminators)

    //************************************************************
    // Reservation record fields (stored in binary file)
    //************************************************************
    char sailingId[SAILING_ID_LENGTH + 1]; // Sailing ID (null-terminated)
    char license[LICENSE_LENGTH + 1];      // License plate (null-terminated)
    bool onBoard;                          // true if the vehicle has boarded

    //************************************************************
    // Constructors
    //************************************************************
    Reservation(); // Default Constructor

    Reservation(const string &license, const string &sailingId, const bool &onBoard);
    // in: license, sailingId, onBoard — used to initialize new record

    //************************************************************
    // Binary File I/O Functions
    //************************************************************
    void writeToFile(fstream &file) const; // in-out: writes this reservation to binary stream
    bool readFromFile(fstream &file);      // in-out: loads this reservation from binary stream

    //************************************************************
    // Query Total Reservations for a Given Sailing
    //************************************************************
    static int getTotalReservationsOnSailing(const string &sailingId);              // in: sailingId

    //************************************************************
    // Remove Specific Reservation
    //************************************************************
    static bool removeReservation( const string &license, const string &sailingId);                // in: sailingId, license

    //************************************************************
    // Remove All Reservations for a Given Sailing
    //************************************************************
    static bool removeReservationsOnSailing(const string &sailingId);               // in: sailingId

    //************************************************************
    // Check if Reservation Exists
    //************************************************************
    static bool checkExist(const string &license, const string &sailingId);               // in: sailingId, license

    //************************************************************
    // Create a New Reservation
    //************************************************************
    static bool writeReservation( const string &license, const string &sailingId);                // in: sailingId, license

    //************************************************************
    // Mark Reservation as Checked In
    //************************************************************
    static void setCheckedIn(const string &license); // in: sailingId, license

    static float calculateFare(const string &license); // Calculates fare based on vehicle type and sailing
    //************************************************************
    // Format Reservation Record as Readable String
    //************************************************************
    string toString() const; // out: returns formatted string version of reservation
};