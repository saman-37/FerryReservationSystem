//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ************************************************************
// OtherControls.h
// ************************************************************
// Purpose: Mid-level controller that coordinates reservation
// creation, deletion, and check-in scenarios. Interfaces with
// entity classes like Vehicle, Sailing, Vessel, and Reservation
// to manage ferry system operations.
// July 22, 2025 Version 2 - Darpandeep Kaur
// ************************************************************

#pragma once

using namespace std;

#include "Vehicle.h"
#include "Vessel.h"
#include "Reservation.h"
#include "Sailing.h"

#include <string>

class OtherControls
{
public:
    OtherControls(); // Default Constructor

    //************************************************************
    // createReservation
    //************************************************************
    // Purpose: Creates a reservation after validating sailing ID,
    // vehicle existence, space availability, and special vehicle details.
    // in: sailingId, licensePlate
    // out: returns true if reservation successfully made
    // Note: phoneNumber parameter is currently unused in implementation
    //************************************************************
    static bool createReservation(int phoneNumber, string &sailingId, string &licensePlate);

    //************************************************************
    // createVessel
    //************************************************************
    // Purpose: Creates a new vessel record with capacity info
    // in: vesselName, HCLL, LCLL
    // out: returns true if vessel is created successfully
    //************************************************************
    static bool createVessel(string &vesselName, int HCLL, int LCLL);

    //************************************************************
    // deleteReservation
    //************************************************************
    // Purpose: Deletes a reservation using license and sailing ID.
    // in: sailingId
    // out: returns true if deletion succeeded
    //************************************************************
    static bool deleteReservation(string &sailingId);

    //************************************************************
    // checkIn
    //************************************************************
    // Purpose: Marks a reservation as checked in for boarding
    // in: licensePlate, sailingId
    // out: returns true if check-in successful
    //************************************************************
    static bool checkIn(string &licensePlate, std::string &sailingId);
};
