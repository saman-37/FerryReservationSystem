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
    strcpy(license, ""); // Initialize license to an empty string
    strcpy(sailingId, ""); // Initialize sailingId to an empty string
    onBoard = false; // Default to not on board
}

//************************************************************
// Parameterized Constructor
// Initializes the reservation with provided values
// in: license, sailingId, onBoard
//************************************************************
Reservation::Reservation(const string &license, const string &sailingId, const bool &onBoard)
{
    strcpy(this->license, license.c_str()); // Copy license string to member variable
    strcpy(this->sailingId, sailingId.c_str()); // Copy sailingId string to member variable
    this->sailingId[SAILING_ID_LENGTH] = '\0'; // Null-terminate sailing ID
    this->license[LICENSE_LENGTH] = '\0'; // Null-terminate license
    this->onBoard = onBoard; // Set onBoard status
}

//************************************************************
// writeToFile()
// Writes this reservation record to a binary file.
// Requires file stream to be open in binary append mode.
//************************************************************
void Reservation::writeToFile(fstream &file) const
{
    // cout << "Entered the writeToFile" << endl;
    if (file.is_open()) // Check if the file is open
    {
        file.write(license, sizeof(license)); // Write license string
        file.write(sailingId, sizeof(sailingId)); // Write sailing ID string
        file.write(reinterpret_cast<const char *>(&onBoard), sizeof(onBoard)); // Write onBoard flag
        file.flush(); // Ensure it’s flushed to disk
    }
    else
    {
        cout << "Error opening file for writing." << endl; // Error message if file is not open
    }
}

//************************************************************
// writeReservation()
// Appends a new reservation to the binary file.
//************************************************************
bool Reservation::writeReservation(const string &license, const string &sailingId)
{
    Reservation reservation(license, sailingId, false); // Create a new reservation with onBoard = false
    Util::reservationFile.clear(); // Clear file flags
    Util::reservationFile.seekg(0, ios::end); // Move to end of the file
    reservation.writeToFile(Util::reservationFile); // Write the reservation to the file
    Util::reservationFile.flush(); // Save to disk

    reservation.readFromFile(Util::reservationFile); // Read back the reservation (not typically needed)

    return true; // Return true indicating success
}

//************************************************************
// readFromFile()
// Reads this reservation record from a binary file.
// Requires file stream to be open in binary input mode.
//************************************************************
bool Reservation::readFromFile(fstream &file)
{
    if (file.is_open()) // Check if the file is open
    {
        file.read(license, sizeof(license)); // Read license field
        file.read(sailingId, sizeof(sailingId)); // Read sailing ID
        file.read(reinterpret_cast<char *>(&onBoard), sizeof(onBoard)); // Read onBoard flag
        return true; // Return true if read was successful
    }
    else
    {
        cout << "Error opening file for reading." << endl; // Error message if file is not open
        return false; // Return false indicating failure
    }
}

//************************************************************
// checkExist()
// Returns true if a reservation exists for the given sailingId + license.
//************************************************************
bool Reservation::checkExist(const string &license, const string &sailingId)
{
    if (!Util::reservationFile.is_open()) // Check if the reservation file is open
    {
        std::cerr << "Reservation file not open." << std::endl;
        return false; // Return false if file is not open
    }

    Util::reservationFile.clear(); // Reset flags
    Util::reservationFile.seekg(0, ios::beg); // Go to start of the file

    Reservation reservation; // Create a Reservation instance to read records

    // Loop while there is data to read
    while (!Util::reservationFile.eof())
    {
        reservation.readFromFile(Util::reservationFile); // Read a reservation record

        // Compare the primary key (here it is a composite key of license and sailingId)
        if (strncmp(reservation.license, license.c_str(), LICENSE_LENGTH) == 0 &&
            strncmp(reservation.sailingId, sailingId.c_str(), SAILING_ID_LENGTH) == 0)
        {
            return true; // Return true if a matching reservation is found
        }
    }

    return false; // Return false if no matching reservation is found
}

//************************************************************
// toString()
// Converts the reservation record into a displayable string.
//************************************************************
string Reservation::toString() const
{
    stringstream ss; // Create a string stream for formatting
    ss << "Reservation: " << license << ", " << sailingId << ", onBoard: " << (onBoard ? "Yes" : "No") << endl; // Format the string
    return ss.str(); // Return the formatted string
}

