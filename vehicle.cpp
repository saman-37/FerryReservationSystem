//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// vehicle.cpp//300
//************************************************************
// Purpose: Represents a binary-stored vehicle record with license,
// phone, height, and length data. Used in reservations.
//July 20, 2025 Revision 1 - Darpandeep Kaur
//************************************************************ 

#include "Vehicle.h"
#include "Util.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sstream>

using namespace std;

//************************************************************
// Default Constructor
// Initializes the vehicle with default values
//************************************************************
Vehicle::Vehicle() {
    strcpy(license, ""); // Initialize license to empty string
    strcpy(phone, ""); // Initialize phone to empty string
    height = 2.0f; // Initialize height to 2.0f
    length = 7.0f; // Initialize length to 7.0f
}

//************************************************************
// Parameterized Constructor
// Initializes the vehicle with provided values
// in: license, phone, height, length
//************************************************************
Vehicle::Vehicle(const string& license, const string& phone, float height, float length) {
    strncpy(this->license, license.c_str(), LICENSE_PLATE_LENGTH); // Copy license string
    this->license[LICENSE_PLATE_LENGTH] = '\0'; // Null-terminate

    strncpy(this->phone, phone.c_str(), PHONE_LENGTH); // Copy phone string
    this->phone[PHONE_LENGTH] = '\0'; // Null-terminate

    this->height = height; // Set height
    this->length = length; // Set length
}

//************************************************************
// Writes the vehicle record to a binary file
// in-out: file - binary file stream
//************************************************************
void Vehicle::writeToFile(fstream& file) const {
    if (file.is_open()) {
        file.write(license, LICENSE_PLATE_LENGTH + 1); // Write license
        file.write (phone, PHONE_LENGTH + 1); // Write phone
        file.write(reinterpret_cast<const char*>(&height), sizeof(height)); // Write height
        file.write(reinterpret_cast<const char*>(&length), sizeof(length)); // Write length
    }
}

//************************************************************
// Reads the vehicle record from a binary file
// in-out: file - binary file stream
//************************************************************
void Vehicle::readFromFile(fstream& file) {
    if (file.is_open()){
        file.read(license, LICENSE_PLATE_LENGTH + 1); // Read license
        file.read(phone, PHONE_LENGTH + 1); // Read phone
        file.read(reinterpret_cast<char*>(&height), sizeof(height)); // Read height
        file.read(reinterpret_cast<char*>(&length), sizeof(length)); // Read length
    }
}

//************************************************************
// Checks if a vehicle with the given license exists
// in: license - vehicle license plate
// out: returns true if exists, false otherwise
//************************************************************
bool Vehicle::checkExist(const string& license) {
    Util::vehicleFile.clear(); // Clear any existing flags
    Util::vehicleFile.seekg(0, ios::beg); // Move to the beginning

    Vehicle vehicle; // Create a Vehicle object
    while (Util::vehicleFile.read(reinterpret_cast<char*>(&vehicle), RECORD_SIZE)) {
        if (strcmp(vehicle.license, license.c_str()) == 0) {
            return true; // Vehicle with the given license exists
        }
    }
    return false; // Vehicle with the given license does not exist
}

//************************************************************
// Writes a new vehicle record to the file
// in: license - vehicle license plate, phone, height, length 
// out: returns true if written successfully, false otherwise
//************************************************************
bool Vehicle::writeVehicle(const string& license, const string& phone, double height, double length){
    if (checkExist(license)){
        cout << "Vehicle with License " << license << "already exists." << endl;
        return false; // Vehicle already exists
    }

    Vehicle vehicle(license, phone, height, length); // Create a Vehicle object
    Util::vehicleFile.clear(); // Clear any existing flags
    Util::vehicleFile.seekp(0, ios::end); // Move to the end
    vehicle.writeToFile(Util::vehicleFile); // Write the vehicle record to the file
    Util::vehicleFile.flush(); // Ensure data is written to disk
}

string Vehicle::toString() const {
    stringstream ss; // Create a string stream for formatting
    ss << "License: " << license 
        << ", Phone: " << phone
        << ", Height: " << height
        << "m, Length: " << length << "m";
    return ss.str(); // Return the formatted string

}

//************************************************************
// Getters
//************************************************************
string Vehicle::getLicense() const {
    return string(license); // Return license as a string
}

string Vehicle::getPhone() const {
    return string(phone); // Return phone as a string
}

double Vehicle::getHeight() const {
    return height; // Return height
}

double Vehicle::getLength() const {
    return length; // Return length
}

//************************************************************
// Setters
//************************************************************

void Vehicle::setLicense(string license) {
    strncpy(this->license, license.c_str(), LICENSE_PLATE_LENGTH); // Copy license string
    this->license[LICENSE_PLATE_LENGTH] = '\0'; // Null-terminate
}

void Vehicle::setPhone(string phone) {
    strncpy(this->phone, phone.c_str(), PHONE_LENGTH); // Copy phone string
    this->phone[PHONE_LENGTH] = '\0'; // Null-terminate
}

void Vehicle::setHeight(double height) {
    this->height = height; // Set height
}

void Vehicle::setLength(double length) {
    this->length = length; // Set length
}
