//************************************************************
// sailing.cpp
//************************************************************
// Purpose: Implementation for Sailing class representing a ferry sailing.
// July 21, 2025 Revision 1 - Team 18
//************************************************************

#include "sailing.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

Sailing::Sailing() {
    memset(sailingId, 0, sizeof(sailingId));
    memset(vesselName, 0, sizeof(vesselName));
    HRL = 0.0;
    LRL = 0.0;
}

Sailing::Sailing(const string& id, const string& vName, double hrl, double lrl) {
    open(id, vName, hrl, lrl);
}

void Sailing::open(const string& id, const string& vName, double hrl, double lrl) {
    strncpy(sailingId, id.c_str(), SAILING_ID_LENGTH);
    sailingId[SAILING_ID_LENGTH] = '\0';

    strncpy(vesselName, vName.c_str(), VESSEL_NAME_LENGTH);
    vesselName[VESSEL_NAME_LENGTH] = '\0';

    HRL = hrl;
    LRL = lrl;
}

void Sailing::writeToFile(fstream& file) const {
    file.write(reinterpret_cast<const char*>(this), RECORD_SIZE);
}

void Sailing::readFromFile(fstream& file) {
    file.read(reinterpret_cast<char*>(this), RECORD_SIZE);
}

string Sailing::toString() const {
    ostringstream out;
    out << "Sailing ID: " << sailingId << "\n"
        << "Vessel Name: " << vesselName << "\n"
        << fixed << setprecision(1)
        << "High Remaining Length: " << HRL << " m\n"
        << "Low Remaining Length: " << LRL << " m\n";
    return out.str();
}

Sailing Sailing::getSailingInfo(const string& sailingId) {
    fstream file("sailing.dat", ios::in | ios::binary);
    Sailing sailing;
    while (file.read(reinterpret_cast<char*>(&sailing), RECORD_SIZE)) {
        if (strcmp(sailing.sailingId, sailingId.c_str()) == 0) {
            file.close();
            return sailing;
        }
    }
    file.close();
    return Sailing(); // return empty/default sailing
}

bool Sailing::checkExist(string& sailingId) {
    fstream file("sailing.dat", ios::in | ios::binary);
    Sailing sailing;
    while (file.read(reinterpret_cast<char*>(&sailing), RECORD_SIZE)) {
        if (strcmp(sailing.sailingId, sailingId.c_str()) == 0) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool Sailing::writeSailing(string& sailingId, string& vesselName, double HRL, double LRL) {
    fstream file("sailing.dat", ios::out | ios::app | ios::binary);
    if (!file.is_open()) return false;
    Sailing s(sailingId, vesselName, HRL, LRL);
    s.writeToFile(file);
    file.close();
    return true;
}

bool Sailing::removeSailing(string& sailingId) {
    fstream file("sailing.dat", ios::in | ios::binary);
    fstream temp("temp.dat", ios::out | ios::binary);
    Sailing s;
    bool removed = false;

    while (file.read(reinterpret_cast<char*>(&s), RECORD_SIZE)) {
        if (strcmp(s.sailingId, sailingId.c_str()) != 0) {
            temp.write(reinterpret_cast<char*>(&s), RECORD_SIZE);
        } else {
            removed = true;
        }
    }

    file.close();
    temp.close();
    remove("sailing.dat");
    rename("temp.dat", "sailing.dat");
    return removed;
}
