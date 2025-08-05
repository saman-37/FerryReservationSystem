//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*********************************************************
// OtherControls.cpp
//*********************************************************
// Purpose: Implements control-level logic for reservations,
// vessels, and check-in functionality for FerryReserver 
// system.
// July 12, 2025 Version 2 - Darpandeep Kaur and Samanpreet
//*********************************************************

#include "OtherControls.h"
#include "Sailing.h"
#include "Vehicle.h"
#include "Vessel.h"
#include "Reservation.h"
#include "Util.h"
#include <string>
#include <iostream>

using namespace std;

Vessel vessel;           // Global instance of Vessel for
                         // managing vessel records
Sailing sailing;         // Global instance of Sailing for
                         // managing sailing records
Reservation reservation; // Global instance of Reservation
                         // for managing reservation records

//*********************************************************
// Default constructor for OtherControls class
//*********************************************************
OtherControls::OtherControls() // Default Constructor
{
    //No internal state to initialize for this control class
}

//*********************************************************
// createReservation()
//*********************************************************
// Implements reservation logic including:
// - sailing lookup
// - duplicate reservation check
// - vehicle existence and info collection
// - vehicle writing (if new)
// - sailing capacity check
// - reservation creation
// Also adjusts space based on vehicle size.
// in: sailingId, licensePlate
//*********************************************************
bool OtherControls::createReservation(string &phoneNumber, 
                    string &sailingId, string &licensePlate) 
{
    // Step 1: check if sailing exists
    // Created a sailing instance; pass it by reference so it 
    // can be filled with file data if found
    // Check if the sailing with the given ID exists
    if (!Sailing::checkExist(sailingId)) 
    {
        // Sailing does not exist
        cout << "The sailing with id " << sailingId 
            << " does not exist." << endl;
        return false; // Return false if sailing does not exist
    }

    // Step 2: check if reservation already exists
    // Check if a reservation already exists for the vehicle and
    // sailing
    if (Reservation::checkExist(licensePlate, sailingId)) 
    {
        // Return false if reservation already exists
        cout << "This reservation already exists." << endl;
        return false; 
    }

    // Step 4: check if vehicle exists
    // Check if vehicle is known from license plate
    // Variables to store vehicle dimensions
    float height, length; 

    // Flag to indicate if the vehicle is special
    bool isSpecial = false; 

    // Check if the vehicle exists based on the license plate
    if (Vehicle::checkExist(licensePlate)) 
    {
        // Vehicle exists, fetch its details
        height = Vehicle::getHeight(licensePlate);
        length = Vehicle::getLength(licensePlate);
    }
    else
    {
        //Step 5: Check if the formats are correct
        // Validate HCLL and LCLL values
        if (phoneNumber.length() > PHONE_LENGTH) 
        {
            cout << "Invalid format for phone number." << endl;
            return false; // Invalid phone number
        }
        else if (licensePlate.length() > LICENSE_PLATE_LENGTH 
                || licensePlate.length() <= LICENSE_MIN_LENGTH)
        {
            cout << "Invalid format for License Plate." << endl;
            return false; // Invalid License plate
        }

        // Step 6: write the new vehicle record if it does not 
        // already exist
        // Ask user if this is a special vehicle, and prompt for
        // input if yes
        // Variable to store user input for special vehicle check
        char isSpecialInput; 

        cout << "Is this a special vehicle? (y/n): " << endl;
        cin >> isSpecialInput; // Get user input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Check if the user indicated a special vehicle
        if (isSpecialInput == 'y' || isSpecialInput == 'Y') 
        {
            // Set the flag to true for special vehicle
            isSpecial = true; 
            // Prompt user for vehicle dimensions
            cout << "Enter height (in meters): ";
            cin >> height; // Get height from user
            cout << "Enter length (in meters): ";
            cin >> length; // Get length from user
            // Validate dimensions
            /*
            Height: Special vehicle height max 9.9 meters. 
            Range 2.1 to 9.9m. Precision 0.1
            Length: Special vehicle length max 99.9 meters. 
            Range 7.1 to 99.9m. Precision 0.1
            */
            if (height < REGULAR_VEHICLE_HEIGHT 
                || height > SPECIAL_VEHICLE_MAX_HEIGHT 
                || length < REGULAR_VEHICLE_LENGTH 
                || length > SPECIAL_VEHICLE_MAX_LENGTH)
            {
                cout << "Invalid height or length format."
                 << endl;
                return false; // Invalid height or length
            }

            // Validate phone number format
            // Check if phone number exceeds maximum length
            // Return false for invalid phone number
            if (phoneNumber.length() > PHONE_LENGTH) 
            {
                cout << "Invalid phone number format."
                    << " Must be max 14 digits." << endl;
                return false; 
            }
        }
        else
        {
            // Default height for regular vehicles
            height = REGULAR_VEHICLE_HEIGHT; 
            // Default length for regular vehicles
            length = REGULAR_VEHICLE_LENGTH; 
        }

        // Write special vehicle record to file
        Vehicle::writeVehicle(licensePlate, phoneNumber,
                                 height, length);
    }

    // Step 7: check if sailing has space available for this 
    // new reservation
    if (Sailing::isSpaceAvailable(sailingId, isSpecial, 
            length, height) == false) 
    {
        cout << "No space available on sailing." << endl;
        return false; // No space available
    }

    // Step 8: Reduce the space available, if reservation is 
    // successful
    // Adjusts space based on vehicle type (high ceiling or
    // low ceiling)
    Sailing::reduceSpace(sailingId, length, isSpecial); 

    // Step 9: Create the reservation record
    Reservation::writeReservation(licensePlate, sailingId); 

    return true; // Return true if reservation was successful
}

