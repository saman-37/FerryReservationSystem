//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// reservation.h
/*

Version History:
ver. 1 -July 12, 2025 Original by  all team members
--------------------------------------------------------------
Purpose: Represents a binary-storable reservation record with check-in status and file-level operations for managing ferry reservations.

*/
#pragma once

#include <string>
#include <fstream>
#include "Sailing.h"

using namespace std;

class Reservation
{

public:
    static const int SAILING_ID_LENGTH = 9;                                                   // constant length for fixed length record
    static const int LICENSE_LENGTH = 10;                                                     // constant length for fixed length record
    static const int RECORD_SIZE = LICENSE_LENGTH + 1 + SAILING_ID_LENGTH + 1 + sizeof(bool); // additional 2 is allocated for 2 null terminators
    char sailingId[SAILING_ID_LENGTH + 1];                                                    // string is dynamic, character array is contiguous, and holds fixed-length memory, added +1 for null terminator
    char license[LICENSE_LENGTH + 1];                                                         // +1 for null terminator
    bool onBoard;                                                                             // variable to indicate if the vehicle is on board

    Reservation();                                                                                // Default Constructor                                                                   // Default Constructor
    Reservation(const string &license, const string &sailingId, const bool &onBoard);             // in: sailingID, license, phone
    void writeToFile(fstream &file) const;                                                        // in-out: file - binary file stream
    void readFromFile(fstream &file);                                                             // in-out: file - binary file stream
    static int getTotalReservationsOnSailing(const string &sailingId);                            // in: sailingID
    static int getTotalReservationsOnSailing(const string &sailingId, fstream &file);             // in: sailingID
    static bool removeReservation(const string &sailingId, const string &license);                // in: sailingID, license
    static bool removeReservation(const string &sailingId, const string &license, fstream &file); // in: sailingID, license
    static bool removeReservationsOnSailing(const string &sailingId);                             // in: sailingId
    static bool removeReservationsOnSailing(const string &sailingId, fstream &file);              // in: sailingId
    static bool checkExist(const string &sailingId, const string &license);                       // in: sailingID, license
    static bool checkExist(const string &sailingId, const string &license, fstream &file);        // in: sailingID, license
    static bool writeReservation(const string &sailingId, const string &license, fstream &file);  // in: sailingID, license, phone
    static bool writeReservation(const string &sailingId, const string &license);                 // in: sailingID, license, phone
    static void setCheckedIn(const string &sailingId, const string &license);                     // in: sailingID, license
    static void setCheckedIn(const string &sailingId, const string &license, fstream &file);      // in: sailingID, license
    string toString() const;                                                                      // out: returns formatted string
};
