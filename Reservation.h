//************************************************************
// reservation.h
//************************************************************
// Purpose: Represents a binary-storable reservation record with
// check-in status and file-level operations for managing ferry
// reservations.
// July 10, 2025 Revision 1
//************************************************************
#pragma once

#include <string>
#include <fstream>

using namespace std;

class Reservation
{

public:
    static const int SAILING_ID_LENGTH = 9;
    static const int LICENSE_LENGTH = 10;
    bool onBoard;
    static const int RECORD_SIZE = LICENSE_LENGTH + 1 + SAILING_ID_LENGTH + 1 + sizeof(bool);

    char sailingId[SAILING_ID_LENGTH + 1]; // +1 for null terminator
    char license[LICENSE_LENGTH + 1];      // +1 for null terminator

    Reservation();                                                                     // Default Constructor                                                                   // Default Constructor
    Reservation(const string &license, const string &sailingId, const bool &onBoard); // in: sailingID, license, phone

    void writeToFile(fstream &file) const; // in-out: file - binary file stream
    void readFromFile(fstream &file);      // in-out: file - binary file stream

    static int getTotalReservationsOnSailing(const string &sailingId);             // in: sailingID
    static bool removeReservation(const string &sailingId, const string &license); // in: sailingID, license
    static bool removeReservationsOnSailing(const string &sailingId);              // in: sailingId
    static bool checkExist(const string &sailingId, const string &license);        // in: sailingID, license
    static bool writeReservation(const string &sailingId, const string &license);  // in: sailingID, license, phone
    static void setCheckedIn(const string &sailingId, const string &license);      // in: sailingID, license
    string toString() const;                                                       // out: returns formatted string
};