//************************************************************
// getTotalReservationsOnSailing()
// Returns the number of reservations for a given sailing ID.
//************************************************************
int Reservation::getTotalReservationsOnSailing(const string &sailingId)
{
    if (!Util::reservationFile.is_open()) // Check if the reservation file is open
    {
        cout << "Error opening Reservation File!" << endl;
        return -1; // Return -1 to indicate an error
    }

    Util::reservationFile.clear(); // Clear any error flags
    Util::reservationFile.seekg(0, ios::beg); // Start at file beginning

    Reservation reservation; // Create a Reservation instance to read records
    int count = 0; // Initialize count of reservations

    // Loop through records until the end of the file
    while (Util::reservationFile.peek() != EOF) // Check for end of file
    {
        reservation.readFromFile(Util::reservationFile); // Read a reservation record

        if (strcmp(reservation.sailingId, sailingId.c_str()) == 0) // Check if the sailingId matches
        {
            count++; // Increment count for each matching reservation
        }
    }

    return count; // Return the total count of reservations for the sailing ID
}

//************************************************************
// removeReservation()
// Removes a reservation with matching sailingId and license.
//************************************************************
bool Reservation::removeReservation(const string &license, const string &sailingId)
{
    Reservation reservation; // Create a Reservation instance to read records

    if (!Util::reservationFile.is_open()) // Check if the reservation file is open
    {
        cout << "Reservation File is not open." << endl;
        return false; // Return false if file is not open
    }

    Util::reservationFile.clear(); // Clear any error flags
    Util::reservationFile.seekg(0, ios::beg); // Move read pointer to beginning

    streampos currentPos; // Variable to store current position in the file
    streampos matchPos = -1; // Variable to store position of matching record

    // Step 1: Find Matching record
    while (!Util::reservationFile.eof()) // Loop until end of file
    {
        reservation.readFromFile(Util::reservationFile); // Read a reservation record
        currentPos = Util::reservationFile.tellg() - static_cast<streamoff>(RECORD_SIZE); // Get current position

        // Check if the current record matches the given license and sailingId
        if (strcmp(reservation.license, license.c_str()) == 0 &&
            strcmp(reservation.sailingId, sailingId.c_str()) == 0)
        {
            matchPos = currentPos; // Store position of matching record
            break; // Exit loop if match is found
        }
    }
    if (matchPos == -1) // Check if no match was found
    {
        cout << "Reservation not found." << endl;
        return false; // Return false if no matching reservation is found
    }

    // Step 2: Determine last record position
    Util::reservationFile.clear(); // Clear any error flags
    Util::reservationFile.seekg(0, ios::end); // Move to end of the file
    streamoff fileSize = Util::reservationFile.tellg(); // Get total file size
    streamoff lastRecordPos = fileSize - RECORD_SIZE; // Calculate position of the last record

    if (matchPos == lastRecordPos) // Check if the matched record is the last one
    {
        Util::reservationFile.close(); // Close the file
        Util::truncate("reservation.dat", lastRecordPos); // Truncate the file to remove the last record
        Util::reservationFile.open("reservation.dat", ios::in | ios::out | ios::binary); // Reopen the file
        return true; // Return true indicating success
    }

    // Step 3: Read last record
    Reservation lastRecord; // Create a Reservation instance for the last record
    Util::reservationFile.clear(); // Clear any error flags
    Util::reservationFile.seekg(lastRecordPos, ios::beg); // Move to the last record's position
    Util::reservationFile.read(reinterpret_cast<char *>(&lastRecord), RECORD_SIZE); // Read last record data

    // Step 4: Overwrite matched record with last record
    Util::reservationFile.clear(); // Clear any error flags
    Util::reservationFile.seekp(matchPos, ios::beg); // Move to the position of the matched record
    Util::reservationFile.write(reinterpret_cast<const char *>(&lastRecord), RECORD_SIZE); // Write last record data to matched position

    // Step 5: Truncate the file
    Util::reservationFile.close(); // Close the file
    Util::truncate("reservation.dat", fileSize - RECORD_SIZE); // Truncate the file to remove the last record
    Util::reservationFile.open("reservation.dat", ios::in | ios::out | ios::binary); // Reopen the file

    return true; // Return true indicating success
}

//************************************************************
// removeReservationsOnSailing()
// Removes all reservations that match the given sailing ID.
//************************************************************

