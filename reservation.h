//************************************************************
// reservation.h
//************************************************************
// Purpose: Represents a binary-storable reservation record with
// check-in status and file-level operations for managing ferry
// reservations.
//************************************************************

#pragma once

#include <fstream>
#include <string>

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

        Reservation(); // Default Constructor
        Reservation(const std::string& sailingId, const std::string& license, const std::string& phone); // Parametrised Constructor

        void writeToFile(std::fstream& file) const;
        void readFromFile(std::fstream& file);
        
        std::string toString() const;

        static int getTotalReservationsOnSailing(const std::string& sailingId) const;
        static bool removeReservation(const std::string& sailingId, const std::string& license) const;
        static bool checkExists(const std::string& sailingId, const std::string& license) const;
        static bool writeReservation(const std::string& sailingId, const std::string& license,) const;
        static void setCheckedIn(const std::string& sailingId, const std::string& license) const;


};