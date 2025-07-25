//************************************************************
// SailingControl.h
//************************************************************
// Purpose: Mid-level controller for managing sailings.
// Provides public interface to create new sailings, delete existing ones,
// query specific sailing details, and print a complete sailing report.
// Interfaces with the Sailing entity and the Reservation module.
// July 20, 2025 Version 2 
//************************************************************

#pragma once

using namespace std;

#include "Sailing.h"
#include <string>

class SailingControl
{
public:
    //************************************************************
    // Default Constructor
    //************************************************************
    SailingControl();

    //************************************************************
    // Creates a new sailing if it doesn't already exist
    // in: sailingId - unique sailing identifier
    //     vesselName - name of the vessel
    // out: true if sailing is successfully created, false otherwise
    //************************************************************
    static bool createSailing(const string &sailingId, const string &vesselName);

    //************************************************************
    // Deletes a sailing and all associated reservations
    // in: sailingId - unique sailing identifier
    // out: true if deletion succeeded, false otherwise
    //************************************************************
    static bool deleteSailing(const string &sailingId);

    //************************************************************
    // Displays details of a specific sailing
    // in: sailingId - unique sailing identifier
    // out: prints details to console
    //************************************************************
    static void querySailing(const string &sailingId);

    //************************************************************
    // Generates a formatted report of all sailings
    // out: prints multiple sailings with paging
    //************************************************************
    static void printSailingReport();
};