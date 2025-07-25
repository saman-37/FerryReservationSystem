#include "Reservation.h"
#include "Sailing.h"
#include "SailingControl.h"
#include "Vessel.h"

#include <iostream>

SailingControl::SailingControl()
{
    // Default Constructor
}

bool SailingControl::createSailing(const string &sailingId, const string &vesselName)
{
    // if checkExist(vesselName)
}

bool SailingControl::deleteSailing(const string &sailingId)
{
    if checkExist (sailingId)
    {
        removeReservationsOnSailing(sailingId);
        removeSailing(sailingId);
        return true;
    }
    else
    {
        // cout << "Sailing does not exist..." << endl;
        return false;
    }
}

void SailingControl::querySailing(const string &sailingId)
{
    if checkExist (sailingId)
    {
        // getName(sailingId);
        // getHRL(sailingId);
        // getLRL(sailingId);
        // getLCLL(sailingId);
        // getHCLL(sailingId);
        // getTotalReservationsOnSailing(sailingId);
        // What to do next?
    }
    else
        return;
}

void SailingControl::printSailingReport()
{
    // getCapacity(sailingId);
    // getSailingInfo(sailingId);
    // getNext(); // What do we need this for?
    // getTotalReservationsOnSailing(sailingId);

    // Should I print them as required or UI will print them? I guess I should.
}
