#pragma once

using namespace std;

#include <string>

class sailing{
    private:


    public:
        sailing();

        bool checkExists(string SailingId);
        bool writeSailing(string SailingId, string vesselName);

};
