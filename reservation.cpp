//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  // Each .cpp file should begin with this line
// July 10, 2025 Revision 1     //Each implementation .cpp module will need a version history at the top
// Introductory comment which adds to already provided comment in .h file,describe any overall design issues internal to this module (like data structure (if there are any) and algorithm (e.g. linear search of file

//************************************************************
#include "Reservation.h"
#include "Util.h"
#include <iostream>
#include <fstream>
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
    strcpy(sailingId, "");
    strcpy(license, "");
    onBoard = false; // Default to not on board
}

//************************************************************
// Parameterized Constructor
// Initializes the reservation with provided values
// in: sailing_id, license, on_board
Reservation::Reservation(const string &license, const string &sailingId, const bool &onBoard) // in: sailingID, license, phone
{
    strcpy(this->sailingId, sailingId.c_str());
    strcpy(this->license, license.c_str());
    this->onBoard = onBoard; // Default to not on board
};

void Reservation::writeToFile(fstream &file) const // in-out: file - binary file stream
{
    ofstream fout;
    fout.open("resevation.dat", ios::out | ios::binary);

    if (fout.is_open())
    {
        file.write(sailingId, SAILING_ID_LENGTH + 1);      // Write sailing ID
        file.write(license, LICENSE_LENGTH + 1);             // Write license                      
        file.write(reinterpret_cast<const char *>(&onBoard), sizeof(onBoard)); // Write onBoard status; we need reinterpret cast as the type should be character memory address 
        fout.flush(); // Ensure data is written to disk
        fout.close(); // Close the file after writing
    }

    else
    {
        cout << "Error opening file for writing." << endl;
    }
};

void Reservation::readFromFile(fstream &file); // in-out: file - binary file stream
{

};

string Reservation::toString() const // out: returns formatted string
{

};

void Reservation::open(const string &sailingId, const string &license, const string &phone) // in: sailing ID, license, phone number
{

};

int Reservation::getTotalReservationsOnSailing(const string &sailingId) // in: sailingID
{

};

bool Reservation::removeReservation(const string &sailingId, const string &license) // in: sailingID, license
{

};

bool Reservation::removeReservationsOnSailing(const std::string &sailingId) // in: sailingId
{

};

bool Reservation::checkExist(const string &sailingId, const string &license) // in: sailingID, license
{

};

bool Reservation::writeReservation(const string &sailingId, const string &license) // in: sailingID, license, phone                                                                                                                                                                                              {
{

};

void Reservation::setCheckedIn(const string &sailingId, const string &license) // in: sailingID, license
{

};
