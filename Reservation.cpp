//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// reservation.cpp
/*
Version History:
ver. 1 - July 23, 2025 by Saman and Noble
      
--------------------------------------------------------------
This module provides the interface for the reservation file, functionality to add, delete, look for reservation records, using binary random access. The reservation file contains the unsorted fixed-length record which are not the best storage for access, yet provides faster inserts and deletes. All the attributes of a newly created reservation and functions to modify them are put together here for encapsulation.
*/

//--------------------------------------------------------------
#include "Reservation.h"
#include "util.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <sstream>
using namespace std;
// --------------------------------------------------------------

//************************************************************
// Default Constructor
// Initializes the reservation with default values
//************************************************************
Reservation::Reservation()
{
    strcpy(sailingId, "");
    strcpy(license, "");
    onBoard = false; // Default to not on board
}

//************************************************************
// Parameterized Constructor
// Initializes the reservation with provided values
// in: sailing_id, license, on_board
//************************************************************
Reservation::Reservation(const string &license, const string &sailingId, const bool &onBoard)
{
    strcpy(this->sailingId, sailingId.c_str());
    strcpy(this->license, license.c_str());
    this->sailingId[SAILING_ID_LENGTH] = '\0'; // Null-terminate the sailing ID attribute
    this->license[LICENSE_LENGTH] = '\0';      // Null-terminate the license attribute
    this->onBoard = onBoard;                   // Default to not on board
};

//************************************************************
// Pre-conditions: assume binary file stream is open, and in both input and output modes
// Writes the reservation record to a binary file
// in-out: file - binary file stream
//************************************************************
void Reservation::writeToFile(fstream &file) const // in-out: file - binary file stream
{
    // file stream object should be in append mode, so that entry is at end of file
    if (file.is_open()) // file stream object is open and provided by util in all the 3 states of input, output and binary
    {
        file.write(license, sizeof(license));                                  // Write license, update, should be sizeOf(license) + 1 for null terminator
        file.write(sailingId, sizeof(sailingId));                              // Write sailing ID
        file.write(reinterpret_cast<const char *>(&onBoard), sizeof(onBoard)); // Write onBoard status; we need reinterpret cast as the type should be character memory address
        file.flush();                                                          // Ensure data is written to disk
    }

    else
    {
        cout << "Error opening file for writing." << endl;
    }
};

//************************************************************
// Pre-conditions: assume binary file stream is open, and in both input and output modes
// Reads the reservation record from a binary file
// in-out: file - binary file stream
//************************************************************
void Reservation::readFromFile(fstream &file) // in-out: file - binary file stream
{
    if (file.is_open()) // file stream object is open and provided by util in all the 3 states of input, output and binary
    {
        file.read(license, sizeof(license));                            // Read into the license instance variable
        file.read(sailingId, sizeof(sailingId));                        // Read sailingId instance variable
        file.read(reinterpret_cast<char *>(&onBoard), sizeof(onBoard)); // Read onBoard status
    }
    else
    {
        cout << "Error opening file for reading." << endl;
    }
};

//************************************************************
// Converts the reservation record to a formatted string
// out: returns formatted string
//************************************************************
string Reservation::toString() const // out: returns formatted string
{
    stringstream ss;
    ss << "Reservation Details:\n"
       << "Sailing ID: " << sailingId << "\n"
       << "License: " << license << "\n"
       << "On Board: " << (onBoard ? "Yes" : "No") << "\n";
    return ss.str();
};

//************************************************************
// Calculates the total number of reservations for a specific sailing ID
// in: sailingId - the sailing ID to check
//************************************************************
int Reservation::getTotalReservationsOnSailing(const string &sailingId){
    return getTotalReservationsOnSailing(sailingId, file);
} 
int Reservation::getTotalReservationsOnSailing(const string &sailingId, fstream &file) // in: sailingID
{
    // loop through all the records in the reservation file
    // do random access and take pointer to the second attribute in each line/record to seek sailing id
    // if it matches the sailingId, increment the counter

    if (file.is_open())
    {
        file.clear();            // Clear any existing flags
        file.seekg(0, ios::beg); // Move to the beginning of the file

        Reservation reservation;
        int count = 0;

        while (file.read(reinterpret_cast<char *>(&reservation), RECORD_SIZE))
        {
            if (strcmp(reservation.sailingId, sailingId.c_str()) == 0)
            {
                count++;
            }
        }

        file.close(); // Close the file after reading
        return count; // Return the total count of reservations for the sailing ID
    }

    else
    {
        cout << "Error opening file for reading." << endl;
    }
};

