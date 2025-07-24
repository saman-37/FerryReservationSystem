//************************************************************
// Vessel.h
//************************************************************
// Purpose: Represents a ferry vessel that holds capacity values
// used to initialize new sailings. Stored as binary data.
// July 10, 2025 Revision 1 - All team members
//************************************************************

#pragma once

using namespace std;

#include <fstream>
#include <string>

class Vessel {
    public:
        static const int NAME_LENGTH = 25; // Length of the vessel name
        static const int ID_LENGTH = 10; // Length of the vessel ID
        static const int RECORD_SIZE = NAME_LENGTH + ID_LENGTH + sizeof(double) * 2; // Size of the record in bytes

        char vesselName[NAME_LENGTH + 1]; // +1 for null terminator
        char vesselId[ID_LENGTH + 1]; // +1 for null terminator 
        double HCLL; // High Capacity Lane Length
        double LCLL; // Low Capacity Lane Length


        Vessel(); // Default Constructor
        Vessel(const string& vesselName, const string& vesselId, double HCLL, double LCLL); // in: vesselName, HCLL, LCLL

        void writeToFile(fstream& file) const; // in-out: file
        void readFromFile(fstream& file); // in-out: file

        bool checkExist(const string& vesselId); // in: vesselId
        bool writeVessel(const string& VesselName, const string& vesselId, double HCLL, double LCLL); // in: vesselName, vesselId, HCLL, LCLL
        string toString() const; // out: string

        string getName() const; // out: vesselName
        string getVesselID() const; // out: vesselId
        double getHCLL() const; // out: HCLL
        double getLCLL() const; // out: LCLL

        int getCapacity() const; // returns the ssum of HCLL and LCLL as capacity of the vessel

    };
