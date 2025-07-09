#pragma once
#include "sailing.h"

#include <string>


class SailingControl {

    public:
        SailingControl();

        bool createSailing(const std::string& sailingId, const std::string& vesselName);
        void querySailing(const std::string& sailingId);
        void printSailingReport(const std::string& sailingId);
        
};