//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// reservation.cpp
//************************************************************
// Purpose: Implements all functionality for the Reservation entity,
// including reading/writing fixed-length binary records, adding,
// deleting, checking, and modifying reservation status. Uses
// unsorted records and random access for simplicity and speed.
//************************************************************
// Version History:
// ver. 2 - July 23, 2025 by Saman and Noble
//************************************************************

/*
This module provides the interface for the reservation file,
functionality to add, delete, and search for reservation records
using binary random access. It encapsulates Reservation record
structure and logic using fixed-length records.
*/

#include "Reservation.h"
#include "Vessel.h"
#include "Vehicle.h"
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
    strcpy(license, "");
    strcpy(sailingId, "");
    onBoard = false; // Default to not on board
}

//************************************************************
// Parameterized Constructor
// Initializes the reservation with provided values
// in: license, sailingId, onBoard
//************************************************************
Reservation::Reservation(const string &license, const string &sailingId, const bool &onBoard)
{
    strcpy(this->license, license.c_str());
    strcpy(this->sailingId, sailingId.c_str());
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
    // cout << "Entered the writeToFile" << endl;
    if (file.is_open())
    {
        cout << "Here I am About To Write !!" << endl;
        file.write(license, sizeof(license));                                  // Write license string
        file.write(sailingId, sizeof(sailingId));                              // Write sailing ID string
        file.write(reinterpret_cast<const char *>(&onBoard), sizeof(onBoard)); // Write onBoard flag
        file.flush();
        // Ensure it’s flushed to disk
    }
    else
    {
        cout << "Error opening file for writing." << endl;
    }
    // cout << "Reservation JUST wrote has license " << license << ", sailing ID " << sailingId << ", onBoard status: " << (onBoard ? "Yes" : "No") << endl;
}

