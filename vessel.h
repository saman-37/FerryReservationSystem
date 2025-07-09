#pragma once

using namespace std;

#include <string>

class vessel {
    private:
        string vesselName;
        string vessel_ID;
        double HCLL;
        double LCLL;

    public:
        vessel(); // default constructor
        vessel(string vesselName, string vesselId, double HCLL, double LCLL); // parameterized constructor

        string getName() const; // getter for name
        string getVesselID() const; // getter for vessel_ID
        double getHCLL() const; // getter for HCLL(High Capacity Lane Length)
        double getLCLL() const; // getter for LCLL(Low Capacity Lane Length)

        void setName(string name); // setter for name
        void setVesselID(string vesselId); // setter for vessel_ID
        void setHCLL(double HCLL); // setter for HCLL(High Capacity Lane Length)
        void setLCLL(double LCLL); // setter for LCLL(Low Capacity Lane Length)

        bool checkExists(string vesselId);
        bool writeVessel(string VesselName, string vesselId, double HCLL, double LCLL);
        double getHCLL();
        double getLCLL();


    };
