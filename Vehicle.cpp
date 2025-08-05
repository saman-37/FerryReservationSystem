//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*********************************************************
// Vehicle.cpp
//*********************************************************
// Purpose: Represents a binary-stored vehicle record with
// license, phone, height, and length data. Used in
// reservations.
// July 20, 2025 Version 2 - Darpandeep Kaur
//*********************************************************

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
    // Set license to empty string
    strcpy(license, ""); 
    // Set phone to empty string
    strcpy(phone, "");   
    // Default height for regular vehicles
    height = REGULAR_VEHICLE_HEIGHT; 
    // Default length for regular vehicles
    length = REGULAR_VEHICLE_LENGTH; 
}

//************************************************************
// Parameterized Constructor
// Initializes a vehicle with provided values.
// in: license, phone, height, length
//************************************************************
Vehicle::Vehicle(const string &license, const string &phone, 
                float height, float length)
{
    // Set license from input
    strncpy(this->license, license.c_str(), 
            LICENSE_PLATE_LENGTH); 

    // Null-terminate the license string
    this->license[LICENSE_PLATE_LENGTH] = '\0'; 

    // Set phone from input
    strncpy(this->phone, phone.c_str(), PHONE_LENGTH); 
    // Null-terminate the phone string
    this->phone[PHONE_LENGTH] = '\0'; 

    this->height = height; // Set height from input
    this->length = length; // Set length from input
}

//************************************************************
// Writes a vehicle record to binary file.
// in-out: file - binary stream to write into
//************************************************************
void Vehicle::writeToFile(fstream &file) const
{
    // Check if the file is open for writing
    if (file.is_open()) 
    {
        // Write license string to file
        file.write(license, LICENSE_PLATE_LENGTH + 1); 
        // Write phone string to file
        file.write(phone, PHONE_LENGTH + 1); 
        // Write height to file
        file.write(reinterpret_cast<const char *>(&height), 
                        sizeof(float)); 
        // Write length to file
        file.write(reinterpret_cast<const char *>(&length), 
                        sizeof(float)); 
    }
    else
    {
        // Error message if file is not open
        cout << "Error opening file for writing." << endl; 
    }
}

//************************************************************
// Reads a vehicle record from binary file.
// in-out: file - binary stream to read from
//************************************************************
void Vehicle::readFromFile(fstream &file)
{
    // Check if the file is open for reading
    if (file.is_open()) 
    {
        // Read license string from file
        file.read(license, LICENSE_PLATE_LENGTH + 1); 
        // Read phone string from file
        file.read(phone, PHONE_LENGTH + 1); 
        // Read height from file
        file.read(reinterpret_cast<char *>(&height), 
                        sizeof(height)); 
        // Read length from file
        file.read(reinterpret_cast<char *>(&length), 
                        sizeof(length)); 
    }
}

//************************************************************
// Checks if a vehicle with a given license exists in the file.
// in: license
// out: true if found, false otherwise
//************************************************************
bool Vehicle::checkExist(const string &license)
{
    // Check if the vehicle file is open
    if (Util::vehicleFile.is_open()) 
    {
        // Clear any error flags
        Util::vehicleFile.clear(); 
        // Move to the beginning of the file
        Util::vehicleFile.seekg(0, ios::beg); 

        // Create a Vehicle instance to read records
        Vehicle vehicle; 
        // Loop until end of file
        while (!Util::vehicleFile.eof()) 
        {
            // Read a vehicle record
            vehicle.readFromFile(Util::vehicleFile); 

            // Check if the license matches
            if (strcmp(vehicle.license, license.c_str()) == 0) 
            {
                // Vehicle found, return true
                return true; 
            }
        }
        // Not found, safe to create new vehicle
        return false; 
    }
    else
    {
        // Error message if file is not open
        cout << "Error opening vessel file." << endl; 
        // Return false indicating failure
        return false; 
    }
}

//************************************************************
// Writes a new vehicle record to the file if it doesn't exist.
// in: license, phone, height, length
// out: true if successfully written, false otherwise
//************************************************************
bool Vehicle::writeVehicle(const string &license, 
                           const string &phone, 
                           float height, 
                           float length)
{
    // Create a Vehicle instance with provided values
    Vehicle vehicle(license, phone, height, length); 
    // Clear any error flags
    Util::vehicleFile.clear(); 
    // Move to the end of the file
    Util::vehicleFile.seekp(0, ios::end); 
    // Write the vehicle record to the file
    vehicle.writeToFile(Util::vehicleFile); 
    // Flush the file to ensure data is written
    Util::vehicleFile.flush(); 
    // Return true indicating success
    return true; 
}

