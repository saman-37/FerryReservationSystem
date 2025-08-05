//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// OtherControls.cpp
//************************************************************
// Purpose: Implements control-level logic for reservations, vessels,
// and check-in functionality for FerryReserver system.
// July 12, 2025 Version 2 - Darpandeep Kaur and Samanpreet
//************************************************************

#include "OtherControls.h"
#include "Sailing.h"
#include "Vehicle.h"
#include "Vessel.h"
#include "Reservation.h"
#include "Util.h"
#include <string>
#include <iostream>

using namespace std;

Vessel vessel;           // Global instance of Vessel for managing vessel records
Sailing sailing;         // Global instance of Sailing for managing sailing records
Reservation reservation; // Global instance of Reservation for managing reservation records

//************************************************************
// Default constructor for OtherControls class
//************************************************************
OtherControls::OtherControls() // Default Constructor
{
    // No internal state to initialize for this control class
}

//************************************************************
// createReservation()
//************************************************************
// Implements reservation logic including:
// - sailing lookup
// - duplicate reservation check
// - vehicle existence and info collection
// - vehicle writing (if new)
// - sailing capacity check
// - reservation creation
// Also adjusts space based on vehicle size.
//************************************************************
bool OtherControls::createReservation(string &phoneNumber, string &sailingId, string &licensePlate) // Makes a new reservation, in: sailingId, licensePlate
{
    // Step 1: check if sailing exists
    // Created a sailing instance; pass it by reference so it can be filled with file data if found
    if (!Sailing::checkExist(sailingId)) // Check if the sailing with the given ID exists
    {
        // Sailing does not exist
        cout << "The sailing with id " << sailingId << " does not exist." << endl;
        return false; // Return false if sailing does not exist
    }

    // Step 2: check if reservation already exists
    if (Reservation::checkExist(licensePlate, sailingId)) // Check if a reservation already exists for the vehicle and sailing
    {
        // Reservation already exists
        cout << "This reservation already exists." << endl;
        return false; // Return false if reservation already exists
    }

    // Step 4: check if vehicle exists
    // Check if vehicle is known from license plate
    float height, length; // Variables to store vehicle dimensions

    bool isSpecial = false; // Flag to indicate if the vehicle is special

    if (Vehicle::checkExist(licensePlate)) // Check if the vehicle exists based on the license plate
    {
        // Vehicle exists, fetch its details
        height = Vehicle::getHeight(licensePlate); // Get height from file
        length = Vehicle::getLength(licensePlate); // Get length from file
    }
    else
    {
        //Step 5: Check if the formats are correct
        if (phoneNumber.length() >= PHONE_LENGTH) // Validate HCLL and LCLL values
        {
            cout << "Invalid format for phone number." << endl;
            return false; // Invalid phone number
        }
        else if (licensePlate.length() >= LICENSE_PLATE_LENGTH || licensePlate.length() <= LICENSE_MIN_LENGTH)
        {
            cout << "Invalid format for License Plate." << endl;
            return false; // Invalid License plate
        }

        // Step 6: write the new vehicle record if it does not already exist
        // Ask user if this is a special vehicle, and prompt for input if yes
        char isSpecialInput; // Variable to store user input for special vehicle check

        cout << "Is this a special vehicle? (y/n): " << endl;
        cin >> isSpecialInput; // Get user input

        if (isSpecialInput == 'y' || isSpecialInput == 'Y') // Check if the user indicated a special vehicle
        {
            isSpecial = true; // Set the flag to true for special vehicle
            // Prompt user for vehicle dimensions
            cout << "Enter height (in meters): ";
            cin >> height; // Get height from user
            cout << "Enter length (in meters): ";
            cin >> length; // Get length from user
            // Validate dimensions
            /*
            Height: Special vehicle height max 9.9 meters. Range 2.1 to 9.9m. Precision 0.1
            Length: Special vehicle length max 99.9 meters. Range 7.1 to 99.9m. Precision 0.1
            */
            if (height < REGULAR_VEHICLE_HEIGHT || height > SPECIAL_VEHICLE_MAX_HEIGHT 
              || length < REGULAR_VEHICLE_LENGTH || length > SPECIAL_VEHICLE_MAX_LENGTH)
            {
                cout << "Invalid height or length for special vehicle." << endl;
                return false; // Invalid height or length
            }

            // Validate phone number format
            if (phoneNumber.length() > PHONE_LENGTH) // Check if phone number exceeds maximum length
            {
                cout << "Invalid phone number format. Must be max 14 digits." << endl;
                return false; // Return false for invalid phone number
            }
        }
        else
        {
            height = REGULAR_VEHICLE_HEIGHT; // Default height for regular vehicles
            length = REGULAR_VEHICLE_LENGTH; // Default length for regular vehicles
        }

        // Write special vehicle record to file
        Vehicle::writeVehicle(licensePlate, phoneNumber, height, length); // Save vehicle details
    }

    // Step 7: check if sailing has space available for this new reservation
    // if (Sailing::isSpaceAvailable(sailingId, isSpecial, length, height) == false) // Check if there is space for the vehicle
    // {
    //     cout << "No space available on sailing." << endl;
    //     return false; // No space available
    // }

    // Step 8: Reduce the space available, if reservation is successful
    // Adjusts space based on vehicle type (high ceiling or low ceiling)
    Sailing::reduceSpace(sailingId, length, isSpecial); // Reduce available space for the sailing

    // Step 9: Create the reservation record
    Reservation::writeReservation(licensePlate, sailingId); // Create a new reservation record

    return true; // Return true if reservation was successful
}

