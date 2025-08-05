//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*********************************************************
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
    static const int SAILING_ID_LENGTH = 9;// Fixed sailing ID length
    static const int LICENSE_LENGTH = 10;// Fixed license length
    
    // Total size of one binary reservation record 
    // (+2 for null terminators)
    static const int RECORD_SIZE = LICENSE_LENGTH + 1 
                    + SAILING_ID_LENGTH + 1 + sizeof(bool); 
    static const int REGULAR_VEHICLE_FARE = 14;

    //************************************************************
    // Reservation record fields (stored in binary file)
    //************************************************************
    char sailingId[SAILING_ID_LENGTH + 1]; 
    char license[LICENSE_LENGTH + 1];     
    bool onBoard;              // true if the vehicle has boarded

    //************************************************************
    // Constructors
    //************************************************************
    // Default Constructor
    Reservation(); 
    
    // license, sailingId, onBoard — used to initialize new record
    Reservation(const string &license, const string &sailingId,
                     const bool &onBoard);

    //************************************************************
    // Binary File I/O Functions
    //************************************************************
    // in-out: writes this reservation to binary stream
    void writeToFile(fstream &file) const; 

    // in-out: loads this reservation from binary stream
    bool readFromFile(fstream &file);      

    //************************************************************
    // Query Total Reservations for a Given Sailing
    // in: sailingId
    //************************************************************
    static int getTotalReservationsOnSailing(const string &sailingId);

    //************************************************************
    // Remove Specific Reservation
    // in: sailingId, license
    //************************************************************
    static bool removeReservation( const string &license, 
                                    const string &sailingId);                

    //************************************************************
    // Remove All Reservations for a Given Sailing
    // in: sailingId
    //************************************************************
    static bool removeReservationsOnSailing(const string &sailingId);               

    //************************************************************
    // Check if Reservation Exists
    // in: sailingId, license
    //************************************************************
    static bool checkExist(const string &license, 
                            const string &sailingId);               

    //************************************************************
    // Create a New Reservation
    // in: sailingId, license
    //************************************************************
    static bool writeReservation( const string &license, 
                                const string &sailingId);                

    //************************************************************
    // Mark Reservation as Checked In
    //************************************************************
    // in: sailingId, license
    static void setCheckedIn(const string &license); 

    // Calculates fare based on vehicle type and sailing
    static float calculateFare(const string &license); 
    //************************************************************
    // Format Reservation Record as Readable String
    // out: returns formatted string version of reservation
    //************************************************************
    string toString() const; 
};