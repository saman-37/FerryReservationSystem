//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// util.cpp
//************************************************************
// Purpose: Provides system-level helper functions such as
// startup, shutdown, and reset operations.
//July 20, 2025 Revision 1 - Darpandeep Kaur
//************************************************************ 

#include "util.h"

#include<fstream>
#include <iostream>
using namespace std;

   fstream Util::vesselFile;
   fstream Util::sailingFile;
   fstream Util::reservationFile;
   fstream Util::vehicleFile;


//************************************************************
// Default Constructor
//************************************************************
Util::Util() {
   // Placeholder for initialization if needed
}

//************************************************************
// Initializes the system by opening necessary data files
//************************************************************
void Util::startup() {

   cout << "Starting up the system..." << endl;

   vesselFile.open("vessel.dat", ios::in | ios::out | ios::binary);  // Open vessel file for reading and writing
   if (!vesselFile.is_open()) {  // Check if the file is open
      vesselFile.clear();    // Clear any error flags
      vesselFile.open("vessel.dat", ios::out | ios::binary);  // Open for writing
      vesselFile.close();  // Close the file after writing
      vesselFile.open("vessel.dat", ios::in | ios::out | ios::binary);  // Reopen for reading and writing
   }

   sailingFile.open("sailing.dat", ios::in | ios::out | ios::binary);  // Open sailing file
   if (!sailingFile.is_open()) {    // Check if the file is open
      sailingFile.clear();  // Clear any error flags
      sailingFile.open("sailing.dat", ios::out | ios::binary);    // Open for writing
      sailingFile.close();  // Close the file after writing
      sailingFile.open("sailing.dat", ios::in | ios::out | ios::binary);    // Reopen for reading and writing
   }

   reservationFile.open("reservation.dat", ios::in | ios::out | ios::binary);   // Open reservation file
   if (!reservationFile.is_open()){ // Check if the file is open
      reservationFile.clear();  // Clear any error flags
      reservationFile.open("reservation.dat", ios::out | ios::binary);  // Open for writing
      reservationFile.close(); // Close the file after writing
      reservationFile.open("reservation.dat", ios::in | ios::out | ios::binary);    // Reopen for reading and writing
   }

   vehicleFile.open("vehicel.dat", ios::in | ios::out | ios::binary);   // Open vehicle file
   if (!vehicleFile.is_open()){     // Check if the file is open
      vehicleFile.clear(); // Clear any error flags
      vehicleFile.open("vehicle.dat", ios::out | ios::binary);  // Open for writing
      vehicleFile.close();  // Close the file after writing
      vehicleFile.open("vehicle.dat", ios::in | ios::out | ios::binary);    // Reopen for reading and writing
   }

   cout << "Startup complete." << endl;

}

//************************************************************
// Gracefully closes all open resources/files
//************************************************************
void Util::shutdown() {
   cout << "Shutting down the system..." << endl;

   if (vesselFile.is_open()){ 
      vesselFile.close();   // Close vessel file only if it is open
   }

   if (sailingFile.is_open()){
      sailingFile.close();  // Close sailing file only if it is open
   }

   if (reservationFile.is_open()){
      reservationFile.close();   // Close reservation file only if it is open
   }

   if (vehicleFile.is_open()){
      vehicleFile.close();   // Close vehicle file only if it is open
   }
    cout << "Shutdown complete." << endl;
}

//************************************************************
// Resets system data by clearing all files
//************************************************************
void Util::reset() {
   cout << "Reseting system data..." << endl;

   ofstream ofs;

   ofs.open("vesse.dat", ios::trunc | ios::binary);   // Open vessel file for truncating to reset the data in the file without deleting the file
   ofs.close();

   ofs.open("sailing.dat", ios::trunc | ios::binary);  // Open sailing file for truncating to reset the data in the file without deleting the file
   ofs.close();

   ofs.open("reservaiton.dat", ios::trunc | ios::binary);  // Open reservation file for truncating to reset the data in the file without deleting the file
   ofs.close();

   ofs.open("vehicle.dat", ios::trunc | ios::binary);  // Open vehicle file for truncating to reset the data in the file without deleting the file
   ofs.close();

   cout << "System data reset compelete." << endl;

}
