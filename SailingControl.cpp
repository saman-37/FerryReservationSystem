//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// SailingControl.cpp
//************************************************************
// Purpose: Mid-level control module for sailing operations.
// Handles creation, deletion, reporting, and querying sailings.
// July 25, 2025 Version 2 - Yadhu
//************************************************************

#include "SailingControl.h"
#include "Sailing.h"
#include "Reservation.h"
#include "Vessel.h"
#include "Util.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
using namespace std;

//************************************************************
// Default constructor
//************************************************************
SailingControl::SailingControl() {
    // No initialization needed for this controller
}

//************************************************************
// createSailing
//************************************************************
// Creates a new sailing if it does not already exist and the
// vessel exists. Retrieves initial HRL and LRL from vessel.
// in: sailingId (string), vesselName (string)
// out: true if creation succeeded, false otherwise
//************************************************************
bool SailingControl::createSailing(const string& sailingId, const string& vesselName) {
    if (Sailing::checkExist(sailingId)) {
        cout << "Sailing already exists." << endl;
        return false;
    }
    if (!Vessel::checkExist(vesselName)) {
        cout << "Vessel does not exist." << endl;
        return false;
    }

    int hcll = Vessel::getHCLL(vesselName);
    int lcll = Vessel::getLCLL(vesselName);

    return Sailing::writeSailing(const_cast<string&>(sailingId),
                                 const_cast<string&>(vesselName),
                                 hcll, lcll);
}

//************************************************************
// deleteSailing
//************************************************************
// Deletes a sailing record and removes all associated reservations.
// in: sailingId (string)
// out: true if deletion was successful, false if sailing doesn't exist
//************************************************************
bool SailingControl::deleteSailing(const string& sailingId) {
    if (Sailing::checkExist(sailingId)) {
        cout << "Entered deleteSailing" << endl;
        Reservation reservation;
        reservation.removeReservationsOnSailing(sailingId);
        return Sailing::removeSailing(sailingId);
        cout << "Exiting deleteSailing" << endl;
    }
    else {
        cout << "deleteSailing return false" << endl;
        return false;
    }
    cout << "Exited Successfully deleteSailing" << endl;
}

//************************************************************
// querySailing
//************************************************************
// Retrieves a sailing by ID and prints all relevant details
// including HRL, LRL, vehicle count, and capacity percentage.
// in: sailingId (string)
//************************************************************
void SailingControl::querySailing(const string& sailingId) {
    if (!Sailing::checkExist(sailingId)) {
        cout << "No sailing with ID '" << sailingId << "' exists." << endl;
        return;
    }

    Sailing sailing = Sailing::getSailingInfo(sailingId);

    cout << "\n========== Sailing Details ==========\n";
    cout << "Sailing ID: " << sailingId << endl;
    cout << "Vessel Name: " << sailing.vesselName << endl;

    int totalVehicles = Reservation::getTotalReservationsOnSailing(sailingId);
    double totalCapacity = sailing.HRL + sailing.LRL;
    double usedCapacity = totalCapacity - (sailing.HRL + sailing.LRL); // ← if not calculated, will always be 0
    double percentUsed = (totalCapacity == 0) ? 0 : (usedCapacity / totalCapacity) * 100.0;

    cout << "High Remaining Capacity (HRL): " << fixed << setprecision(0) << sailing.HRL << " m" << endl;
    cout << "Low Remaining Capacity (LRL): " << fixed << setprecision(0) << sailing.LRL << " m" << endl;
    cout << "Total Vehicles on Board: " << totalVehicles << endl;
    cout << "Capacity Used: " << fixed << setprecision(0) << percentUsed << "%\n";
}

//************************************************************
// printSailingReport
//************************************************************
// Displays a multi-entry report of all sailings stored in the file.
// Allows users to view reports in chunks of 5 with paging prompt.
//************************************************************
void SailingControl::printSailingReport() {
    fstream file("sailing.dat", ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Unable to open sailing.dat for reading." << endl;
        return;
    }

    vector<string> sailingIds;
    Sailing sailing;

    // Collect sailing IDs from file
    while (true)
    {
        Sailing sailing;

        if (!file.read(sailing.sailingId, Sailing::SAILING_ID_LENGTH + 1)) break;
        if (!file.read(sailing.vesselName, Sailing::VESSEL_NAME_LENGTH + 1)) break;
        if (!file.read(reinterpret_cast<char*>(&sailing.HRL), sizeof(double))) break;
        if (!file.read(reinterpret_cast<char*>(&sailing.LRL), sizeof(double))) break;

        sailingIds.push_back(string(sailing.sailingId));
    }

    file.close();

    if (sailingIds.empty()) {
        cout << "No sailings available to display." << endl;
        return;
    }

    // Header
    cout << "=================== Sailing Report ===================\n";
    cout << left
         << setw(10) << "Date"
         << setw(15) << "Sailing_ID"
         << setw(20) << "Vessel name"
         << setw(6)  << "LRL"
         << setw(6)  << "HRL"
         << setw(8)  << "Total"
         << "% of lane\n";

    size_t count = 0;

    // Display sailings in groups of 5
    while (count < sailingIds.size()) {
        size_t batchEnd = min(count + 5, sailingIds.size());
        for (size_t i = count; i < batchEnd; ++i) {
            Sailing s = Sailing::getSailingInfo(sailingIds[i]);
            string date = sailingIds[i].substr(sailingIds[i].find('-') + 1); // e.g., extract date from ID
            int totalVehicles = Reservation::getTotalReservationsOnSailing(s.sailingId);
            double total = s.HRL + s.LRL;
            double used = total - (s.HRL + s.LRL); // Placeholder logic (should be real usage)
            double percent = (total > 0.0) ? ((used / total) * 100.0) : 0.0;
            cout << left
                 << setw(10) << date
                 << setw(15) << s.sailingId
                 << setw(20) << s.vesselName
                 << setw(6)  << (int)s.LRL
                 << setw(6)  << (int)s.HRL
                 << setw(8)  << totalVehicles
                 << fixed << setprecision(1) << percent << endl;
        }

        count = batchEnd;

        if (count >= sailingIds.size()) break;

        // Prompt user to continue or stop
        cout << "\nShow more sailings? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (tolower(choice) != 'y') break;
    }
}