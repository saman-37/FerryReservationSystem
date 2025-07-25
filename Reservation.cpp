//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// reservation.cpp
// July 10, 2025 Revision 1
// Introductory comment which adds to already provided comment in .h file,describe any overall design issues internal to this module (like data structure (if there are any) and algorithm (e.g. linear search of file
/*
Purpose: Provides the interface for the reservation file, functionality to add, delete, look for reservation records, using binary random access
*/
//************************************************************
#include "Reservation.h"

#include "util.h"
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
// in: sailing_id, license, on_board
Reservation::Reservation(const string &license, const string &sailingId, const bool &onBoard) // in: sailingID, license, phone
{
    strcpy(this->sailingId, sailingId.c_str());
    strcpy(this->license, license.c_str());
    this->onBoard = onBoard; // Default to not on board
};

void Reservation::writeToFile(fstream &file) const // in-out: file - binary file stream
{

    if (file.is_open())
    {
        file.write(license, LICENSE_LENGTH + 1);                               // Write license
        file.write(sailingId, SAILING_ID_LENGTH + 1);                          // Write sailing ID
        file.write(reinterpret_cast<const char *>(&onBoard), sizeof(onBoard)); // Write onBoard status; we need reinterpret cast as the type should be character memory address
        file.flush();                                                          // Ensure data is written to disk
        file.close();                                                          // Close the file after writing
    }

    else
    {
        cout << "Error opening file for writing." << endl;
    }
};

void Reservation::readFromFile(fstream &file) // in-out: file - binary file stream
{
    if (file.is_open())
    {
        file.read(license, LICENSE_LENGTH + 1);                         // Read license
        file.read(sailingId, SAILING_ID_LENGTH + 1);                    // Read sailing ID
        file.read(reinterpret_cast<char *>(&onBoard), sizeof(onBoard)); // Read onBoard status
    }
    else
    {
        cout << "Error opening file for reading." << endl;
    }
};

string Reservation::toString() const // out: returns formatted string
{
    stringstream ss;
    ss << "Reservation Details:\n"
       << "Sailing ID: " << sailingId << "\n"
       << "License: " << license << "\n"
       << "On Board: " << (onBoard ? "Yes" : "No") << "\n";
    return ss.str();
};

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

bool Reservation::removeReservation(const string &sailingId, const string &license, fstream &file) // in: sailingID, license
{
    // shorten the reservation file by 1 reservation, i.e. removing the record with the given sailingId and license
    /*
    - close the file remembering where the end of the last record is.
    - open it using the C function called fopen( ) from <io.h> to get a handle.
    - use chsize( ) in any way that you want.
    - close the file using fclose( )
    - reopen it using your <fstream> calls.
    */
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

bool Reservation::removeReservationsOnSailing(const std::string &sailingId, fstream &file) // in: sailingId
{
    // Remove all reservations for a specific sailing ID
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
