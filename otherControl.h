//************************************************************
// otherControl.h
//************************************************************
// Purpose: Mid-level controller that coordinates reservation
// creation, deletion, and check-in scenarios. Interfaces with
// entity classes like Vehicle, Sailing, Vessel, and Reservation
// to manage ferry system operations.
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

        bool createReservation(std::string& sailingId, std::string& licensePlate); // Makes a new reservation
        bool deleteReservation(std::string& sailingId); // Deletes all reservations for a sailing
        bool deleteSailing(std::string& sailingId); // Deletes a sailing record
        bool checkIn(std::string& licensePlate, std::string& sailingId); // Checks in a vehicle to a sailing

};
