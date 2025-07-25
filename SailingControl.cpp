//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// SailingControl.cpp
//************************************************************
// Purpose: Mid-level control module for sailing operations.
// July 25, 2025 Revision 2 - Darpandeep Kaur
//************************************************************

#include "SailingControl.h"
#include "Sailing.h"
#include "Reservation.h"
#include "Vessel.h"
#include "Util.h"
#include <iostream>
#include <iomanip>
using namespace std;

SailingControl::SailingControl() {
    // Default constructor
}

//************************************************************
// Creates a sailing record if it doesn't exist
// in: sailingId, vesselName
// out: true if successful
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

    double hcll = vessel.getHCLL();
    double lcll = vessel.getLCLL();
    return Sailing::writeSailing(const_cast<string&>(sailingId), const_cast<string&>(vesselName), hcll, lcll);
}

//************************************************************
// Deletes a sailing and all its reservations
// in: sailingId
// out: true if successful
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
// Queries a sailing and prints details
// in: sailingId
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
    double usedCapacity = totalCapacity - (sailing.HRL + sailing.LRL); // placeholder
    double percentage = (usedCapacity / totalCapacity) * 100.0;

    cout << "1) Vessel name: " << sailing.vesselName << endl;
    cout << "2) High Remaining Capacity (HRL): " << fixed << setprecision(0) << sailing.HRL << endl;
    cout << "3) Low Remaining Capacity (LRL): " << fixed << setprecision(0) << sailing.LRL << endl;
    cout << "4) Total vehicles on board: " << totalVehicles << endl;
    cout << "5) Percentage of capacity occupied: " << fixed << setprecision(0) << percentage << "%\n";
}

//************************************************************
// Prints a report of all sailings
//************************************************************
void SailingControl::printSailingReport() {
    fstream file("sailing.dat", ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Unable to open sailing.dat for reading." << endl;
        return;
    }

    vector<string> sailingIds;
    Sailing sailing;

    while (file.read(reinterpret_cast<char*>(&sailing), Sailing::RECORD_SIZE)) {
        sailingIds.push_back(string(sailing.sailingId));
    }
    file.close();

    if (sailingIds.empty()) {
        cout << "No sailings available to display." << endl;
        return;
    }

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
    while (count < sailingIds.size()) {
        size_t batchEnd = min(count + 5, sailingIds.size());

        for (size_t i = count; i < batchEnd; ++i) {
            Sailing s = Sailing::getSailingInfo(sailingIds[i]);

            string date = sailingIds[i].substr(sailingIds[i].find('-') + 1); // e.g., 07-11
            int totalVehicles = Reservation::getTotalReservationsOnSailing(s.sailingId, Util::reservationFile);
            double total = s.HRL + s.LRL;
            double used = total - (s.HRL + s.LRL); // placeholder
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

        cout << "\nShow more sailings? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (tolower(choice) != 'y') break;
    }
}