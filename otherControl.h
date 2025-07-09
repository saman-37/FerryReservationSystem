#pragma once

#include "vehicle.h"
#include "vessel.h"
#include "reservation.h"
#include "sailing.h"

#include <string>

class OtherControl {
    public:
        OtherControl(); // constructor

        bool createReservation(std::string& sailingId, std::string& licensePlate);
        bool deleteReservation(std::string& sailingId);
        bool deleteSailing(std::string& sailingId);
        bool checkIn(std::string& licensePlate, std::string& sailingId); 

};
