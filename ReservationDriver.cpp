#include "Reservation.h"

#include <iostream>
#include "Util.h"
#include "Vehicle.h"
#include "UI.h"

using namespace std;

int main()
{
    Reservation r;
    r.writeReservation("NAVIX3", "van-07-07");

    bool exists = Reservation::checkExist("NAVIX3", "van-07-07");
    cout << "Reservation exists: " << (exists ? "Yes" : "No") << endl;

    r.readFromFile(Util::reservationFile);

    return true;
}