//************************************************************
// Returns a formatted string representation of the vehicle.
// out: formatted string
//************************************************************
string Vehicle::toString() const
{
    // Create a string stream for formatting
    stringstream ss; 
    // Format the string with vehicle details
    ss << "License: " << license 
       << ", Phone: " << phone
       << ", Height: " << height
       << "m, Length: " << length << "m";
    // Return the formatted string
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
    // Clear any error flags
    Util::vehicleFile.clear(); 
    // Move to the beginning of the file
    Util::vehicleFile.seekg(0, ios::beg); 

    // Create a Vehicle instance to read records
    Vehicle vehicle; 
    // Loop through records
    while (Util::vehicleFile.read(reinterpret_cast
            <char *>(&vehicle), RECORD_SIZE)) 
    {
        // Check if the license matches
        if (strcmp(vehicle.license, license.c_str()) == 0) 
        {
            // Output found message
            cout << "License: " << license << " found." 
                << endl; 
            // Return the matching license
            return license; 
        }
    }
    // Output not found message
    cout << "License: " << license << " not found." 
        << endl; 
    // Return empty string if not found
    return ""; 
}

//************************************************************
// Gets the height of a vehicle with a given license.
// in: license
// out: height (rounded to 2 decimal places), or -1 if not found
//************************************************************
float Vehicle::getHeight(string license)
{
    // Check if the vehicle file is open
    if (!Util::vehicleFile.is_open()) 
    {
        // Error message if file is not open
        cout << "Vehicle file is not open." << endl; 
        // Return -1 to indicate error
        return -1; 
    }

    // Clear any error flags
    Util::vehicleFile.clear(); 
    // Move to the beginning of the file
    Util::vehicleFile.seekg(0, ios::beg); 

    // Create a Vehicle instance to read records
    Vehicle vehicle; 

    // Loop until end of file
    while (!Util::vehicleFile.eof()) 
    {
        // Read a vehicle record
        vehicle.readFromFile(Util::vehicleFile); 
        // Check if the license matches
        if (strcmp(vehicle.license, license.c_str()) == 0) 
        {
            // Return the height if found
            return vehicle.height; 
        }
    }

    // Output not found message
    cout << "Vehicle with license " << license 
            << " not found." << endl; 
    // Return -1 if not found
    return -1; 
}

//************************************************************
// Gets the length of a vehicle with a given license.
// in: license
// out: length (rounded to 2 decimal places), or -1 if not found
//************************************************************
float Vehicle::getLength(string license)
{
    // Check if the vehicle file is open
    if (!Util::vehicleFile.is_open()) 
    {
        // Error message if file is not open
        cout << "Vehicle file is not open." << endl; 
        return -1; // Return -1 to indicate error
    }

    // Clear any error flags
    Util::vehicleFile.clear(); 
    // Move to the beginning of the file
    Util::vehicleFile.seekg(0, ios::beg); 

    // Create a Vehicle instance to read records
    Vehicle vehicle; 

    // Loop until end of file
    while (!Util::vehicleFile.eof()) 
    {
        // Read a vehicle record
        vehicle.readFromFile(Util::vehicleFile); 
        // Check if the license matches
        if (strcmp(vehicle.license, license.c_str()) == 0) 
        {
            // Return the length if found
            return vehicle.length; 
        }
    }

    // Output not found message
    cout << "Vehicle with license " << license 
        << " not found." << endl; 
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
    // Set license from input
    strncpy(this->license, license.c_str(), 
                LICENSE_PLATE_LENGTH); 
    
    // Null-terminate the license string
    this->license[LICENSE_PLATE_LENGTH] = '\0'; 
}

//************************************************************
// Sets the vehicle height.
// in: height
//************************************************************
void Vehicle::setHeight(float height)
{
    // Set height from input
    this->height = height; 
}

//************************************************************
// Sets the vehicle length.
// in: length
//************************************************************
void Vehicle::setLength(float length)
{
    // Set length from input
    this->length = length; 
}
