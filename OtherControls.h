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

class OtherControl {
    public:
        OtherControl(); // Default Constructor

<<<<<<< HEAD
        bool createReservation(int phoneNumber, string& sailingId, string& licensePlate); // Makes a new reservation, in: sailingId, licensePlate
        bool createVessel(string& vesselName, int HCLL, int LCLL); //in: vesselName, HCLL, LCLL
=======
        int createReservation(int phoneNumber, string& sailingId, string& licensePlate); // Makes a new reservation, in: sailingId, licensePlate
        bool createVessel(string& vesselName, string& vesselId, double HCLL, double LCLL); //in: vesselName, HCLL, LCLL
>>>>>>> 3d2876dfa93ab77bcc0a0cb01fd073870c60bcbf
        bool deleteReservation(string& sailingId); // Deletes all reservations for a sailing, in: sailingId
        bool deleteSailing(string& sailingId); // Deletes a sailing record, in: sailingId
        bool checkIn(string& licensePlate, std::string& sailingId); // Checks in a vehicle to a sailing, in: sailingId, licensePlate

};
