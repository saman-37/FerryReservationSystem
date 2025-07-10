//************************************************************
// vehicle.h
//************************************************************
// Purpose: Represents a binary-stored vehicle record with license,
// phone, height, and length data. Used in reservations.
// July 10, 2025 Revision 1
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
        Vehicle(const std::string& license, const std::string& phone, float height, float length); // in: license, phone, height, length

        void writeToFile(std::fstream& file) const; // in-out: file
        void readFromFile(std::fstream& file); // in-out: file

        void initialize(const std::string& license, const std::string& phone, float height, float length); // in: license, phone, height, length
       
        std::string getLicense() const; // out: license
        std::string getPhone() const; // out: phone
        double getHeight() const; // out: height
        double getLength() const; // out: length

        void setLicense(string license); // in: license
        void setPhone(string phone); // in: phone
        void setHeight(double height); // in: height
        void setLength(double length); // in: length
        
        static bool checkExist(const std::string& license); // in: license
        static bool writeVehicle(const std::string& license, const std::string& phone, double height, double length); // in: license, phone, height, length
};
