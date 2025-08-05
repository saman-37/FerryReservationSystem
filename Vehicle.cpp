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
    height = REGULAR_VEHICLE_HEIGHT; // Default height for regular vehicles
    length = REGULAR_VEHICLE_LENGTH; // Default length for regular vehicles
}

//************************************************************
// Parameterized Constructor
// Initializes a vehicle with provided values.
// in: license, phone, height, length
//************************************************************
Vehicle::Vehicle(const string &license, const string &phone, float height, float length)
{
    strncpy(this->license, license.c_str(), LICENSE_PLATE_LENGTH); // Set license from input
    this->license[LICENSE_PLATE_LENGTH] = '\0'; // Null-terminate the license string

    strncpy(this->phone, phone.c_str(), PHONE_LENGTH); // Set phone from input
    this->phone[PHONE_LENGTH] = '\0'; // Null-terminate the phone string

    this->height = height; // Set height from input
    this->length = length; // Set length from input
}

//************************************************************
// Writes a vehicle record to binary file.
// in-out: file - binary stream to write into
//************************************************************
void Vehicle::writeToFile(fstream &file) const
{
    if (file.is_open()) // Check if the file is open for writing
    {
        file.write(license, LICENSE_PLATE_LENGTH + 1); // Write license string to file
        file.write(phone, PHONE_LENGTH + 1); // Write phone string to file
        file.write(reinterpret_cast<const char *>(&height), sizeof(float)); // Write height to file
        file.write(reinterpret_cast<const char *>(&length), sizeof(float)); // Write length to file
    }
    else
    {
        cout << "Error opening file for writing." << endl; // Error message if file is not open
    }
}

//************************************************************
// Reads a vehicle record from binary file.
// in-out: file - binary stream to read from
//************************************************************
void Vehicle::readFromFile(fstream &file)
{
    if (file.is_open()) // Check if the file is open for reading
    {
        file.read(license, LICENSE_PLATE_LENGTH + 1); // Read license string from file
        file.read(phone, PHONE_LENGTH + 1); // Read phone string from file
        file.read(reinterpret_cast<char *>(&height), sizeof(height)); // Read height from file
        file.read(reinterpret_cast<char *>(&length), sizeof(length)); // Read length from file
    }
}

//************************************************************
// Checks if a vehicle with a given license exists in the file.
// in: license
// out: true if found, false otherwise
//************************************************************
bool Vehicle::checkExist(const string &license)
{
    if (Util::vehicleFile.is_open()) // Check if the vehicle file is open
    {
        Util::vehicleFile.clear(); // Clear any error flags
        Util::vehicleFile.seekg(0, ios::beg); // Move to the beginning of the file

        Vehicle vehicle; // Create a Vehicle instance to read records
        while (!Util::vehicleFile.eof()) // Loop until end of file
        {
            vehicle.readFromFile(Util::vehicleFile); // Read a vehicle record

            if (strcmp(vehicle.license, license.c_str()) == 0) // Check if the license matches
            {
                return true; // Vehicle found, return true
            }
        }
        return false; // Not found, safe to create new vehicle
    }
    else
    {
        cout << "Error opening vessel file." << endl; // Error message if file is not open
        return false; // Return false indicating failure
    }
}

//************************************************************
// Writes a new vehicle record to the file if it doesn't exist.
// in: license, phone, height, length
// out: true if successfully written, false otherwise
//************************************************************
bool Vehicle::writeVehicle(const string &license, const string &phone, float height, float length)
{
    Vehicle vehicle(license, phone, height, length); // Create a Vehicle instance with provided values
    Util::vehicleFile.clear(); // Clear any error flags
    Util::vehicleFile.seekp(0, ios::end); // Move to the end of the file
    vehicle.writeToFile(Util::vehicleFile); // Write the vehicle record to the file
    Util::vehicleFile.flush(); // Flush the file to ensure data is written
    return true; // Return true indicating success
}

//************************************************************
// Returns a formatted string representation of the vehicle.
// out: formatted string
//************************************************************
string Vehicle::toString() const
{
    stringstream ss; // Create a string stream for formatting
    ss << "License: " << license // Format the string with vehicle details
       << ", Phone: " << phone
       << ", Height: " << height
       << "m, Length: " << length << "m";
    return ss.str(); // Return the formatted string
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
    Util::vehicleFile.clear(); // Clear any error flags
    Util::vehicleFile.seekg(0, ios::beg); // Move to the beginning of the file

    Vehicle vehicle; // Create a Vehicle instance to read records
    while (Util::vehicleFile.read(reinterpret_cast<char *>(&vehicle), RECORD_SIZE)) // Loop through records
    {
        if (strcmp(vehicle.license, license.c_str()) == 0) // Check if the license matches
        {
            cout << "License: " << license << " found." << endl; // Output found message
            return license; // Return the matching license
        }
    }
    cout << "License: " << license << " not found." << endl; // Output not found message
    return ""; // Return empty string if not found
}

//************************************************************
// Gets the height of a vehicle with a given license.
// in: license
// out: height (rounded to 2 decimal places), or -1 if not found
//************************************************************
float Vehicle::getHeight(string license)
{
    if (!Util::vehicleFile.is_open()) // Check if the vehicle file is open
    {
        cout << "Vehicle file is not open." << endl; // Error message if file is not open
        return -1; // Return -1 to indicate error
    }

    Util::vehicleFile.clear(); // Clear any error flags
    Util::vehicleFile.seekg(0, ios::beg); // Move to the beginning of the file

    Vehicle vehicle; // Create a Vehicle instance to read records

    while (!Util::vehicleFile.eof()) // Loop until end of file
    {
        vehicle.readFromFile(Util::vehicleFile); // Read a vehicle record
        if (strcmp(vehicle.license, license.c_str()) == 0) // Check if the license matches
        {
            return vehicle.height; // Return the height if found
        }
    }

    cout << "Vehicle with license " << license << " not found." << endl; // Output not found message
    return -1; // Return -1 if not found
}

//************************************************************
// Gets the length of a vehicle with a given license.
// in: license
// out: length (rounded to 2 decimal places), or -1 if not found
//************************************************************
float Vehicle::getLength(string license)
{
    if (!Util::vehicleFile.is_open()) // Check if the vehicle file is open
    {
        cout << "Vehicle file is not open." << endl; // Error message if file is not open
        return -1; // Return -1 to indicate error
    }

    Util::vehicleFile.clear(); // Clear any error flags
    Util::vehicleFile.seekg(0, ios::beg); // Move to the beginning of the file

    Vehicle vehicle; // Create a Vehicle instance to read records

    while (!Util::vehicleFile.eof()) // Loop until end of file
    {
        vehicle.readFromFile(Util::vehicleFile); // Read a vehicle record
        if (strcmp(vehicle.license, license.c_str()) == 0) // Check if the license matches
        {
            return vehicle.length; // Return the length if found
        }
    }

    cout << "Vehicle with license " << license << " not found." << endl; // Output not found message
    return -1; // Return -1 if not found
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
    strncpy(this->license, license.c_str(), LICENSE_PLATE_LENGTH); // Set license from input
    this->license[LICENSE_PLATE_LENGTH] = '\0'; // Null-terminate the license string
}

//************************************************************
// Sets the vehicle height.
// in: height
//************************************************************
void Vehicle::setHeight(float height)
{
    this->height = height; // Set height from input
}

//************************************************************
// Sets the vehicle length.
// in: length
//************************************************************
void Vehicle::setLength(float length)
{
    this->length = length; // Set length from input
}
