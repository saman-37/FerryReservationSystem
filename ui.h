//************************************************************
// ui.h
//************************************************************
// Purpose: Top-level UI class for the Ferry Reservation System.
// This is the user interface layer responsible for managing
// all menus, taking user input, and routing commands to
// mid-level control modules.
// July 10, 2025 Revision 1
//************************************************************

#pragma once

#include <string>


class UI {
    public:
        UI();         // Default Constructor
        UI(int argc); // in: argc - argument count from command-line


        void userInterface();
        void displayMainMenu();
        void displayCreateMenu();
        void displayDeleteMenu();
        void CheckInVehicle();
        void displayQuery();
        void displaySailingReport();

        int getUserChoice(int min, int max); // in: min, max
        std::string getInput(const std::string& prompt); // in: prompt - message to display

};
