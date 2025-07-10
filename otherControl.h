//************************************************************
// otherControl.h
//************************************************************
// Purpose: Mid-level controller that coordinates reservation
// creation, deletion, and check-in scenarios. Interfaces with
// entity classes like Vehicle, Sailing, Vessel, and Reservation
// to manage ferry system operations.
// July 10, 2025 Revision 1
//************************************************************

#pragma once

#include "vehicle.h"
#include "vessel.h"
#include "reservation.h"
#include "sailing.h"

#include <string>

class OtherControl {
    public:
        OtherControl(); // Default Constructor

        bool createReservation(std::string& sailingId, std::string& licensePlate); // Makes a new reservation, in: sailingId, licensePlate
        bool createVessel(std::string& vesselName, double HCLL, double LCLL); //in: vesselName, HCLL, LCLL
        bool deleteReservation(std::string& sailingId); // Deletes all reservations for a sailing, in: sailingId
        bool deleteSailing(std::string& sailingId); // Deletes a sailing record, in: sailingId
        bool checkIn(std::string& licensePlate, std::string& sailingId); // Checks in a vehicle to a sailing, in: sailingId, licensePlate

};
