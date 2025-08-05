//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*********************************************************
// createVesselStub.cpp
//*********************************************************
// Purpose: Writes a new vessel record to the file if the 
// parameters are valid. It checks for the validity of the 
// vessel name and dimensions before creating the record.
// July 24, 2025 - Version 1 - Team 18
//*********************************************************

#include "OtherControls.h"
#include "Vessel.h" 
#include <string>
#include <iostream>
#include <fstream> 

using namespace std;

//*********************************************************
// createVessel()
//*********************************************************
// Purpose: Writes a new vessel record to the file if the 
// parameters are valid. It checks for the validity of the 
// vessel name and dimensions before creating the record.
//*********************************************************
bool createVessel(const string &vesselName, 
                    int HCLL, int LCLL)
{
    // Step 1: Check if all the parameters are valid
    // Check length of vessel name and if HCLL and LCLL 
    // are positive and within limits
    if (vesselName.length() > NAME_LENGTH || 
        HCLL <= 0 || LCLL <= 0 ||            
        HCLL > 3600 || LCLL > 3600)          
    {
        cout << "Invalid format for vessel name, or "
                << "invalid HCLL or LCLL values." << endl;
        // Invalid vessel name or dimensions
        return false; 
    }

    // Step 2: Check if vessel already exists
    if (Vessel::checkExist(vesselName)) 
    {
        cout << "Vessel with Vessel Name " << vesselName 
              << " already exists." << endl;
        // Vessel already exists
        return false; 
    }
    else
    {
        // Step 3: Create a new vessel record
        Vessel newVessel(vesselName, HCLL, LCLL); 
        // Open vessel file in append mode
        fstream vesselFile("vessel.dat", ios::app 
                                       | ios::binary); 

        // Check if the file opened successfully
        if (!vesselFile.is_open()) 
        {
            // Error opening file
            cout << "Error opening vessel file for writing."
                 << endl;
            return false; 
        }
        else
        {
            // Save the vessel record to the file
            newVessel.writeToFile(vesselFile); 
            // Close the file after writing
            vesselFile.close(); 
            cout << "Vessel created successfully." << endl;
            return true; 
        }
    }
}
