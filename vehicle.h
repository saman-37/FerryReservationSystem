#pragma once

using namespace std;

#include <string>

class vehicle {
    private:
        string license;
        string phone;
        float height;
        float length;

    public:
        vehicle(); // default constructor
        vehicle(string license, string phone, float height, float length); // parameterized constructor

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