// TEST ABOVE FIRST, THIS WITH 1-1 LOOP AT FRONT & END LATER, OTHERWISE TOO MANY PRINTS
bool Reservation::removeReservationsOnSailing(const std::string &sailingId)
{
    if (!Util::reservationFile.is_open()) // Check if the reservation file is open
    {
        cout << "Reservation File is not open." << endl;
        return false; // Return false if file is not open
    }

    Reservation reservation; // Create a Reservation instance to read records
    bool foundAMatchingReservation = false; // Flag to indicate if a matching reservation is found

    Util::reservationFile.clear(); // Clear any error flags
    Util::reservationFile.seekg(0, ios::beg); // Move read pointer to beginning

    // Read the records until the end of the file
    while (!Util::reservationFile.eof()) // Loop until end of file
    {
        reservation.readFromFile(Util::reservationFile); // Read a reservation record

        if (strcmp(reservation.sailingId, sailingId.c_str()) == 0) // Check if the sailingId matches
        {
            foundAMatchingReservation = true; // Found at least one matching reservation

            // Extract the license number of the reservation record
            string license(reservation.license); // Create a string from the license

            removeReservation(license, sailingId); // Call removeReservation using both parameters
        }
    }

    if (!foundAMatchingReservation) // Check if no matching reservations were found
    {
        cout << "No reservations found for this sailing ID: " << sailingId << "\n Hence, no reservations deletions happened." << endl;
    }

    return true; // Return true indicating the operation was completed
}

//************************************************************
// setCheckedIn()
// Marks a reservation as checked in and update the checked-in value in the binary file record.
//************************************************************
void Reservation::setCheckedIn(const string &license)
{
    if (!Util::reservationFile.is_open()) // Check if the reservation file is open
    {
        cout << "Error opening Reservation File!" << endl;
        return; // Exit if file is not open
    }
    Util::reservationFile.clear(); // Clear any error flags
    Util::reservationFile.seekg(0, ios::beg); // Move read pointer to beginning

    Reservation reservation; // Create a Reservation instance to read records

    while (reservation.readFromFile(Util::reservationFile)) // Loop through records
    {
        streampos recordStartPos = Util::reservationFile.tellg() - static_cast<streamoff>(RECORD_SIZE); // Get start position of the current record

        if (strcmp(reservation.license, license.c_str()) == 0) // Check if the license matches
        {
            reservation.onBoard = true; // Mark the reservation as checked in
            cout << "The fare for your vehicle is : $" << calculateFare(license) << endl; // Output fare for the vehicle

            // Update the record in the file
            // Move back to start of current record
            Util::reservationFile.seekp(recordStartPos); // Move write pointer to the start of the current record
            reservation.writeToFile(Util::reservationFile); // Write updated reservation data
            return; // Exit after updating
        }
    }

    cout << "Reservation with license " << license << " not found." << endl; // Error message if reservation not found
}

//$14 for normal vehicles under 2m high and 7m long
// For long low special vehicles $2 * length in meters; For long overheight vehicles $3 * length in meters
float Reservation::calculateFare(const string &license)
{
    Vehicle vehicle; // Create a Vehicle instance to fetch details
    float height = vehicle.getHeight(license); // Get height of the vehicle
    float length = vehicle.getLength(license); // Get length of the vehicle

    if (height <= REGULAR_VEHICLE_HEIGHT && length <= REGULAR_VEHICLE_LENGTH)
    {
        return REGULAR_VEHICLE_FARE; // Normal vehicle fare
    }
    else if (length > REGULAR_VEHICLE_LENGTH && height <= REGULAR_VEHICLE_HEIGHT)
    { // Long-low special vehicle
        return 2.0 * length; // Long overheight vehicle fare
    }
    else if (length > REGULAR_VEHICLE_LENGTH && height > REGULAR_VEHICLE_HEIGHT)
    { // Long-overheight special vehicle
        return 3.0 * length; // Long overheight vehicle fare
    }
    else if (length > REGULAR_VEHICLE_LENGTH && height > REGULAR_VEHICLE_HEIGHT 
            && length > REGULAR_VEHICLE_LENGTH && height <= REGULAR_VEHICLE_HEIGHT) 
    {
        return (3.0 * length) + (2.0 * length); // Combined fare for both conditions
    }
    return 0.0; // Return 0 for invalid vehicle dimensions
}