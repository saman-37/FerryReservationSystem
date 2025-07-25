//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// ************************************************************
// OtherControls.cpp
// ************************************************************
// Purpose: Mid-level controller that coordinates reservation
// creation, deletion, and check-in scenarios. Interfaces with
// entity classes like Vehicle, Sailing, Vessel, and Reservation
// to manage ferry system operations.
// July 12, 2025 Version 1
//************************************************************
#include "OtherControls.h"
#include "Sailing.h"
#include "Vehicle.h"
#include "Reservation.h"
#include <string>
#include <iostream>
using namespace std;

Vessel vessel; // Global instance of Vessel to be used in createVessel function

OtherControls::OtherControls() // Default Constructor
{
}

// Step 1: call from UI to create a reservation
bool createReservation(string &sailingId, string &licensePlate) // Makes a new reservation, in: sailingId, licensePlate
{

  // Step 2: check if sailing exists
  //  created a sailing instance,pass it by referance, such that if sailing found, can be filled with other attributes, to refer later to sailing capacity
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
  // We dont need the attributes of found reservation to be saved, hence, passing only strings: license number and sailing id, to check its existence
  if (Reservation::checkExist(sailingId, licensePlate))
  {
    // Reservation already exists
    cout << "This reservation already exists." << endl;
    return false;
  }

  // Step 4: check if vehicle exists
  // Created an instance of vehicle, pass it by referance pass the license number, read the vehicle file, restore the attributes of the vehicle if found into this object.
  Vehicle vehicle; // a vehicle instance, appsed  such that if sailing found, can be filled with opther attributes and returned to refer later to sailing capacity
  if (Vehicle::checkExist(licensePlate))
  {
    // vehicle exists and foundVehicle contains it
  }

  // Step 5: write the new vehicle record. if not already exist
  // we ask user for further details of the vehicle, if it is special
  char isSpecial;
  cout << "Is this a special vehicle? (y/n): y" << endl;
  cin >> isSpecial;
  double height, length;
  if (isSpecial == 'y' || isSpecial == 'Y')
  {

    cout << "Enter height (in meters): ";
    cin >> height;
    cout << "Enter length (in meters): ";
    cin >> length;

    // Check for correct format and data range of height and length
    /*
    Height: Special vehicle height max 9.9 meters. Range 2.1 to 9.9m. Precision 0.1 [If not stated, -0.5 marks]
    Length: Special vehicle length max 99.9 meters. Range 7.1-999.9m. Precision .1 [If not stated, -0.5 marks]
    */
    if (height < 2.1 || height > 9.9 || length < 7.1 || length > 99.9)
    {
      cout << "Invalid height or length for special vehicle." << endl;
      return false; // Invalid height or length
    }

    // Phone number is needed to save the vehicle record
    string phone;
    cout << "Enter Customer Phone Number (format: 14 characters):7781234567" << endl;
    cin >> phone;
    // Check for correct format and data range of phone number
    if (phone.length() != 14)
    {
      cout << "Invalid phone number format. Must be 14 digits." << endl;
      // Invalid phone number format
      return false;
    }

    // Write the vehicle to the file
    Vehicle::writeVehicle(licensePlate, phone, height, length); // Phone number is not used here
  }

  else
  {
    // Write the vehicle to the file with default height and length
    Vehicle::writeVehicle(licensePlate, "", 2.0, 7.0); // Default values for height and length
  }

  // Step 6: check if sailing has space available for this new reservation
  /*
  Each sailing has High Ceiling Lane Length (HCLL) and Low Ceiling Lane Length (LCLL) capacity. If the low ceiling reserved space becomes full, low
  vehicles can be reserved into the high ceiling lanes, so we need to check both capacities.
  Check in the LCLL if regular vehicle, or check HCLL if not available in LCLL, and HCLL if special vehicle.
  If space is available, write the reservation to the file.
  */
  if (!Sailing::isSpaceAvailable(sailingId, isSpecial == 'y' || isSpecial == 'Y', length, height))
  {
    cout << "No space available on sailing." << endl;
    return false; // No space available
  }

  // Step 7: Reduce the space available, if reservation is successful
  Sailing::reduceSpace(sailingId, length, isSpecial == 'y' || isSpecial == 'Y');
}

// Step 1: call from UI to delete a reservation
// Since primary key of reservation entity is both attributes, sailingId and license, we need to pass both to delete a reservation
bool deleteReservation(string &license, string &sailingId) // Deletes all reservations for a sailing, in: sailingId
{
  // Step 2: check if reservation exists
  if (!Reservation::checkExist(sailingId, license))
  { // Reservation doesnt exist in the system.
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
    // reservation deletion successful
    return true;
  }

  // Step 5: add the space back to the sailing
  /*
  Need to specify which of HCLL or LCLL should be added back, based on the type of vehicle, and if the regular was taking HCLL space
  */
  Sailing::addSpace(sailingId, length);
};

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
// Creates a new vessel record
// in: vesselName, HCLL, LCLL
// out: returns true if vessel created successfully, false otherwise
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
    Vessel newVessel(vesselName, HCLL, LCLL);                 // Create a new Vessel object with provided details
    fstream vesselFile("vessel.dat", ios::app | ios::binary); // Open vessel file for writing
    if (!vesselFile.is_open())
    {
      cout << "Error opening vessel file for writing." << endl;
      return false; // Error opening vessel file for writting.
    }
    else
    {
      newVessel.writeToFile(vesselFile); // creates the vessel record in file
      cout << "Vessel created successfully." << endl;
      return true; // Vessel Successfully created
    }
  }
};
