//************************************************************
// vehicle.h
//************************************************************
// Purpose: Represents a binary-stored vehicle record with license,
// phone, height, and length data. Used in reservations.
//************************************************************

#pragma once

#include <string>
#include <fstream>

class Vehicle {

    public:
        static const int LICENSE_PLATE_LENGTH = 10;
        static const int PHONE_LENGTH = 10;
        static const int RECORD_SIZE = LICENSE_PLATE_LENGTH + PHONE_LENGTH + sizeof(float) * 2;

        char license[LICENSE_PLATE_LENGTH + 1]; // +1 for null terminator
        char phone[PHONE_LENGTH + 1]; // +1 for null terminator
        float height;
        float length;
        
        Vehicle(); // Default Constructor
        Vehicle(const std::string& license, const std::string& phone, float height, float length); // Parameterized Constructor

        void writeToFile(std::fstream& file) const; // Write vehicle information to a file
        void readFromFile(std::fstream& file); // Read vehicle information from a file

        void initialize(const std::string& license, const std::string& phone, float height, float length); // Initialize vehicle with license, phone, height, and length
       
        string getLicense() const; // getter for license
        string getPhone() const; // getter for phone
        double getHeight() const; // getter for height
        double getLength() const; // getter for length

        void setLicense(string license); // setter for license
        void setPhone(string phone); // setter for phone
        void setHeight(double height); // setter for height
        void setLength(double length); // setter for length
        
        static bool checkExists(const std::string& license); // Checks if a vehicle exists by license
        static bool writeVehicle(const std::string& license, const std::string& phone, double height, double length);// Writes new vehicle to file
};
