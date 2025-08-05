//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// Vehicle.cpp
//************************************************************
// Purpose: Represents a binary-stored vehicle record with license,
// phone, height, and length data. Used in reservations.
// July 20, 2025 Version 2 - Darpandeep Kaur
//************************************************************

#include "Vehicle.h"
#include "Util.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

//************************************************************
// Default Constructor
// Initializes a vehicle with default values.
//************************************************************
Vehicle::Vehicle()
{
    strcpy(license, ""); // Set license to empty string
    strcpy(phone, "");   // Set phone to empty string
    height = REGULAR_VEHICLE_HEIGHT;       // Default height
    length = REGULAR_VEHICLE_LENGTH;       // Default length
}

//************************************************************
// Parameterized Constructor
// Initializes a vehicle with provided values.
// in: license, phone, height, length
//************************************************************
Vehicle::Vehicle(const string &license, const string &phone, float height, float length)
{
    strncpy(this->license, license.c_str(), LICENSE_PLATE_LENGTH); // Set license
    this->license[LICENSE_PLATE_LENGTH] = '\0';                    // Null-terminate

    strncpy(this->phone, phone.c_str(), PHONE_LENGTH); // Set phone
    this->phone[PHONE_LENGTH] = '\0';                  // Null-terminate

    this->height = height; // Set height
    this->length = length; // Set length
}

//************************************************************
// Writes a vehicle record to binary file.
// in-out: file - binary stream to write into
//************************************************************
void Vehicle::writeToFile(fstream &file) const
{
    if (file.is_open())
    {
        file.write(license, LICENSE_PLATE_LENGTH + 1);
        file.write(phone, PHONE_LENGTH + 1);
        file.write(reinterpret_cast<const char *>(&height), sizeof(float));
        file.write(reinterpret_cast<const char *>(&length), sizeof(float));
    }
    else
    {
        cout << "Error opening file for writing." << endl;
    }
}

//************************************************************
// Reads a vehicle record from binary file.
// in-out: file - binary stream to read from
//************************************************************
void Vehicle::readFromFile(fstream &file)
{
    if (file.is_open())
    {
        file.read(license, LICENSE_PLATE_LENGTH + 1);
        file.read(phone, PHONE_LENGTH + 1);
        file.read(reinterpret_cast<char *>(&height), sizeof(height));
        file.read(reinterpret_cast<char *>(&length), sizeof(length));
    }
}

//************************************************************
// Checks if a vehicle with a given license exists in the file.
// in: license
// out: true if found, false otherwise
//************************************************************
bool Vehicle::checkExist(const string &license)
{
    if (Util::vehicleFile.is_open())
    {
        Util::vehicleFile.clear();
        // not in good position, so we need to seek to the beginning
        Util::vehicleFile.seekg(0, ios::beg);

        Vehicle vehicle;
        while (!Util::vehicleFile.eof())
        {
            vehicle.readFromFile(Util::vehicleFile);

            if (strcmp(vehicle.license, license.c_str()) == 0)
            {
                return true; // Vessel found end here
            }
        }
        return false; // Not found, safe to create new vessel
    }
    else
    {
        cout << "Error opening vessel file." << endl;
        return false;
    }
}

//************************************************************
// Writes a new vehicle record to the file if it doesn't exist.
// in: license, phone, height, length
// out: true if successfully written, false otherwise
//************************************************************
bool Vehicle::writeVehicle(const string &license, const string &phone, float height, float length)
{
   
    Vehicle vehicle(license, phone, height, length);
    Util::vehicleFile.clear();
    Util::vehicleFile.seekp(0, ios::end);
    vehicle.writeToFile(Util::vehicleFile);
    Util::vehicleFile.flush();
    return true;
}

//************************************************************
// Returns a formatted string representation of the vehicle.
// out: formatted string
//************************************************************
string Vehicle::toString() const
{
    stringstream ss;
    ss << "License: " << license
       << ", Phone: " << phone
       << ", Height: " << height
       << "m, Length: " << length << "m";
    return ss.str();
}

//************************************************************
// Getters
//************************************************************

//************************************************************
// Searches for a vehicle and returns the license if found.
// in: license
// out: matching license or empty string
//************************************************************
string Vehicle::getLicense(string license) const
{
    Util::vehicleFile.clear();
    Util::vehicleFile.seekg(0, ios::beg);

    Vehicle vehicle;
    while (Util::vehicleFile.read(reinterpret_cast<char *>(&vehicle), RECORD_SIZE))
    {
        if (strcmp(vehicle.license, license.c_str()) == 0)
        {
            cout << "License: " << license << " found." << endl;
            return license;
        }
    }
    cout << "License: " << license << " not found." << endl;
    return "";
}

//************************************************************
// Gets the height of a vehicle with a given license.
// in: license
// out: height (rounded to 2 decimal places), or -1 if not found
//************************************************************
float Vehicle::getHeight(string license)
{
    if (!Util::vehicleFile.is_open())
    {
        cout << "Vehicle file is not open." << endl;
        return -1;
    }

    Util::vehicleFile.clear();
    Util::vehicleFile.seekg(0, ios::beg);

    Vehicle vehicle;

    while (!Util::vehicleFile.eof())
    {
        vehicle.readFromFile(Util::vehicleFile);
        if (strcmp(vehicle.license, license.c_str()) == 0)
        {
            return vehicle.height; // Vessel found end here
        }
    }

    cout << "Vehicle with license " << license << " not found." << endl;
    return -1;
}

//************************************************************
// Gets the length of a vehicle with a given license.
// in: license
// out: length (rounded to 2 decimal places), or -1 if not found
//************************************************************
float Vehicle::getLength(string license)
{
    if (!Util::vehicleFile.is_open())
    {
        cout << "Vehicle file is not open." << endl;
        return -1;
    }

    Util::vehicleFile.clear();
    Util::vehicleFile.seekg(0, ios::beg);

    Vehicle vehicle;

    while (!Util::vehicleFile.eof())
    {
        vehicle.readFromFile(Util::vehicleFile);
        if (strcmp(vehicle.license, license.c_str()) == 0)
        {
            return vehicle.length; // Vessel found end here
        }
    }

    cout << "Vehicle with license " << license << " not found." << endl;
    return -1;
}

//************************************************************
// Setters
//************************************************************

//************************************************************
// Sets the vehicle license.
// in: license
//************************************************************
void Vehicle::setLicense(string license)
{
    strncpy(this->license, license.c_str(), LICENSE_PLATE_LENGTH);
    this->license[LICENSE_PLATE_LENGTH] = '\0';
}

//************************************************************
// Sets the vehicle height.
// in: height
//************************************************************
void Vehicle::setHeight(float height)
{
    this->height = height;
}

//************************************************************
// Sets the vehicle length.
// in: length
//************************************************************
void Vehicle::setLength(float length)
{
    this->length = length;
}
