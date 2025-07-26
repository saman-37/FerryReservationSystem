//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// SailingControl.cpp
//************************************************************
// Purpose: Mid-level control module for sailing operations.
// Handles creation, deletion, reporting, and querying sailings.
// July 25, 2025 Version 1 - Yadhu
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
    if (Sailing::checkExist(const_cast<string&>(sailingId))) {
        cout << "Sailing already exists." << endl;
        return false;
    }

    Vessel vessel;
    if (!vessel.checkExist(vesselName)) {
        cout << "Vessel does not exist." << endl;
        return false;
    }

    double hcll = vessel.getHCLL(vesselName);
    double lcll = vessel.getLCLL(vesselName);

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
        Reservation reservation;
        reservation.removeReservationsOnSailing(sailingId, Util::reservationFile);
        return Sailing::removeSailing(sailingId);
    } else {
        return false;
    }
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
        cout << "No sailing with such ID exist" << endl;
        return;
    }

    Sailing sailing = Sailing::getSailingInfo(sailingId);

    cout << "The sailing with given id is found and listed.\n\n";
    cout << "Inquiry about sailing " << sailingId << ":\n\n";

    int totalVehicles = Reservation::getTotalReservationsOnSailing(sailingId, Util::reservationFile);
    double totalCapacity = sailing.HRL + sailing.LRL;
    double usedCapacity = totalCapacity - (sailing.HRL + sailing.LRL); // Placeholder calculation
    double percentage = (usedCapacity / totalCapacity) * 100.0;

    cout << "1) Vessel name: " << sailing.vesselName << endl;
    cout << "2) High Remaining Capacity (HRL): " << fixed << setprecision(0) << sailing.HRL << endl;
    cout << "3) Low Remaining Capacity (LRL): " << fixed << setprecision(0) << sailing.LRL << endl;
    cout << "4) Total vehicles on board: " << totalVehicles << endl;
    cout << "5) Percentage of capacity occupied: " << fixed << setprecision(0) << percentage << "%\n";
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
    while (file.read(reinterpret_cast<char*>(&sailing), Sailing::RECORD_SIZE)) {
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
            int totalVehicles = Reservation::getTotalReservationsOnSailing(s.sailingId, Util::reservationFile);
            double total = s.HRL + s.LRL;
            double used = total - (s.HRL + s.LRL); // Placeholder logic (should be real usage)
            double percent = (used / total) * 100.0;

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