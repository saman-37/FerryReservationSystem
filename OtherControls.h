//************************************************************
// OtherControl.h
//************************************************************
// Purpose: Mid-level controller that coordinates reservation
// creation, deletion, and check-in scenarios. Interfaces with
// entity classes like Vehicle, Sailing, Vessel, and Reservation
// to manage ferry system operations.
// July 10, 2025 Revision 1
//************************************************************

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

    static bool createReservation(int phoneNumber, string &sailingId, string &licensePlate);  // Makes a new reservation, in: sailingId, licensePlate
    static bool createVessel(string &vesselName, string &vesselId, double HCLL, double LCLL); // in: vesselName, HCLL, LCLL
    static bool deleteReservation(string &sailingId);                                         // Deletes a sailing record, in: sailingId
    static bool checkIn(string &licensePlate, std::string &sailingId);                        // Checks in a vehicle to a sailing, in: sailingId, licensePlate
};