//************************************************************
// deleteReservation()
//************************************************************
// Removes a reservation and returns the vehicle’s reserved
// space back to the sailing (LCLL or HCLL as appropriate).
//************************************************************
bool OtherControls::deleteReservation(string &license, string &sailingId) // Deletes all reservations for a sailing, in: sailingId
{
    // Step 1: check if reservation exists
    if (Reservation::checkExist(license, sailingId) == false) // Check if the reservation exists
    {
        cout << "Reservation not found in the system." << endl;
        return false; // Return false if reservation does not exist
    }

    // Step 2: get length from the vehicle
    Vehicle vehicle; // Create a Vehicle instance to fetch details
    float length = vehicle.getLength(license); // Fetch vehicle length from file using license key

    // Step 3: remove the reservation record from the reservation file
    if (!Reservation::removeReservation(license, sailingId)) // Attempt to remove the reservation
    {
        return false; // Failed to remove reservation
    }

    // Step 4: add the space back to the sailing
    Sailing::addSpace(sailingId, length); // Add the space back to the sailing
    return true; // Return true if deletion was successful
};

//************************************************************
// checkIn()
//************************************************************
// Marks a reservation as checked in if it exists.
//************************************************************
bool OtherControls::checkIn(string &licensePlate, string &sailingId) // Checks in a vehicle to a sailing, in: sailingId, licensePlate
{
    // Step 1: Check if reservation exists
    if (!Reservation::checkExist(licensePlate, sailingId)) // Check if the reservation exists
    {
        return false; // Reservation does not exist
    }

    // Step 2: Set the reservation as checked in
    Reservation::setCheckedIn(licensePlate); // Mark the reservation as checked in

    return true; // Successfully checked in
};

//************************************************************
// createVessel()
//************************************************************
// Writes a new vessel record to file if parameters are valid.
//************************************************************
bool OtherControls::createVessel(string &vesselName, int HCLL, int LCLL)
{
    // Step 1: Check if all the parameters are valid
    if (vesselName.length() > NAME_LENGTH || // Check if vessel name exceeds maximum length
        HCLL <= 0 || LCLL <= 0 || HCLL > 3600.0 || LCLL > 3600.0) // Validate HCLL and LCLL values
    {
        cout << "Invalid format for vessel name, or invalid HCLL or LCLL values." << endl;
        return false; // Invalid vessel name or ID length
    }

    // Step 2: Check if vessel already exists
    if (vessel.checkExist(vesselName)) // Check if the vessel already exists
    {
        cout << "Vessel with Vessel Name " << vesselName << " already exists." << endl;
        return false; // Vessel already exists
    }
    else
    {
        // Step 3: Create a new vessel record
        Vessel newVessel(vesselName, HCLL, LCLL); // Create Vessel object with provided parameters
        if (!Util::vesselFile.is_open()) // Check if the vessel file is open for writing
        {
            cout << "Error opening vessel file for writing." << endl;
            return false; // Error opening file
        }
        else
        {
            return Vessel::writeVessel(vesselName, HCLL, LCLL); // Save vessel record
        }
    }
};