//************************************************************
// Vehicle.h
//************************************************************
// Purpose: Represents a binary-stored vehicle record with license,
// phone, height, and length data. Used in reservations.
// July 20, 2025 Version 3 - All team members
//************************************************************

#pragma once

#include <string>
#include <fstream>

using namespace std;

static const float REGULAR_VEHICLE_HEIGHT = 2.0;
static const float REGULAR_VEHICLE_LENGTH = 7.0;
static const int LICENSE_PLATE_LENGTH = 10;
static const int PHONE_LENGTH = 14;

class Vehicle
{

public:
    
    static const int RECORD_SIZE = LICENSE_PLATE_LENGTH + PHONE_LENGTH + sizeof(float) * 2;

    char license[LICENSE_PLATE_LENGTH + 1]; // +1 for null terminator
    char phone[PHONE_LENGTH + 1];           // +1 for null terminator
    float height;
    float length;

    Vehicle();                                                                       // Default Constructor
    Vehicle(const string &license, const string &phone, float height, float length); // in: license, phone, height, length

    void writeToFile(fstream &file) const; // in-out: file
    void readFromFile(fstream &file);      // in-out: file

    string getLicense(const string license) const; // out: license
    static float getHeight(const string license) ;  // out: height
    static float getLength(const string license); // out: length

    void setLicense(string license); // in: license
    void setHeight(float height);   // in: height
    void setLength(float length);   // in: length

    static bool checkExist(const string &license);                                                      // in: license
    static bool writeVehicle(const string &license, const string &phone, float height, float length); // in: license, phone, height, length
    string toString() const;                                                                            // out: formatted string
};
