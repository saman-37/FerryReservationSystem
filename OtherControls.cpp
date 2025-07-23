//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// July 12, 2025 Revision 1
//************************************************************
#include "OtherControl.h"
#include <string>
using namespace std;

class OtherControl {
    public:
        OtherControl(); // Default Constructor

        //STEP 1 --- Creating a New Reservation
        bool createReservation(string& sailingId, string& licensePlate) // Makes a new reservation, in: sailingId, licensePlate
        {
          if (sailing.checkExist(sailingId))  //STEP 2
          {
             //STEP 3
            if(vehicle.checkExist() == false) // do the EXTRA WORK HERE, BCZ LOWER WORK IS MUTUAL //need to create vehicle record too
            {
              //ask more attributes FROM USER befpre writeVehicle; BUT CHECK FIRST DO WE EVEN HAVE SPACE?
              //TECHINCALLY CHANGE STEP ORDER!!!!!!!!!!
              if (sailing.isSpaceAvailable(){ //NOW DEPEND ON VEHICLE, SO SHOULD WE INVOKE .isSpaceAvailableInHigh()   ND isSpaceAvailableInLow()
              
                //calling the write method in reservation file
                reservation.writeReservation();  //STEP 8
                
              }

              else 
                exit(2); //ERROR CODE FOR SPACE NOT AVAILABLE
            }
          }

            
           if (reservation.checkExist(licensePlate){
                exit(1); //ERROR CODE WITH ALREADY RESERVATION EXIST
              }
              
              //lets create reservation, hence not here, after CREATING THE VEHICLE
              
          }

          else 
          { 
            //WE JUST WANT TO EXIT WITH A CODE AND LET ANOTHER MODULE HANDLE IT //YES, give exit code to otherControl, it will either detect, or send code back to UI which has a error handling function
            //cout << "Sailing must already exist"; 
            exit(0); //ERROR CODE FOR SAILING DOESNT EXIST
          }
          
      
          
        };

        bool createVessel(string& vesselName, double HCLL, double LCLL) //in: vesselName, HCLL, LCLL
        {
        };
        bool deleteReservation(string& sailingId) // Deletes all reservations for a sailing, in: sailingId
        {
        };

        bool deleteSailing(string& sailingId)// Deletes a sailing record, in: sailingId
        {
        };

        bool checkIn(string& licensePlate,:string& sailingId) // Checks in a vehicle to a sailing, in: sailingId, licensePlate
        {
        };

};
