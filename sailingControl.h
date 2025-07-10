//************************************************************
// sailingControl.h
//************************************************************
// Purpose: Mid-level controller for managing sailings. Handles
// the creation of sailings, querying individual sailings,
// and generating sailing reports. Interfaces with the Sailing entity.
// July 10, 2025 Revision 1
//************************************************************

#pragma once

#include "sailing.h"

#include <string>


class SailingControl {

    public:
        SailingControl(); // Default Constructor

        bool createSailing(const std::string& sailingId, const std::string& vesselName); // in: sailingId, vesselName
        bool deleteSailing(const std::& sailingId); // in: sailingId
        void querySailing(const std::string& sailingId); // in: sailingId
        void printSailingReport(const std::string& sailingId); // in: sailingId
        
};