//************************************************************
// writeReservation()
// Appends a new reservation to the binary file.
//************************************************************
bool Reservation::writeReservation(const string &license, const string &sailingId)
{
    cout << "Entered the writeReservation" << endl;
    // const string &license, const string &phone, float height, float length
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
bool Reservation::readFromFile(fstream &file)
{
    // cout << "\nEntered the readFromFile in reservation" << endl;

    if (file.is_open())
    {
        file.read(license, sizeof(license));                            // Read license field
        file.read(sailingId, sizeof(sailingId));                        // Read sailing ID
        file.read(reinterpret_cast<char *>(&onBoard), sizeof(onBoard)); // Read onBoard flag
        // cout << "Reservation: " << license << ", " << sailingId << ", onBoard: " << (onBoard ? "Yes" : "No") << endl;
        return true;
    }
    else
    {
        cout << "Error opening file for reading." << endl;
        return false;
    }

    // Printing out:
    // toString();
    // cout << "Reservation JUST read has license: " << license << ", sailing ID: " << sailingId << ", onBoard status: " << (onBoard ? "Yes" : "No") << endl;
}

//************************************************************
// checkExist()
// Returns true if a reservation exists for the given sailingId + license.
//************************************************************
bool Reservation::checkExist(const string &license, const string &sailingId)
{
    if (!Util::reservationFile.is_open())
    {
        std::cerr << "Reservation file not open." << std::endl;
        return false;
    }

    Util::reservationFile.clear();            // Reset flags
    Util::reservationFile.seekg(0, ios::beg); // Go to start

    Reservation reservation;

    // Loop while there is data to read
    while (!Util::reservationFile.eof())
    {
        reservation.readFromFile(Util::reservationFile);

        // compare the primary key (here it is a composite key of license and sailingId)
        if (strncmp(reservation.license, license.c_str(), LICENSE_LENGTH) == 0 &&
            strncmp(reservation.sailingId, sailingId.c_str(), SAILING_ID_LENGTH) == 0)
        {
            return true;
        }
    }

    return false;
}

//************************************************************
// toString()
// Converts the reservation record into a displayable string.
//************************************************************
string Reservation::toString() const
{
    stringstream ss;
    ss << "Reservation: " << license << ", " << sailingId << ", onBoard: " << (onBoard ? "Yes" : "No") << endl;
    return ss.str();
}

//************************************************************
// getTotalReservationsOnSailing()
// Returns the number of reservations for a given sailing ID.
//************************************************************
int Reservation::getTotalReservationsOnSailing(const string &sailingId)
{

    if (!Util::reservationFile.is_open())
    {
        cout << "Error opening Reservation File!" << endl;
        return -1;
    }

    Util::reservationFile.clear();
    Util::reservationFile.seekg(0, ios::beg); // Start at file beginning

    Reservation reservation;
    int count = 0;

    // Loop through records until the end of the file
    while (Util::reservationFile.peek() != EOF)
    {
        reservation.readFromFile(Util::reservationFile);

        if (strcmp(reservation.sailingId, sailingId.c_str()) == 0) // the sailingId of the record just read if matches with the given sailingId
        {
            count++;
        }
    }

    return count;
}

//************************************************************
// removeReservation()
// Removes a reservation with matching sailingId and license.
//************************************************************

bool Reservation::removeReservation(const string &license, const string &sailingId)
{
    Reservation reservation;

    //----------------------------------------------------------------------------------------------------------
    cout << "Entered the removeReservation." << endl;
    cout << "The CONTENTS before deleting reservation are: " << endl;

    Util::reservationFile.clear();
    Util::reservationFile.seekg(0, ios::beg); // move read pointer to beginning

    while (Util::reservationFile.peek() != EOF)
    {
        reservation.readFromFile(Util::reservationFile);
        cout << reservation.toString(); // WEIRDLY THIS WASNT WORKING , IT SHOULD BE AN EASY WAY TO DEBUG AND PRINT
    }
    //----------------------------------------------------------------------------------------------------------

    if (!Util::reservationFile.is_open())
    {
        cout << "Reservation File is not open." << endl;
        return false;
    }

    Util::reservationFile.clear();
    Util::reservationFile.seekg(0, ios::beg); // move read pointer to beginning

    streampos currentPos;
    streampos matchPos = -1;

    // Step1. Find Matching record
    while (!Util::reservationFile.eof())
    {
        reservation.readFromFile(Util::reservationFile);                                  // reading one record at a time
        currentPos = Util::reservationFile.tellg() - static_cast<streamoff>(RECORD_SIZE); //  currentPos = Util::reservationFile.tellg() - static_cast<streamoff>(RECORD_SIZE);

        if (strcmp(reservation.license, license.c_str()) == 0 &&
            strcmp(reservation.sailingId, sailingId.c_str()) == 0)
        {
            matchPos = currentPos;
            break;
        }
    }
    if (matchPos == -1)
    {
        cout << "Reservation not found." << endl;
        return false;
    }

    // Step2. Determine last record position
    Util::reservationFile.clear();
    Util::reservationFile.seekg(0, ios::end);
    streamoff fileSize = Util::reservationFile.tellg(); // since at end, tellg will tell the whole file size; total file size in bytes
    streamoff lastRecordPos = fileSize - RECORD_SIZE;

    if (matchPos == lastRecordPos)
    {
        Util::reservationFile.close();
        Util::truncate("reservation.dat", lastRecordPos);
        Util::reservationFile.open("reservation.dat", ios::in | ios::out | ios::binary);
        return true;
    }

    // 3. Read last record
    Reservation lastRecord;
    Util::reservationFile.clear();
    Util::reservationFile.seekg(lastRecordPos, ios::beg);                           // move the read pointer to last record's front
    Util::reservationFile.read(reinterpret_cast<char *>(&lastRecord), RECORD_SIZE); // read data into lastRecord

    // 4. Overwrite matched record with last record
    Util::reservationFile.clear();
    Util::reservationFile.seekp(matchPos, ios::beg);
    Util::reservationFile.write(reinterpret_cast<const char *>(&lastRecord), RECORD_SIZE);

    // 5. Truncate the file
    Util::reservationFile.close();
    Util::truncate("reservation.dat", fileSize - RECORD_SIZE);
    Util::reservationFile.open("reservation.dat", ios::in | ios::out | ios::binary);

    return true;
}

//************************************************************
// removeReservationsOnSailing()
// Removes all reservations that match the given sailing ID.
//************************************************************

// TEST ABOVE FIRST, THIS WITH 1-1 LOOP AT FRONT & END LATER, OTHERWISE TOO MANY PRINTS
bool Reservation::removeReservationsOnSailing(const std::string &sailingId)
{
    //----------------------------------------------------------------------------------------------------------
    cout << "Entered the removeReservationsOnSailing." << endl;
    Util::reservationFile.seekg(0, ios::end); // move read pointer to beginning
    int totalReservations = Util::reservationFile.tellg() / RECORD_SIZE;
    cout << "Total reservations in system are: " << totalReservations << endl;
    cout << "Total reservations with given sailing id are:" << getTotalReservationsOnSailing(sailingId) << endl;
    //----------------------------------------------------------------------------------------------------------

    if (!Util::reservationFile.is_open())
    {
        cout << "Reservation File is not open." << endl;
        return false;
    }

    Reservation reservation;
    bool foundAMatchingReservation = false;

    Util::reservationFile.clear();
    Util::reservationFile.seekg(0, ios::beg); // move read pointer to beginning

    // read the records until the end of the file
    while (!Util::reservationFile.eof())
    {
        reservation.readFromFile(Util::reservationFile); // reading one record at a time

        if (strcmp(reservation.sailingId, sailingId.c_str()) == 0)
        {
            foundAMatchingReservation = true; // Found at least one matching reservation

            // extract the license no of the reservation record
            string license(reservation.license);

            removeReservation(license, sailingId); // call removeReservation using both the parameters
        }
    }

    if (!foundAMatchingReservation)
    {
        cout << "No reservations found for this sailing ID: " << sailingId << "\n Hence, no reservations deletions happened." << endl;
    }

    return true;
}

//************************************************************
// setCheckedIn()
// Marks a reservation as checked in and update the checked-in value in the binary file record.
//************************************************************
void Reservation::setCheckedIn(const string &license)
{
    if (!Util::reservationFile.is_open())
    {
        cout << "Error opening Reservation File!" << endl;
        return;
    }
    Util::reservationFile.clear();
    Util::reservationFile.seekg(0, ios::beg);

    Reservation reservation;

    while (reservation.readFromFile(Util::reservationFile))
    {
        streampos recordStartPos = Util::reservationFile.tellg() - static_cast<streamoff>(RECORD_SIZE);

        if (strcmp(reservation.license, license.c_str()) == 0)
        {
            reservation.onBoard = true;
            cout << "The fare for your vehicle is : $" << calculateFare(license) << endl;

            // also updating the record in the file
            // VISIT THE RECORD, seek at "license +sailing id " skipped record position and put true there in place of false
            // Move back to start of current record
            Util::reservationFile.seekp(recordStartPos);
            reservation.writeToFile(Util::reservationFile);
            return;
        }
    }

    cout << "Reservation with license " << license << " not found." << endl;
}

//$14 for normal vehicles under 2m high and 7m long
// For long low special vehicles $2 *length in meters; For long overheight vehicles $3 * length in meters
float Reservation::calculateFare(const string &license)
{
    Vehicle vehicle;
    float height = vehicle.getHeight(license);
    float length = vehicle.getLength(license);

    if (height <= REGULAR_VEHICLE_HEIGHT && length <= REGULAR_VEHICLE_LENGTH)
    {
        return REGULAR_VEHICLE_FARE; // Normal vehicle fare
    }
    else if (length > REGULAR_VEHICLE_LENGTH && height <= REGULAR_VEHICLE_HEIGHT)
    {                        // long-low special vehicle
        return 2.0 * length; // Long overheight vehicle fare
    }
    else if (length > REGULAR_VEHICLE_LENGTH && height > REGULAR_VEHICLE_HEIGHT)
    {                        // long-overheight special vehicle
        return 3.0 * length; // Long overheight vehicle fare
    }
    else if (length > REGULAR_VEHICLE_LENGTH && height > REGULAR_VEHICLE_HEIGHT 
            && length > REGULAR_VEHICLE_LENGTH && height <= REGULAR_VEHICLE_HEIGHT) 
    {
        return (3.0 * length) + (2.0 * length);
    }
    return 0.0; // Invalid vehicle dimensions
}