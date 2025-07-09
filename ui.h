#pragma once

#include <iostream>
#include <string>

#include "sailingControl.h"
#include "otherControl.h"
#include "util.h"

class UI {
    public:
        UI();        //constructor
        UI(int argc);     //constructor with arguments


        void userInterface();

        void displayMainMenu();

        void displayCreateMenu();
        void displayDeleteMenu();

        int getUserChoice(int min, int max);
        std::string getInput(const std::string& prompt);

};
