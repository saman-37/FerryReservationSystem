//************************************************************
// sailingControl.h
//************************************************************
// Purpose: Mid-level controller for managing sailings. Handles
// the creation of sailings, querying individual sailings,
// and generating sailing reports. Interfaces with the Sailing entity.
// July 10, 2025 Revision 1
//************************************************************

#pragma once

using namespace std;

#include "Sailing.h"

#include <string>


class SailingControl {

    public:
        SailingControl(); // Default Constructor

        bool createSailing(const string& sailingId, const std::string& vesselName); // in: sailingId, vesselName
        bool deleteSailing(const string& sailingId); // in: sailingId
        void querySailing(const string& sailingId); // in: sailingId
        void printSailingReport(const string& sailingId); // in: sailingId
        
};