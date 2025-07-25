//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// OtherControls.cpp
//************************************************************
// Purpose: Implements control-level logic for reservations, vessels,
// and check-in functionality for FerryReserver system.
// July 12, 2025 Version 1 - Darpandeep Kaur
//************************************************************

#include "OtherControls.h"
#include "Sailing.h"
#include "Vehicle.h"
#include "Reservation.h"
#include <string>
#include <iostream>
using namespace std;

Vessel vessel; // Global instance of Vessel to be used in createVessel function

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
bool createReservation(string &sailingId, string &licensePlate) // Makes a new reservation, in: sailingId, licensePlate
{
  // Step 2: check if sailing exists
  // Created a sailing instance; pass it by reference so it can be filled with file data if found
  Sailing foundSailing;
  Reservation reservation; // Reservation instance to be used later
  if (Sailing::searchForSailing(sailingId, foundSailing))
  {
    // Sailing found, and foundSailing contains it
  }
  else
  {
    // Sailing does not exist
    cout << "The sailing with id " << sailingId << " does not exist." << endl;
    return false;
  }

  // Step 3: check if reservation already exists
  // We don’t need full reservation data — just check existence
  if (Reservation::checkExist(sailingId, licensePlate))
  {
    // Reservation already exists
    cout << "This reservation already exists." << endl;
    return false;
  }

  // Step 4: check if vehicle exists
  // Check if vehicle is known from license plate
  Vehicle vehicle;
  if (Vehicle::checkExist(licensePlate))
  {
    // vehicle exists and foundVehicle contains it
  }

  // Step 5: write the new vehicle record if it does not already exist
  // Ask user if this is a special vehicle, and prompt for input if yes
  char isSpecial;
  cout << "Is this a special vehicle? (y/n): y" << endl;
  cin >> isSpecial;
  double height, length;
  if (isSpecial == 'y' || isSpecial == 'Y')
  {
    // Prompt user for vehicle dimensions
    cout << "Enter height (in meters): ";
    cin >> height;
    cout << "Enter length (in meters): ";
    cin >> length;

    // Validate dimensions
    /*
    Height: Special vehicle height max 9.9 meters. Range 2.1 to 9.9m. Precision 0.1
    Length: Special vehicle length max 99.9 meters. Range 7.1 to 99.9m. Precision 0.1
    */
    if (height < 2.1 || height > 9.9 || length < 7.1 || length > 99.9)
    {
      cout << "Invalid height or length for special vehicle." << endl;
      return false; // Invalid height or length
    }

    // Prompt for phone number
    string phone;
    cout << "Enter Customer Phone Number (format: 14 characters):7781234567" << endl;
    cin >> phone;

    // Validate phone number format
    if (phone.length() != 14)
    {
      cout << "Invalid phone number format. Must be 14 digits." << endl;
      return false;
    }

    // Write special vehicle record to file
    Vehicle::writeVehicle(licensePlate, phone, height, length);
  }
  else
  {
    // Write regular vehicle with default height and length
    Vehicle::writeVehicle(licensePlate, "", 2.0, 7.0); // Default values
  }

  // Step 6: check if sailing has space available for this new reservation
  /*
  LCLL used for regular vehicles;
  HCLL used for special vehicles or if LCLL full.
  */
  if (!Sailing::isSpaceAvailable(sailingId, isSpecial == 'y' || isSpecial == 'Y', length, height))
  {
    cout << "No space available on sailing." << endl;
    return false; // No space available
  }

  // Step 7: Reduce the space available, if reservation is successful
  Sailing::reduceSpace(sailingId, length, isSpecial == 'y' || isSpecial == 'Y');
}

//************************************************************
// deleteReservation()
//************************************************************
// Removes a reservation and returns the vehicle’s reserved
// space back to the sailing (LCLL or HCLL as appropriate).
//************************************************************
bool deleteReservation(string &license, string &sailingId) // Deletes all reservations for a sailing, in: sailingId
{
  // Step 2: check if reservation exists
  if (!Reservation::checkExist(sailingId, license))
  {
    cout << "Reservation not found in the system." << endl;
    return false;
  }

  // Step 3: get length from the vehicle
  Vehicle vehicle;
  int length = vehicle.getLength(license);

  // Step 4: remove the reservation record from the reservation file
  if (!Reservation::removeReservation(sailingId, license))
  {
    // Failed to remove reservation
    return false;
  }
  else
  {
    // Reservation deletion successful
    return true;
  }

  // Step 5: add the space back to the sailing
  /*
  Determine LCLL or HCLL based on vehicle type.
  */
  Sailing::addSpace(sailingId, length);
};

//************************************************************
// checkIn()
//************************************************************
// Marks a reservation as checked in if it exists.
//************************************************************
bool checkIn(string &licensePlate, string &sailingId) // Checks in a vehicle to a sailing, in: sailingId, licensePlate
{
  // Step 1: Check if reservation exists
  if (!Reservation::checkExist(sailingId, licensePlate))
  {
    return false; // Reservation does not exist
  }

  // Step 2: Set the reservation as checked in
  Reservation::setCheckedIn(sailingId, licensePlate);

  return true; // Successfully checked in
};

//************************************************************
// createVessel()
//************************************************************
// Writes a new vessel record to file if parameters are valid.
//************************************************************
bool createVessel(string &vesselName, int HCLL, int LCLL)
{
  // Step 1: Check if all the parameters are valid
  if (vesselName.length() > Vessel::NAME_LENGTH ||
      HCLL <= 0 || LCLL <= 0 || HCLL > 3600.0 || LCLL > 3600.0)
  {
    cout << "Invalid format for vessel name, or invalid HCLL or LCLL values." << endl;
    return false; // Invalid vessel name or ID length
  }

  // Step 2: Check if vessel already exists
  if (vessel.checkExist(vesselName))
  {
    cout << "Vessel with Vessel Name " << vesselName << " already exists." << endl;
    return false; // Vessel already exists
  }
  else
  {
    // Step 3: Create a new vessel record
    Vessel newVessel(vesselName, HCLL, LCLL);                 // Create Vessel object
    fstream vesselFile("vessel.dat", ios::app | ios::binary); // Open vessel file
    if (!vesselFile.is_open())
    {
      cout << "Error opening vessel file for writing." << endl;
      return false; // Error opening file
    }
    else
    {
      newVessel.writeToFile(vesselFile); // Save record
      cout << "Vessel created successfully." << endl;
      return true; // Vessel created
    }
  }
};