//************************************************************
// Removes a specific reservation based on sailing ID and license
// in: sailingId - the sailing ID of the reservation to remove
//************************************************************
bool Reservation::removeReservation(const string &sailingId, const string &license, fstream &file) {
    return removeReservation(sailingId, license, file);
}
bool Reservation::removeReservation(const string &sailingId, const string &license, fstream &file) // in: sailingID, license
{

    if (file.is_open())
    {
        file.clear();            // Clear any existing flags
        file.seekg(0, ios::beg); // Move to the beginning of the file

        Reservation reservation;
        bool found = false;

        while (file.read(reinterpret_cast<char *>(&reservation), RECORD_SIZE))
        {
            if (strcmp(reservation.sailingId, sailingId.c_str()) == 0 && strcmp(reservation.license, license.c_str()) == 0)
            {
                found = true; // Reservation found, do not write it to temp file
            }
        }

        file.close();

        return found; // Return true if reservation was found and removed, false otherwise
    }

    else
    {
        cout << "Error opening file for reading." << endl;
    }
};

//************************************************************
// Removes all reservations for a specific sailing ID
// in: sailingId - the sailing ID for which to remove all reservations
//************************************************************
bool Reservation::removeReservationsOnSailing(const std::string &sailingId){
    return removeReservationsOnSailing(sailingId, file);
} 
bool Reservation::removeReservationsOnSailing(const std::string &sailingId, fstream &file) // in: sailingId
{
    if (file.is_open())
    {
        file.clear();            // Clear any existing flags
        file.seekg(0, ios::beg); // Move to the beginning of the file

        Reservation reservation;
        bool found = false;

        while (file.read(reinterpret_cast<char *>(&reservation), RECORD_SIZE))
        {
            if (strcmp(reservation.sailingId, sailingId.c_str()) == 0)
            {
                found = true; // Reservation found, do not write it to temp file
            }
        }

        file.close();

        return found; // Return true if at least one reservation was found and removed, false otherwise
    }

    else
    {
        cout << "Error opening file for reading." << endl;
    }
};

//************************************************************
// Checks if a reservation exists for a specific sailing ID and license
// in: sailingId - the sailing ID to check, license - the license to check
//************************************************************
bool Reservation::checkExist(const string &sailingId, const string &license){
    return checkExist(sailingId, license, file);
} 
bool Reservation::checkExist(const string &sailingId, const string &license, fstream &file) // in: sailingID, license
{
    // Check if a reservation exists for the given sailing ID and license
    if (file.is_open())
    {
        file.clear();            // Clear any existing flags
        file.seekg(0, ios::beg); // Move to the beginning of the file

        Reservation reservation;

        while (file.read(reinterpret_cast<char *>(&reservation), RECORD_SIZE))
        {
            if (strcmp(reservation.sailingId, sailingId.c_str()) == 0 && strcmp(reservation.license, license.c_str()) == 0)
            {
                return true; // Reservation exists
            }
        }

        file.close(); // Close the file after reading
        return false; // Reservation does not exist
    }

    else
    {
        cout << "Error opening file for reading." << endl;
    }
};

//************************************************************
// Writes a new reservation to the file
// in: sailingId - the sailing ID, license - the license of the vehicle
//************************************************************
bool Reservation::writeReservation(const string &sailingId, const string &license) {
    return writeReservation(const string &sailingId, const string &license, fstream &file);
}
bool Reservation::writeReservation(const string &sailingId, const string &license, fstream &file) // in: sailingID, license, phone                                                                                                                                                                                              {
{
    // Write a new reservation to the file
    if (file.is_open())
    {
        Reservation reservation(license, sailingId, false); // Create a new reservation object
        reservation.writeToFile(file);                      // Write the reservation to the file
        return true;                                        // Return true if written successfully
    }
    else
    {
        cout << "Error opening file for writing." << endl;
        return false; // Return false if file could not be opened
    }
};

//************************************************************
// Sets the reservation as checked in
// in: sailingId - the sailing ID, license - the license of the vehicle
//************************************************************
void Reservation::setCheckedIn(const string &sailingId, const string &license) {
    return setCheckedIn(sailingId, license, file);
}
void Reservation::setCheckedIn(const string &sailingId, const string &license, fstream &file) // in: sailingID, license
{
    // Set the reservation as checked in
    if (file.is_open())
    {
        file.clear();            // Clear any existing flags
        file.seekg(0, ios::beg); // Move to the beginning of the file

        Reservation reservation;

        while (file.read(reinterpret_cast<char *>(&reservation), RECORD_SIZE))
        {
            if (strcmp(reservation.sailingId, sailingId.c_str()) == 0 && strcmp(reservation.license, license.c_str()) == 0)
            {
                reservation.onBoard = true;    // Set onBoard status to true
                file.seekp(file.tellg());      // Move back to the position of the current record //// -RECORD_SIZE
                reservation.writeToFile(file); // Write the updated reservation back to the file
                break;                         // Exit loop after updating
            }
        }

        file.close(); // Close the file after writing
    }
    else
    {
        cout << "Error opening file for writing." << endl;
    }
};
