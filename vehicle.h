#pragma once

using namespace std;

#include <string>
#include <fstream>


class vehicle {

    public:
        const int LICENSE_PLATE_LENGTH = 10;
        const int PHONE_LENGTH = 10;
        static const int RECORD_SIZE = LICENSE_PLATE_LENGTH + PHONE_LENGTH + sizeof(float) * 2;

        char license[LICENSE_PLATE_LENGTH + 1]; // +1 for null terminator
        char phone[PHONE_LENGTH + 1]; // +1 for null terminator
        float height;
        float length;
        
        vehicle(); // default constructor
        vehicle(const std::string& license, const std::string& phone, float height, float length); // parameterized constructor

        string getLicense() const; // getter for license
        string getPhone() const; // getter for phone
        float getHeight() const; // getter for height
        float getLength() const; // getter for length

        void setLicense(string license); // setter for license
        void setPhone(string phone); // setter for phone
        void setHeight(float height); // setter for height
        void setLength(float length); // setter for length
        
        bool checkExists(string license);
        bool writeVehicle(string license, string phone, float height, float length);
        double getHeight();
        double getLength();
};
