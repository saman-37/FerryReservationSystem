//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// reservation.cpp
//************************************************************
// Purpose: Implements all functionality for the Reservation entity,
// including reading/writing fixed-length binary records, adding,
// deleting, checking, and modifying reservation status. Uses
// unsorted records and random access for simplicity and speed.
//************************************************************
// Version History:
// ver. 1 - July 23, 2025 by Saman and Noble
//************************************************************

/*
This module provides the interface for the reservation file,
functionality to add, delete, and search for reservation records
using binary random access. It encapsulates Reservation record
structure and logic using fixed-length records.
*/

#include "Reservation.h"
#include "Vessel.h"
#include "Util.h"
#include "Sailing.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <sstream>
using namespace std;

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
// in: license, sailingId, onBoard
//************************************************************
Reservation::Reservation(const string &license, const string &sailingId, const bool &onBoard)
{
    strcpy(this->sailingId, sailingId.c_str());
    strcpy(this->license, license.c_str());
    this->sailingId[SAILING_ID_LENGTH] = '\0'; // Null-terminate sailing ID
    this->license[LICENSE_LENGTH] = '\0';      // Null-terminate license
    this->onBoard = onBoard;
}

//************************************************************
// writeToFile()
// Writes this reservation record to a binary file.
// Requires file stream to be open in binary append mode.
//************************************************************
void Reservation::writeToFile(fstream &file) const
{
    cout << "You entered the write reservation method " << endl;
    if (file.is_open())
    {
        cout << "Here I am About To Write !!"   << endl;
        file.write(license, sizeof(license));                                  // Write license string
        file.write(sailingId, sizeof(sailingId));                              // Write sailing ID string
        file.write(reinterpret_cast<const char *>(&onBoard), sizeof(onBoard)); // Write onBoard flag
        file.flush();
        cout << "Reservation created has license: " << license << "\nsailing id: " << sailingId << "\nand on board: " << onBoard << endl;
        // Ensure it’s flushed to disk
    }
    else
    {
        cout << "Error opening file for writing." << endl;
    }
    cout << "this is the write method's read reservation: " << endl;
    cout << "Reservation created has license: " << license << "\nsailing id: " << sailingId << "\nand on board: " << onBoard << endl;
}

//************************************************************
// writeReservation()
// Appends a new reservation to the binary file.
//************************************************************
bool Reservation::writeReservation(const string &sailingId, const string &license)
{
    cout << "Entered the writeReservation:" << endl;

    Reservation reservation(license, sailingId, false); // onBoard = false
    Util::reservationFile.clear();                      // Clear file flags
    Util::reservationFile.seekg(0, ios::end);           // Move to end
    reservation.writeToFile(Util::reservationFile);     // Write vessel
    Util::reservationFile.flush();                      // Save to disk

    reservation.readFromFile(Util::reservationFile);

    return true;
}
//************************************************************
// readFromFile()
// Reads this reservation record from a binary file.
// Requires file stream to be open in binary input mode.
//************************************************************
void Reservation::readFromFile(fstream &file)
{
    if (file.is_open())
    {
        file.read(license, sizeof(license));                            // Read license field
        file.read(sailingId, sizeof(sailingId));                        // Read sailing ID
        file.read(reinterpret_cast<char *>(&onBoard), sizeof(onBoard)); // Read onBoard flag
        cout << "Reservation created has license: " << license << "\nsailing id: " << sailingId << "\nand on board: " << onBoard << endl;
    }
    else
    {
        cout << "Error opening file for reading." << endl;
    }
    cout << "this is the read method's read reservation: " << endl;
    cout << "Reservation created has license: " << license << "\nsailing id: " << sailingId << "\nand on board: " << onBoard << endl;
}

//************************************************************
// toString()
// Converts the reservation record into a displayable string.
//************************************************************
string Reservation::toString() const
{
    stringstream ss;
    ss << "Reservation Details:\n"
       << "Sailing ID: " << sailingId << "\n"
       << "License: " << license << "\n"
       << "On Board: " << (onBoard ? "Yes" : "No") << "\n";
    return ss.str();
}