//*********************************************************
// deleteReservation()
//*********************************************************
// Removes a reservation and returns the vehicle’s reserved
// space back to the sailing (LCLL or HCLL as appropriate).
//*********************************************************
bool OtherControls::deleteReservation(string &license, 
                                    string &sailingId) 
{
    // Step 1: check if reservation exists
    if (Reservation::checkExist(license, sailingId) == false) 
    {
        cout << "Reservation not found in the system." << endl;
        return false; // Return false if reservation does not exist
    }

    // Step 2: get length from the vehicle
    // Create a Vehicle instance to fetch details
    Vehicle vehicle; 

    // Fetch vehicle length from file using license key
    float length = vehicle.getLength(license); 

    // Step 3: get height from the vehicle

    // Fetch vehicle height from file using license key
    float height = vehicle.getHeight(license); 

    // Step 4: remove the reservation record from the reservation
    // file
    if (!Reservation::removeReservation(license, sailingId)) 
    {
        return false; // Failed to remove reservation
    }

    // Step 5: add the space back to the sailing
    bool isSpecial = height > 2;
    Sailing::addSpace(sailingId, length, isSpecial);
    return true; // Return true if deletion was successful
};

//*********************************************************
// checkIn()
//*********************************************************
// Marks a reservation as checked in if it exists. in: sailingId,
// licensePlate
//*********************************************************
bool OtherControls::checkIn(string &licensePlate, string &sailingId)
{
    // Step 1: Check if reservation exists
    if (!Reservation::checkExist(licensePlate, sailingId)) 
    {
        return false; // Reservation does not exist
    }

    // Step 2: Set the reservation as checked in
    Reservation::setCheckedIn(licensePlate); 

    return true; // Successfully checked in
};

//*********************************************************
// createVessel()
//*********************************************************
// Writes a new vessel record to file if parameters are valid.
//*********************************************************
bool OtherControls::createVessel(string &vesselName, 
                                int HCLL, int LCLL)
{
    // Step 1: Check if all the parameters are valid
    // Check if vessel name exceeds maximum length and
    // Validate HCLL and LCLL values
    if (vesselName.length() > NAME_LENGTH || HCLL <= 0 
            || LCLL <= 0 || HCLL > 3600.0 || LCLL > 3600.0) 
    {
        cout << "Invalid format for vessel name,"
            << " or invalid HCLL or LCLL values." << endl;
        return false; // Invalid vessel name or ID length
    }

    // Step 2: Check if vessel already exists
    if (vessel.checkExist(vesselName)) 
    {
        cout << "Vessel with Vessel Name " << vesselName 
            << " already exists." << endl;
        return false; // Vessel already exists
    }
    else
    {
        // Step 3: Create a new vessel record
        Vessel newVessel(vesselName, HCLL, LCLL); 
        // Check if the vessel file is open for writing
        if (!Util::vesselFile.is_open()) 
        {
            cout << "Error opening vessel file for writing." 
                << endl;
            return false; // Error opening file
        }
        else
        {
            // Save vessel record
            return Vessel::writeVessel(vesselName, HCLL, LCLL); 
        }
    }
};