//************************************************************
// Sailing.h
//************************************************************
// Purpose: Represents a ferry sailing with fixed-size binary fields
// and supports lane management (HRL, LRL), file operations, and info retrieval.
// July 10, 2025 Version 1
//************************************************************

#pragma once

using namespace std;

#include <fstream>
#include <string>

class Sailing
{
public:
    static const int SAILING_ID_LENGTH = 9;                                                    // Length of the sailing ID
    static const int VESSEL_NAME_LENGTH = 25;                                                   // Length of the vessel name
    static const int RECORD_SIZE = SAILING_ID_LENGTH + VESSEL_NAME_LENGTH + sizeof(double) * 3; // Size of each record in bytes

  char sailingId[SAILING_ID_LENGTH + 1];   // Unique identifier for the sailing
  char vesselName[VESSEL_NAME_LENGTH + 1]; // Name of the vessel
  double HRL;                              // High Remaining Length in meters
  double LRL;                              // Low Remaining Length in meters

    Sailing();                                                                          // Default Constructor
    Sailing(const char* sailingId, const char* vesselName, double HRL, double LRL); // in: sailingId, vesselName, HRL, LRL

  void writeToFile(fstream &file) const; // Write sailing information to a file, in-out: file
  void readFromFile(fstream &file);      // Read sailing information from a file, in-out: file

  string toString() const; // Convert sailing data to string for display, out: string

  static bool Sailing::searchForSailing(const string &sailingId, Sailing &foundSailing); // Searches for a sailing by ID, in: sailingId, out: foundSailing and full record of the found sailing

  // Step 6: check if sailing has space available for this new reservation
  /* Each sailing has High Ceiling Lane Length (HCLL) and Low Ceiling Lane Length (LCLL) capacity. If the low ceiling reserved space becomes full, low
    vehicles can be reserved into the high ceiling lanes, so we need to check both capacities.
    Check in the LCLL if regular vehicle, or check HCLL if not available in LCLL, and HCLL if special vehicle.
    If space is available, write the reservation to the file.
  */

  static bool isSpaceAvailable(const string &sailingId, bool isSpecial, double vehicleLength, double vehicleHeight); // Checks if space is available for a new reservation, in: sailingId, vehicleLength, isSpecial

  void open(const string &sailingId, const string &vesselName, double HRL, double LRL); // in: sailingID, vesselName, HRL, LRL

  static Sailing getSailingInfo(const string &sailingId); // returns sailing information as a string, in: sailingId

    static bool checkExist(string sailingId);                                                   // in: sailingId
    static bool writeSailing(string &sailingId, string &vesselName, double HRL, double LRL);     // in: sailingId, vesselName, HRL, LRL
    static bool removeSailing(string sailingId);                                                // in: sailingId
    static bool isSpaceAvailable(const string &sailingId, double vehicleLength, bool isSpecial); // in: sailingId, vehicleLength, isSpecial

  static void reduceSpace(const string &sailingId, double vehicleLength, bool isSpecial); // in-out: modifies storage file
  static void addSpace(const string &sailingId, double vehicleLength);                    // in-out: modifies storage file

  double getHRL(const string &sailingId) const; // getter for HRL (High Remaining Length), in: sailingId, out: HRL
  double getLRL(const string &sailingId) const; // getter for LRL (Low Remaining Length), in: sailingId, out: LRL
};
