//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*********************************************************
// Vehicle.h
//*********************************************************
// Purpose: Represents a binary-stored vehicle record with
// license, phone, height, and length data. Used in
// reservations.
// July 20, 2025 Version 3 - All team members
//*********************************************************

#pragma once

#include <string>
#include <fstream>

using namespace std;

// Maximum height for regular vehicles
static const float REGULAR_VEHICLE_HEIGHT = 2.0; 
// Maximum length for regular vehicles
static const float REGULAR_VEHICLE_LENGTH = 7.0; 
// Maximum length for vehicle license plates
static const int LICENSE_PLATE_LENGTH = 10; 
// Maximum length for phone numbers
static const int PHONE_LENGTH = 14; 

class Vehicle
{
public:
    //*********************************************************
    // RECORD_SIZE
    //*********************************************************
    // Total size of a vehicle record in bytes: 
    // license + phone + height + length
    //*********************************************************
    static const int RECORD_SIZE = LICENSE_PLATE_LENGTH 
                                + PHONE_LENGTH 
                                + sizeof(float) * 2;

    // Array to store vehicle license, +1 for null terminator
    char license[LICENSE_PLATE_LENGTH + 1]; 
    // Array to store phone number, +1 for null terminator
    char phone[PHONE_LENGTH + 1];      
    // Height of the vehicle     
    float height; 
    // Length of the vehicle
    float length; 

    //*********************************************************
    // Default Constructor
    //*********************************************************
    Vehicle(); // Initializes a vehicle with default values.

    //*********************************************************
    // Parameterized Constructor
    //*********************************************************
    // Initializes a vehicle with provided values.
    // in: license, phone, height, length
    //*********************************************************
    Vehicle(const string &license, const string &phone, 
            float height, float length);

    //*********************************************************
    // writeToFile
    //*********************************************************
    // Writes the vehicle record to a binary file.
    // in-out: file - binary stream to write into
    //*********************************************************
    void writeToFile(fstream &file) const;

    //*********************************************************
    // readFromFile
    //*********************************************************
    // Reads the vehicle record from a binary file.
    // in-out: file - binary stream to read from
    //*********************************************************
    void readFromFile(fstream &file);

    //*********************************************************
    // getLicense
    //*********************************************************
    // Searches for a vehicle and returns the license if found.
    // in: license
    // out: matching license or empty string
    //*********************************************************
    string getLicense(const string license) const;

    //*********************************************************
    // getHeight
    //*********************************************************
    // Gets the height of a vehicle with a given license.
    // in: license
    // out: height (rounded to 2 decimal places), or -1 if not
    // found
    //*********************************************************
    static float getHeight(const string license);

    //*********************************************************
    // getLength
    //*********************************************************
    // Gets the length of a vehicle with a given license.
    // in: license
    // out: length (rounded to 2 decimal places), or -1 if not
    // found
    //*********************************************************
    static float getLength(const string license);

    //*********************************************************
    // setLicense
    //*********************************************************
    // Sets the vehicle license.
    // in: license
    //*********************************************************
    void setLicense(string license);

    //*********************************************************
    // setHeight
    //*********************************************************
    // Sets the vehicle height.
    // in: height
    //*********************************************************
    void setHeight(float height);

    //*********************************************************
    // setLength
    //*********************************************************
    // Sets the vehicle length.
    // in: length
    //*********************************************************
    void setLength(float length);

    //*********************************************************
    // checkExist
    //*********************************************************
    // Checks if a vehicle with a given license exists in the
    // file.
    // in: license
    // out: true if found, false otherwise
    //*********************************************************
    static bool checkExist(const string &license);

    //*********************************************************
    // writeVehicle
    //*********************************************************
    // Writes a new vehicle record to the file if it doesn't
    // exist.
    // in: license, phone, height, length
    // out: true if successfully written, false otherwise
    //*********************************************************
    static bool writeVehicle(const string &license, 
                            const string &phone, 
                            float height, float length);

    //*********************************************************
    // toString
    //*********************************************************
    // Returns a formatted string representation of the vehicle.
    // out: formatted string
    //*********************************************************
    string toString() const;
};