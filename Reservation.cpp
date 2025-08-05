//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*********************************************************
// reservation.cpp
//**********************************************************
// Purpose: Implements all functionality for the Reservation 
// entity, including reading/writing fixed-length binary 
// records, adding, deleting, checking, and modifying 
// reservation status. Uses unsorted records and random access
// for simplicity and speed.
//**********************************************************
// Version History:
// ver. 2 - July 23, 2025 by Saman and Noble
//**********************************************************

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

//**********************************************************
// Default Constructor
// Initializes the reservation with default values
//**********************************************************
Reservation::Reservation()
{
    strcpy(license, "");
    strcpy(sailingId, "");
    onBoard = false; // Default to not on board
}

//**********************************************************
// Parameterized Constructor
// Initializes the reservation with provided values
// in: license, sailingId, onBoard
//**********************************************************
Reservation::Reservation(const string &license, 
                const string &sailingId, const bool &onBoard)
{
    strcpy(this->license, license.c_str()); 
    strcpy(this->sailingId, sailingId.c_str());
    this->sailingId[SAILING_ID_LENGTH] = '\0'; 
    this->license[LICENSE_LENGTH] = '\0'; 
    this->onBoard = onBoard; // Set onBoard status
}

//**********************************************************
// writeToFile()
// Writes this reservation record to a binary file.
// Requires file stream to be open in binary append mode.
//**********************************************************
void Reservation::writeToFile(fstream &file) const
{
    // cout << "Entered the writeToFile" << endl;
    if (file.is_open()) // Check if the file is open
    {
        file.write(license, sizeof(license)); 
        file.write(sailingId, sizeof(sailingId)); 
        file.write(reinterpret_cast<const char *>(&onBoard),
                     sizeof(onBoard)); // Write onBoard flag
        file.flush(); // Ensure it’s flushed to disk
    }
    else
    {
        // Error message if file is not open
        cout << "Error opening file for writing." << endl; 
    }
}

//**********************************************************
// writeReservation()
// Appends a new reservation to the binary file.
//**********************************************************
bool Reservation::writeReservation(const string &license, 
                                const string &sailingId)
{
    // Create a new reservation with onBoard = false
    Reservation reservation(license, sailingId, false); 
    Util::reservationFile.clear(); // Clear file flags
    // Move to end of the file
    Util::reservationFile.seekg(0, ios::end); 
    // Write the reservation to the file
    reservation.writeToFile(Util::reservationFile); 
    Util::reservationFile.flush(); // Save to disk

    return true; // Return true indicating success
}

//**********************************************************
// readFromFile()
// Reads this reservation record from a binary file.
// Requires file stream to be open in binary input mode.
//**********************************************************
bool Reservation::readFromFile(fstream &file)
{
    if (file.is_open()) // Check if the file is open
    {
        file.read(license, sizeof(license)); 
        file.read(sailingId, sizeof(sailingId)); 
        file.read(reinterpret_cast<char *>(&onBoard), 
                        sizeof(onBoard)); 
        return true; // Return true if read was successful
    }
    else
    {
        // Error message if file is not open
        cout << "Error opening file for reading." << endl; 
        return false; // Return false indicating failure
    }
}

//**********************************************************
// checkExist()
// Returns true if a reservation exists for the given
// sailingId + license.
//**********************************************************
bool Reservation::checkExist(const string &license, 
                            const string &sailingId)
{
    // Check if the reservation file is open
    if (!Util::reservationFile.is_open()) 
    {
        std::cerr << "Reservation file not open." 
                    << std::endl;
        return false; // Return false if file is not open
    }

    Util::reservationFile.clear(); // Reset flags
    // Go to start of the file
    Util::reservationFile.seekg(0, ios::beg); 

    // Create a Reservation instance to read records
    Reservation reservation; 

    // Loop while there is data to read
    while (!Util::reservationFile.eof())
    {
        // Read a reservation record
        reservation.readFromFile(Util::reservationFile); 

        // Compare the primary key (here it is a composite 
        // key of license and sailingId)
        if (strncmp(reservation.license, license.c_str(),
            LICENSE_LENGTH) == 0 && 
            strncmp(reservation.sailingId, 
            sailingId.c_str(), SAILING_ID_LENGTH) == 0)
        {
            // Return true if a matching reservation is found
            return true; 
        }
    }

    // Return false if no matching reservation is found
    return false; 
}

//**********************************************************
// toString()
// Converts the reservation record into a displayable string.
//**********************************************************
string Reservation::toString() const
{
    stringstream ss; // Create a string stream for formatting
    ss << "Reservation: " << license << ", " << sailingId 
    << ", onBoard: " << (onBoard ? "Yes" : "No") << endl; 
    return ss.str(); // Return the formatted string
}

