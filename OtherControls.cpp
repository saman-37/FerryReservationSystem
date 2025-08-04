//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// OtherControls.cpp
//************************************************************
// Purpose: Implements control-level logic for reservations, vessels,
// and check-in functionality for FerryReserver system.
// July 12, 2025 Version 1 - Darpandeep Kaur and Samanpreet
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

Vessel vessel;           // Global instance of Vessel
Sailing sailing;         // Global instance of Sailing
Reservation reservation; // Global instance of Reservation

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
   if (!Sailing::checkExist(sailingId))
   {
     // Sailing does not exist
     cout << "The sailing with id " << sailingId << " does not exist." << endl;
     return false;
   }

  // Step 2: check if reservation already exists
  if (Reservation::checkExist(licensePlate, sailingId))
  {
    // Reservation already exists
    cout << "This reservation already exists." << endl;
    return false;
  }

  // Step 4: check if vehicle exists
  // Check if vehicle is known from license plate
  float height, length;

  bool isSpecial = false;

  if (Vehicle::checkExist(licensePlate))
  {
    // Vehicle exists, fetch its details
    height = Vehicle::getHeight(licensePlate); // Get height from file
    length = Vehicle::getLength(licensePlate); // Get length from file
    cout << "Height: " << height << ", lenght: " << length << endl;
  }
  else
  {
    // Step 5: write the new vehicle record if it does not already exist
    // Ask user if this is a special vehicle, and prompt for input if yes
    char isSpecialInput;

    cout << "Is this a special vehicle? (y/n): " << endl;
    cin >> isSpecialInput;

    if (isSpecialInput == 'y' || isSpecialInput == 'Y')
    {
      isSpecial = true;
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
      if (height < 2.1 || height > 9.9 || length < 7.1 || length > 999.9)
      {
        cout << "Invalid height or length for special vehicle." << endl;
        return false; // Invalid height or length
      }

      // Validate phone number format
      if (phoneNumber.length() > 13)
      {
        cout << "Invalid phone number format. Must be max 14 digits." << endl;
        return false;
      }
    }

    else
    {
      height = 2.0; // Default height for regular vehicles
      length = 7.0; // Default length for regular vehicles
    }

    // Write special vehicle record to file
    Vehicle::writeVehicle(licensePlate, phoneNumber, height, length);
  }

  // // Step 6: check if sailing has space available for this new reservation
  if (Sailing::isSpaceAvailable(sailingId, isSpecial, length, height) == false)
  {
    cout << "No space available on sailing." << endl;
    return false; // No space available
  }

  // Step 7: Reduce the space available, if reservation is successful
  // Adjusts space based on vehicle type (high ceiling or low ceiling)
  Sailing::reduceSpace(sailingId, length, isSpecial);

  // Step 8: Create the reservation record
  Reservation::writeReservation(licensePlate, sailingId); // onBoard = false
  cout << "i am outide write Reservation in OtherControls.cpp" << endl;

  return true;
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

  if (Reservation::checkExist(license, sailingId) == false)
  {
    cout << "Reservation not found in the system." << endl;
    return false;
  }

  // Step 2: get length from the vehicle
  Vehicle vehicle;
  float length = vehicle.getLength(license); // Fetch vehicle length from file using license key

  // Step 3: remove the reservation record from the reservation file
  if (!Reservation::removeReservation(license, sailingId))
  {
    return false; // Failed to remove reservation
  }

  // Step 4: add the space back to the sailing
  //----------------------------------------------------------------------------
  Util::reservationFile.clear();
  Util::reservationFile.seekg(0, ios::beg); // move read pointer to beginning
  cout << "The CONTENTS after deleting reservation are: " << endl;
  while (Util::reservationFile.peek() != EOF)
  {
    reservation.readFromFile(Util::reservationFile);
    cout << reservation.toString();
  }
  //----------------------------------------------------------------------------

  cout << "Now adding space back to sailing: " << sailingId << endl;
  // Sailing::addSpace(sailingId, length);
  return true;
};

//************************************************************
// checkIn()
//************************************************************
// Marks a reservation as checked in if it exists.
//************************************************************
bool OtherControls::checkIn(string &licensePlate, string &sailingId) // Checks in a vehicle to a sailing, in: sailingId, licensePlate
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

//************************************************************
// createVessel()
//************************************************************
// Writes a new vessel record to file if parameters are valid.
//************************************************************
bool OtherControls::createVessel(string &vesselName, int HCLL, int LCLL)
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
    Vessel newVessel(vesselName, HCLL, LCLL); // Create Vessel object
    if (!Util::vesselFile.is_open())
    {
      cout << "Error opening vessel file for writing." << endl;
      return false; // Error opening file
    }
    else
    {
      return Vessel::writeVessel(vesselName, HCLL, LCLL); // Save record{
    }
  }
};