//************************************************************
// reservation.h
//************************************************************
// Purpose: Represents a binary-storable reservation record with
// check-in status and file-level operations for managing ferry
// reservations.
// July 10, 2025 Revision 1
//************************************************************

#pragma once

#include <fstream>
#include <string>
using namespace std;

class Reservation {
    public:
        // Fixed lengths for binary record layout
        static const int SAILING_ID_LENGTH = 15;
        static const int LICENSE_LENGTH = 10;
        static const int PHONE_LENGTH = 14;
        static const int RECORD_SIZE = SAILING_ID_LENGTH + LICENSE_LENGTH + PHONE_LENGTH + 1;

        // Reservation record fields
        char sailingId[SAILING_ID_LENGTH + 1]; // +1 for null terminator
        char license[LICENSE_LENGTH + 1]; // +1 for null terminator
        char phone[PHONE_LENGTH + 1]; // +1 for null terminator
        bool checkedIn; // Track whether the vehicle has checked in.

        //HOW CAN WE PROVIDE A DEFAULT CONSTRUCTOR HERE?
        Reservation(); // Default Constructor 
        Reservation(const string& sailingId, const string& license, const string& phone); // in: sailingID, license, phone

        void writeToFile(fstream& file) const; // in-out: file - binary file stream
        void readFromFile(fstream& file); // in-out: file - binary file stream
        
        string toString() const; // out: returns formatted string

        void open(const string& sailingId, const string& license, const string& phone); // in: sailing ID, license, phone number

        static int getTotalReservationsOnSailing(const string& sailingId); // in: sailingID
        static bool removeReservation(const string& sailingId, const string& license); // in: sailingID, license
        static bool removeReservationsOnSailing(const string& sailingId); // in: sailingId
        static bool checkExist(const string& sailingId, const string& license); // in: sailingID, license
        static bool writeReservation(const string& sailingId, const string& license); // in: sailingID, license, phone
        static void setCheckedIn(const string& sailingId, const string& license); // in: sailingID, license


};