//**********************************************************
// getTotalReservationsOnSailing()
// Returns the number of reservations for a given sailing ID.
//**********************************************************
int Reservation::getTotalReservationsOnSailing(
                    const string &sailingId)
{
    // Check if the reservation file is open
    if (!Util::reservationFile.is_open()) 
    {
        cout << "Error opening Reservation File!" << endl;
        return -1; // Return -1 to indicate an error
    }

    Util::reservationFile.clear(); // Clear any error flags
    
    // Start at file beginning
    Util::reservationFile.seekg(0, ios::beg); 

    // Create a Reservation instance to read records
    Reservation reservation; 
    int count = 0; // Initialize count of reservations

    // Check for end of file and Loop through records 
    while (Util::reservationFile.peek() != EOF) 
    {
        // Read a reservation record
        reservation.readFromFile(Util::reservationFile); 

        // Check if the sailingId matches
        if (strcmp(reservation.sailingId, 
            sailingId.c_str()) == 0) 
        {
            // Increment count for each matching reservation
            count++; 
        }
    }

    // Return total reservations for the sailing ID
    return count; 
}

//**********************************************************
// removeReservation()
// Removes a reservation with matching sailingId and license.
//**********************************************************
bool Reservation::removeReservation(const string &license, 
                                    const string &sailingId)
{
    // Create a Reservation instance to read records
    Reservation reservation; 

    // Check if the reservation file is open
    if (!Util::reservationFile.is_open()) 
    {
        cout << "Reservation File is not open." << endl;
        return false; // Return false if file is not open
    }

    Util::reservationFile.clear(); // Clear any error flags

    // Move read pointer to beginning
    Util::reservationFile.seekg(0, ios::beg); 

    // Variable to store current position in the file
    streampos currentPos; 

    // Variable to store position of matching record
    streampos matchPos = -1; 

    // Step 1:Find Matching record and Loop till end of file
    while (!Util::reservationFile.eof()) 
    {
        // Read a reservation record
        reservation.readFromFile(Util::reservationFile); 
        // Get current position
        currentPos = Util::reservationFile.tellg() - 
                        static_cast<streamoff>(RECORD_SIZE); 

        // Check if the current record matches the given 
        // license and sailingId
        if (strcmp(reservation.license, 
            license.c_str()) == 0 &&
            strcmp(reservation.sailingId, 
            sailingId.c_str()) == 0)
        {
            // Store position of matching record
            matchPos = currentPos; 
            break; // Exit loop if match is found
        }
    }
    if (matchPos == -1) // Check if no match was found
    {
        cout << "Reservation not found." << endl;
        // Return false if no matching reservation is found
        return false; 
    }

    // Step 2: Determine last record position
    Util::reservationFile.clear(); // Clear any error flags
    // Move to end of the file
    Util::reservationFile.seekg(0, ios::end); 
    // Get total file size
    streamoff fileSize = Util::reservationFile.tellg(); 
    // Calculate position of the last record
    streamoff lastRecordPos = fileSize - RECORD_SIZE; 

    // Check if the matched record is the last one
    if (matchPos == lastRecordPos) 
    {
        Util::reservationFile.close(); // Close the file
        // Truncate the file to remove the last record
        Util::truncate("reservation.dat", lastRecordPos); 
        // Reopen the file
        Util::reservationFile.open("reservation.dat", ios::in 
                                    | ios::out | ios::binary); 
        return true; // Return true indicating success
    }

    // Step 3: Read last record
    // Create a Reservation instance for the last record
    Reservation lastRecord; 
    Util::reservationFile.clear(); // Clear any error flags
    // Move to the last record's position
    Util::reservationFile.seekg(lastRecordPos, ios::beg); 
    // Read last record data
    Util::reservationFile.read(
        reinterpret_cast<char *>(&lastRecord), RECORD_SIZE); 

    // Step 4: Overwrite matched record with last record
    Util::reservationFile.clear(); // Clear any error flags
    // Move to the position of the matched record
    Util::reservationFile.seekp(matchPos, ios::beg); 
    // Write last record data to matched position
    Util::reservationFile.write(
        reinterpret_cast<const char *>(&lastRecord), RECORD_SIZE); 

    // Step 5: Truncate the file
    Util::reservationFile.close(); // Close the file
    // Truncate the file to remove the last record
    Util::truncate("reservation.dat", fileSize 
                        - RECORD_SIZE); 
    // Reopen the file
    Util::reservationFile.open("reservation.dat", ios::in 
                                | ios::out | ios::binary); 

    return true; // Return true indicating success
}

//**********************************************************
// removeReservationsOnSailing()
// Removes all reservations that match the given sailing ID.
//**********************************************************