//************************************************************
// getTotalReservationsOnSailing()
// Returns the number of reservations for a given sailing ID.
//************************************************************
int Reservation::getTotalReservationsOnSailing(const string &sailingId)
{
    if (Util::reservationFile.is_open())
    {
        Util::reservationFile.clear();
        Util::reservationFile.seekg(0, ios::beg); // Start at file beginning

        Reservation reservation;
        int count = 0;

        // Loop through records
        while (Util::reservationFile.read(reinterpret_cast<char *>(&reservation), RECORD_SIZE))
        {
            if (strcmp(reservation.sailingId, sailingId.c_str()) == 0)
            {
                count++; // Match found
            }
        }

        return count;
    }
    else
    {
        cout << "Error opening file for reading." << endl;
    }
}

//************************************************************
// removeReservation()
// Removes a reservation with matching sailingId and license.
//************************************************************

bool Reservation::removeReservation(const string &sailingId, const string &license)
{
    if (Util::reservationFile.is_open())
    {
        Util::reservationFile.clear();
        Util::reservationFile.seekg(0, ios::beg);

        Reservation reservation;
        bool found = false;

        while (Util::reservationFile.read(reinterpret_cast<char *>(&reservation), RECORD_SIZE))
        {
            if (strcmp(reservation.sailingId, sailingId.c_str()) == 0 &&
                strcmp(reservation.license, license.c_str()) == 0)
            {
                found = true;
            }
        }

        return found;
    }
    else
    {
        cout << "Error opening file for reading." << endl;
    }
}

//************************************************************
// removeReservationsOnSailing()
// Removes all reservations that match the given sailing ID.
//************************************************************
bool Reservation::removeReservationsOnSailing(const std::string &sailingId)
{
    if (Util::reservationFile.is_open())
    {
        Util::reservationFile.clear();
        Util::reservationFile.seekg(0, ios::beg);

        Reservation reservation;
        bool found = false;

        while (Util::reservationFile.read(reinterpret_cast<char *>(&reservation), RECORD_SIZE))
        {
            if (strcmp(reservation.sailingId, sailingId.c_str()) == 0)
            {
                found = true;
            }
        }

        return found;
    }
    else
    {
        cout << "Error opening file for reading." << endl;
    }
}

//************************************************************
// checkExist()
// Returns true if a reservation exists for the given sailingId + license.
//************************************************************

bool Reservation::checkExist(const string &sailingId, const string &license)
{
    if (Util::reservationFile.is_open())
    {
        Util::reservationFile.clear();
        Util::reservationFile.seekg(0, ios::beg);

        Reservation reservation;

        while (Util::reservationFile.read(reinterpret_cast<char *>(&reservation), RECORD_SIZE))
        {
            if (strcmp(reservation.sailingId, sailingId.c_str()) == 0 &&
                strcmp(reservation.license, license.c_str()) == 0)
            {
                return true;
            }
        }

        return false;
    }
    else
    {
        cout << "Error opening file for reading." << endl;
        return false;
    }
}

//************************************************************
// setCheckedIn()
// Marks a reservation as checked in and rewrites the record.
//************************************************************
void Reservation::setCheckedIn(const string &sailingId, const string &license)
{
    if (Util::reservationFile.is_open())
    {
        Util::reservationFile.clear();
        Util::reservationFile.seekg(0, ios::beg);

        Reservation reservation;

        while (Util::reservationFile.read(reinterpret_cast<char *>(&reservation), RECORD_SIZE))
        {
            if (strcmp(reservation.sailingId, sailingId.c_str()) == 0 &&
                strcmp(reservation.license, license.c_str()) == 0)
            {
                reservation.onBoard = true;

                // Move back to start of current record
                Util::reservationFile.seekp(Util::reservationFile.tellg());
                reservation.writeToFile(Util::reservationFile);
                break;
            }
        }
    }
    else
    {
        cout << "Error opening file for writing." << endl;
    }
}