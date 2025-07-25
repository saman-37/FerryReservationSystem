//************************************************************
// Sailing.cpp
//************************************************************
// Purpose: Implementation for Sailing class representing a ferry sailing.
// July 21, 2025 Revision 1 - Team 18
//************************************************************

#include "Sailing.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

Sailing::Sailing()
{
    memset(sailingId, 0, sizeof(sailingId));
    memset(vesselName, 0, sizeof(vesselName));
    HRL = 0.0;
    LRL = 0.0;
}

// Ensure this matches the declaration in Sailing.h
Sailing::Sailing(const char* sailingId, const char* vesselName, double HRL, double LRL) {
    strncpy(this->sailingId, sailingId, SAILING_ID_LENGTH - 1);
    this->sailingId[SAILING_ID_LENGTH - 1] = '\0';

    strncpy(this->vesselName, vesselName, VESSEL_NAME_LENGTH - 1);
    this->vesselName[VESSEL_NAME_LENGTH - 1] = '\0';

    this->HRL = HRL;
    this->LRL = LRL;
}
void Sailing::open(const string& id, const string& vName, double hrl, double lrl) {
    strncpy(sailingId, id.c_str(), SAILING_ID_LENGTH);
    sailingId[SAILING_ID_LENGTH] = '\0';

    strncpy(vesselName, vName.c_str(), VESSEL_NAME_LENGTH);
    vesselName[VESSEL_NAME_LENGTH] = '\0';

    HRL = hrl;
    LRL = lrl;
}

void Sailing::writeToFile(fstream &file) const
{
    file.write(reinterpret_cast<const char *>(this), RECORD_SIZE);
}

void Sailing::readFromFile(fstream &file)
{
    file.read(reinterpret_cast<char *>(this), RECORD_SIZE);
}

#include "Sailing.h"
#include <fstream>
#include <cstring> // for strcmp if needed

bool Sailing::searchForSailing(const string &sailingId, Sailing &foundSailing)
{
    ifstream file("sailing.dat", ios::in | ios::binary);
    if (!file)
    {
        cerr << "Could not open sailing.dat for reading." << endl;
        return false;
    }

    Sailing temp;
    while (file.read(reinterpret_cast<char *>(&temp), sizeof(Sailing)))
    {
        if (strcmp(temp.sailingId, sailingId.c_str()) == 0)
        {
            foundSailing = temp; // Copy found object into reference
            file.close();
            return true;
        }
    }

    file.close();
    return false; // Not found
}

<<<<<<< HEAD
Sailing Sailing::getSailingInfo(const string& sailingId) {
=======
string Sailing::toString() const
{
    ostringstream out;
    out << "Sailing ID: " << sailingId << "\n"
        << "Vessel Name: " << vesselName << "\n"
        << fixed << setprecision(1)
        << "High Remaining Length: " << HRL << " m\n"
        << "Low Remaining Length: " << LRL << " m\n";
    return out.str();
}

Sailing Sailing::getSailingInfo(const string &sailingId)
{
>>>>>>> fb57e86e11e1bd8b21ef6a2a1808a055f0606f79
    fstream file("sailing.dat", ios::in | ios::binary);
    Sailing sailing;
    while (file.read(reinterpret_cast<char *>(&sailing), RECORD_SIZE))
    {
        if (strcmp(sailing.sailingId, sailingId.c_str()) == 0)
        {
            file.close();
            return sailing;
        }
    }
    file.close();
    return Sailing(); // return empty/default sailing
}

<<<<<<< HEAD
bool Sailing::checkExist(string sailingId) {
=======
bool Sailing::checkExist(string &sailingId)
{
>>>>>>> fb57e86e11e1bd8b21ef6a2a1808a055f0606f79
    fstream file("sailing.dat", ios::in | ios::binary);
    Sailing sailing;
    while (file.read(reinterpret_cast<char *>(&sailing), RECORD_SIZE))
    {
        if (strcmp(sailing.sailingId, sailingId.c_str()) == 0)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool Sailing::writeSailing(string &sailingId, string &vesselName, double HRL, double LRL)
{
    fstream file("sailing.dat", ios::out | ios::app | ios::binary);
<<<<<<< HEAD
    if (!file.is_open()) return false;
    Sailing s(sailingId.c_str(), vesselName.c_str(), HRL, LRL);
=======
    if (!file.is_open())
        return false;
    Sailing s(sailingId, vesselName, HRL, LRL);
>>>>>>> fb57e86e11e1bd8b21ef6a2a1808a055f0606f79
    s.writeToFile(file);
    file.close();
    return true;
}

<<<<<<< HEAD
bool Sailing::removeSailing(string sailingId) {
=======
bool Sailing::removeSailing(string &sailingId)
{
>>>>>>> fb57e86e11e1bd8b21ef6a2a1808a055f0606f79
    fstream file("sailing.dat", ios::in | ios::binary);
    fstream temp("temp.dat", ios::out | ios::binary);
    Sailing s;
    bool removed = false;

    while (file.read(reinterpret_cast<char *>(&s), RECORD_SIZE))
    {
        if (strcmp(s.sailingId, sailingId.c_str()) != 0)
        {
            temp.write(reinterpret_cast<char *>(&s), RECORD_SIZE);
        }
        else
        {
            removed = true;
        }
    }

    file.close();
    temp.close();
    remove("sailing.dat");
    rename("temp.dat", "sailing.dat");
    return removed;
}