// TEST ABOVE FIRST, THIS WITH 1-1 LOOP AT FRONT & END LATER, 
// OTHERWISE TOO MANY PRINTS
bool Reservation::removeReservationsOnSailing(
                    const std::string &sailingId)
{
    // Check if the reservation file is open
    if (!Util::reservationFile.is_open()) 
    {
        cout << "Reservation File is not open." << endl;
        return false; // Return false if file is not open
    }

    // Create a Reservation instance to read records
    Reservation reservation; 
    // Flag to indicate if a matching reservation is found
    bool foundAMatchingReservation = false; 

    // Clear any error flags
    Util::reservationFile.clear(); 
    // Move read pointer to beginning
    Util::reservationFile.seekg(0, ios::beg); 

    // Read the records until the end of the file
    // Loop until end of file
    while (!Util::reservationFile.eof()) 
    {
        // Read a reservation record
        reservation.readFromFile(Util::reservationFile); 

        // Check if the sailingId matches
        if (strcmp(reservation.sailingId, 
            sailingId.c_str()) == 0) 
        {
            // Found at least one matching reservation
            foundAMatchingReservation = true; 

            // Extract the license number of the reservation
            // record
            string license(reservation.license); 

            // Call removeReservation using both parameters
            removeReservation(license, sailingId); 
        }
    }

    // Check if no matching reservations were found
    if (!foundAMatchingReservation) 
    {
        cout <<"No reservations found for this sailing ID: " 
        << sailingId<<"\n Hence, no reservations deletions "
        << "happened." << endl;
    }

    // Return true indicating the operation was completed
    return true; 
}

//**********************************************************
// setCheckedIn()
// Marks a reservation as checked in and update the checked
// -in value in the binary file record.
//**********************************************************
void Reservation::setCheckedIn(const string &license)
{
    // Check if the reservation file is open
    if (!Util::reservationFile.is_open()) 
    {
        cout << "Error opening Reservation File!" << endl;
        return; // Exit if file is not open
    }
    // Clear any error flags
    Util::reservationFile.clear(); 
    // Move read pointer to beginning
    Util::reservationFile.seekg(0, ios::beg); 

    // Create a Reservation instance to read records
    Reservation reservation; 

    // Loop through records
    while (reservation.readFromFile(Util::reservationFile)) 
    {
        // Get start position of the current record
        streampos recordStartPos = 
        Util::reservationFile.tellg() 
        - static_cast<streamoff>(RECORD_SIZE); 

        // Check if the license matches
        if (strcmp(reservation.license, 
            license.c_str()) == 0) 
        {
            // Mark the reservation as checked in
            reservation.onBoard = true; 
            // Output fare for the vehicle
            cout << "The fare for your vehicle is : $" 
                << calculateFare(license) << endl; 

            // Update the record in the file
            // Move write pointer to the start of the current
            // record
            Util::reservationFile.seekp(recordStartPos); 
            // Write updated reservation data
            reservation.writeToFile(Util::reservationFile); 
            return; // Exit after updating
        }
    }

    // Error message if reservation not found
    cout << "Reservation with license " << license 
        << " not found." << endl; 
}

//$14 for normal vehicles under 2m high and 7m long
// For long low special vehicles $2 * length in meters; For
// long overheight vehicles $3 * length in meters
float Reservation::calculateFare(const string &license)
{
    // Create a Vehicle instance to fetch details
    Vehicle vehicle; 
    // Get height of the vehicle
    float height = vehicle.getHeight(license); 
    // Get length of the vehicle
    float length = vehicle.getLength(license); 

    if (height <= REGULAR_VEHICLE_HEIGHT 
        && length <= REGULAR_VEHICLE_LENGTH)
    {
        // Normal vehicle fare
        return REGULAR_VEHICLE_FARE; 
    }
    else if (length > REGULAR_VEHICLE_LENGTH 
            && height <= REGULAR_VEHICLE_HEIGHT)
    { 
        // Long overheight vehicle fare
        return 2.0 * length; 
    }
    else if (length > REGULAR_VEHICLE_LENGTH 
            && height > REGULAR_VEHICLE_HEIGHT)
    { 
        // Long-overheight special vehicle
        return 3.0 * length; 
    }
    else if (length > REGULAR_VEHICLE_LENGTH 
            && height > REGULAR_VEHICLE_HEIGHT 
            && length > REGULAR_VEHICLE_LENGTH 
            && height <= REGULAR_VEHICLE_HEIGHT) 
    {
        // Combined fare for both conditions
        return (3.0 * length) + (2.0 * length); 
    }
    // Return 0 for invalid vehicle dimensions
    return 0.0; 
}