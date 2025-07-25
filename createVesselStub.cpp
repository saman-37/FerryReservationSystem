
#include "OtherControls.h"
#include <string>
#include <iostream>
using namespace std;

Vessel vessel; // Global instance of Vessel to be used in createVessel function


//************************************************************
// createVessel()
//************************************************************
// Writes a new vessel record to file if parameters are valid.
//************************************************************
bool createVessel(const string &vesselName, int HCLL, int LCLL)
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