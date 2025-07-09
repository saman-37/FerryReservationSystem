//************************************************************
// sailingControl.h
//************************************************************
// Purpose: Mid-level controller for managing sailings. Handles
// the creation of sailings, querying individual sailings,
// and generating sailing reports. Interfaces with the Sailing entity.
//************************************************************

#pragma once

#include "sailing.h"

#include <string>


class SailingControl {

    public:
        SailingControl(); // Default Constructor

        bool createSailing(const std::string& sailingId, const std::string& vesselName);
        void querySailing(const std::string& sailingId);
        void printSailingReport(const std::string& sailingId);
        
};