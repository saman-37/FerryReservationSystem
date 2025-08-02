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
    // this->sailingId[SAILING_ID_LENGTH] = '\0'; // Null-terminate sailing ID
    // this->license[LICENSE_LENGTH] = '\0';      // Null-terminate license
    this->onBoard = onBoard;
}

//************************************************************
// writeToFile()
// Writes this reservation record to a binary file.
// Requires file stream to be open in binary append mode.
//************************************************************
void Reservation::writeToFile(fstream &file) const
{
    //cout << "Entered the writeToFile" << endl;
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
    //cout << "Reservation JUST wrote has license " << license << ", sailing ID " << sailingId << ", onBoard status: " << (onBoard ? "Yes" : "No") << endl;
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
        file.read(license, sizeof(license)); // Read license field
        // license[sizeof(license) - 1] = '\0';
        file.read(sailingId, sizeof(sailingId)); // Read sailing ID
        // sailingId[sizeof(sailingId) - 1] = '\0';
        file.read(reinterpret_cast<char *>(&onBoard), sizeof(onBoard)); // Read onBoard flag
        return true;
    }
    else
    {
        cout << "Error opening file for reading." << endl;
        return false;
    }

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
    ss << "Reservation:" << "License:[" << license << "], Sailing ID:[" << sailingId << "], on Board: " << (onBoard ? "Yes" : "No") << "\n";
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
    
    // Loop through records
    while (reservation.readFromFile(Util::reservationFile))
    {
        reservation.readFromFile(Util::reservationFile);
        
        if (strcmp(reservation.sailingId, sailingId.c_str()) == 0)
        {
            count++; // Match found
            cout << "Found " << count << " reservation(s) SO FAR with given sailing id: " << sailingId << endl;
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
    cout << "Entered the removeReservation." << endl;
    // For Debugging
    // cout << "The CONTENTS before deleting reservation are: " << endl;
    
    if (!Util::reservationFile.is_open()) {
        cout << "Reservation File is not open." << endl;
        return false;
    }
    
    Reservation reservation;
    Util::reservationFile.clear();
    Util::reservationFile.seekg(0, ios::beg); // move read pointer to beginning

    streampos currentPos;
    streampos matchPos = -1;
    
    //Step1. Find Matching record
    while (reservation.readFromFile(Util::reservationFile))
    {
        streampos currentPos = Util::reservationFile.tellg() - static_cast<streamoff>(RECORD_SIZE);

        if (strcmp(reservation.license, license.c_str()) == 0 &&
        strcmp(reservation.sailingId, sailingId.c_str()) == 0)
        {
            matchPos = currentPos;
            break;
        }
    }
    if (matchPos == -1) 
    {
        cout<< "Reservation not found." << endl;
        return false;
    }

    //Step2. Determine last record position
    Util::reservationFile.clear();
    Util::reservationFile.seekg(0, ios::end);
    streamoff fileSize = Util::reservationFile.tellg();
    streamoff lastRecordPos = fileSize - RECORD_SIZE;

    if (matchPos == lastRecordPos)
    {
        Util::reservationFile.close();
        Util::truncate("reservation.dat", lastRecordPos);
        Util::reservationFile.open("reservation.dat", ios::in | ios::out | ios::binary);
        return true;
    }

    //3. Read last record
    Reservation lastRecord;
    Util::reservationFile.seekg(lastRecordPos, ios::beg);
    Util::reservationFile.read(reinterpret_cast<char *>(&lastRecord), RECORD_SIZE);


    //4. Overwrite matched record with last record
    Util::reservationFile.seekp(matchPos, ios::beg);
    Util::reservationFile.write(reinterpret_cast<const char *>(&lastRecord), RECORD_SIZE);


    //5. Truncate the file
    Util::reservationFile.close();
    Util::truncate("reservation.dat", fileSize - RECORD_SIZE);
    Util::reservationFile.open("reservation.dat", ios::in | ios::out | ios::binary);

    return true;

    // cout << "The CONTENTS after deleting reservation are: " << endl;
    
    while (!Util::reservationFile.eof())
    {
        reservation.readFromFile(Util::reservationFile);
    }
    return false;
}

//************************************************************
// removeReservationsOnSailing()
// Removes all reservations that match the given sailing ID.
//************************************************************

// TEST ABOVE FIRST, THIS WITH 1-1 LOOP AT FRONT & END LATER, OTHERWISE TOO MANY PRINTS
bool Reservation::removeReservationsOnSailing(const std::string &sailingId)
{
    
    if (!Util::reservationFile.is_open()) {
        cout << "Reservation File is not open." << endl;
        return false;
    }
    
    vector<Reservation> keptReservations;
    Reservation reservation;
    bool foundMatch = false;

    Util::reservationFile.clear();
    Util::reservationFile.seekg(0, ios::beg); // move read pointer to beginning

    //Read all reservations and keep only the ones that don't match
    while (reservation.readFromFile(Util::reservationFile))
    {

        if (strcmp(reservation.sailingId, sailingId.c_str()) != 0)
        {
            //push the matching reservations on the vector
            keptReservations.push_back(reservation);
        }
        else
        {
            foundMatch = true;
        }
    }

    //close the reservationFile to truncate changes
    Util::reservationFile.close();

    if(!foundMatch) 
    {
        cout << "No reservations found for sailing ID: " << sailingId << endl;
        return false;
    }

    //open a different file to write the reservations that matched 
    ofstream outFile("reservation.dat", ios::out | ios::binary | ios::trunc);
    for ( const Reservation &r : keptReservations) 
    {
        outFile.write(reinterpret_cast<const char *> (&r), RECORD_SIZE);
    }
    outFile.close();

    //reopen the reservationFile with only the reservations not matching the sailing Id
    Util::reservationFile.open("reservation.dat", ios::in | ios::out | ios::binary);
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
            // does this update in the file ? No, it just updates the object
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

    if (height <= 2.0 && length <= 7.0)
    {
        return 14.0; // Normal vehicle fare
    }
    else if (length > 7.0 && height <= 2.0)
    {                        // long-low special vehicle
        return 2.0 * length; // Long overheight vehicle fare
    }
    else if (length > 7.0 && height > 2.0)
    {                        // long-overheight special vehicle
        return 3.0 * length; // Long overheight vehicle fare
    }
    return 0.0; // Invalid vehicle dimensions
}