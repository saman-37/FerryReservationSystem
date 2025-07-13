
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// July 10, 2025 Revision 1
//************************************************************
#include "sailingControl.h"
#include <string>
using namespace std;


class SailingControl {

    public:
        SailingControl(); // Default Constructor

        bool createSailing(const string& sailingId, const string& vesselName); // in: sailingId, vesselName
        bool deleteSailing(const & sailingId); // in: sailingId
        void querySailing(const string& sailingId); // in: sailingId
        void printSailingReport(const string& sailingId); // in: sailingId
        
};
