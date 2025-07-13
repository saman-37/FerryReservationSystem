//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  // Each .cpp file should begin with this line
// July 10, 2025 Revision 1     //Each implementation .cpp module will need a version history at the top
                                // Introductory comment which adds to already provided comment in .h file,describe any overall design issues internal to this module (like data structure (if there are any) and algorithm (e.g. linear search of file

//************************************************************
#include "reservation.h"

class Reservation {
    public:
        // Fixed lengths for binary record layout
        static const int SAILING_ID_LENGTH = 15;
        static const int LICENSE_LENGTH = 10;
        static const int PHONE_LENGTH = 14;
        static const int RECORD_SIZE = SAILING_ID_LENGTH + LICENSE_LENGTH + PHONE_LENGTH + 1;

        // Reservation record fields
        char sailingId[SAILING_ID_LENGTH + 1]; // +1 for null terminator
        char license[LICENSE_LENGTH + 1]; // +1 for null terminator

        char phone[PHONE_LENGTH + 1]; // +1 for null terminator
        //WE DONT NEED TO STORE PHONE IN RESERVATION, LICENSE AND SAILING ID ARE KEYS
        //but WE MAY NEED IT, IN-CASE THE VEHICLE IS NOT ALREADY, WE WILL CREATE ITS OBJECT AND PUSH IT IN VEHICLE FILE FOR FUTURE easy referance and reservation creation

        bool checkedIn; // Track whether the vehicle has checked in.

        //????????????????????
        Reservation(); // Default Constructor

        Reservation(const string& sailingId, const string& license, const string& phone) // in: sailingID, license, phone
        {
            int length;
            int height;
            //search in "vehicle" file, if it already exists
            //SO HERE, DO I NEED TO HAVE .csv file for vehicle,which i will communicate to now 

            //yet how do i get data from vehicle?
            // do i create an empty vehicle instance with just license, and tell it to match with license in vehicle, return the whole record? 
            //...
            if (vehicle.checkExists(license){
                //use that object
                height = vehicle.getHeight();
                length = vehicle.getLength();
            }
            else{
                //prompts customer for attributes-- BUT THIS IS DONE BY UI RIGHT? 
                //SO WE NEED THIS CHANGE IN user interface documnet, that after getting license, NOT ALWAYS WE ASK FOR ALL OTHER ATTRIBUTES
                //need to push this instance to vehicle file too
                vehicle.writeVehicle();
            }

            

        };

        void writeToFile(fstream& file) const // in-out: file - binary file stream
        {
        };

        void readFromFile(fstream& file); // in-out: file - binary file stream 
        {
        };

        
        string toString() const // out: returns formatted string 
        {
            
        };


        void open(const string& sailingId, const string& license, const string& phone) // in: sailing ID, license, phone number        
        {
    
        };

        static int getTotalReservationsOnSailing(const string& sailingId)// in: sailingID
        {
    
        };

        static bool removeReservation(const string& sailingId, const string& license) // in: sailingID, license
        {
    
        };

        static bool removeReservationsOnSailing(const std::string& sailingId) // in: sailingId
        {
    
        };

        static bool checkExist(const string& sailingId, const string& license)// in: sailingID, license
        {
            
    
        };

        static bool writeReservation(const string& sailingId, const string& license)// in: sailingID, license, phone                                                                                                                                                                                              {
        {
            
    
        };

        static void setCheckedIn(const string& sailingId, const string& license) // in: sailingID, license
        {
    
        };

};
