    
    
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  // Each .cpp file should begin with this line
// July 10, 2025 Revision 1     //Each implementation .cpp module will need a version history at the top
// Introductory comment which adds to already provided comment in .h file,describe any overall design issues internal to this module (like data structure (if there are any) and algorithm (e.g. linear search of file

//************************************************************
#include "Reservation.h"
#include "util.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sstream>

using namespace std;

//************************************************************
// Default Constructor
// Initializes the reservation with default values
//************************************************************
Reservation::Reservation()
{
    sailingId ="";
    
}

Reservation::Reservation(const string &sailingId, const string &license, const bool on_board) // in: sailingID, license, phone
{
    int length;
    int height;

    if (vehicle.checkExists(license){
        // use that object
        height = vehicle.getHeight();
        length = vehicle.getLength();
        }
        else{
        // prompts customer for attributes-- BUT THIS IS DONE BY UI RIGHT?
        // SO WE NEED THIS CHANGE IN user interface documnet, that after getting license, NOT ALWAYS WE ASK FOR ALL OTHER ATTRIBUTES
        // need to push this instance to vehicle file too
        vehicle.writeVehicle()
        }
};

void Reservation::writeToFile(fstream &file) const // in-out: file - binary file stream
{
};

void Reservation::readFromFile(fstream &file); // in-out: file - binary file stream
{};

string Reservation::toString() const // out: returns formatted string
{

};

void Reservation::open(const string &sailingId, const string &license, const string &phone) // in: sailing ID, license, phone number
{

};

static int Reservation::getTotalReservationsOnSailing(const string &sailingId) // in: sailingID
{

};

static bool Reservation::removeReservation(const string &sailingId, const string &license) // in: sailingID, license
{

};

static bool Reservation::removeReservationsOnSailing(const std::string &sailingId) // in: sailingId
{

};

static bool Reservation::checkExist(const string &sailingId, const string &license) // in: sailingID, license
{

};

static bool Reservation::writeReservation(const string &sailingId, const string &license) // in: sailingID, license, phone                                                                                                                                                                                              {
{

};

static void Reservation::setCheckedIn(const string &sailingId, const string &license) // in: sailingID, license
{

};
