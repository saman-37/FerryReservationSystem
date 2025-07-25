//************************************************************
// Ui.h
//************************************************************
// Purpose: Top-level UI class for the Ferry Reservation System.
// This is the user interface layer responsible for managing
// all menus, taking user input, and routing commands to
// mid-level control modules.
// July 10, 2025 Version 1 - All team members
//************************************************************

#pragma once

#include <string>

class UI
{
public:
    UI(); // Default Constructor

    static void userInterface();
    static void displayMainMenu();
    static void displayCreateMenu();
    static void displayDeleteMenu();
    static void CheckInVehicle();
    static void displayQuery();
    static void displaySailingReport();

    static int getUserChoice(int min, int max);      // in: min, max
    static std::string getInput(const std::string &prompt); // in: prompt - message to display
    static void sailingCreation();
    static void vesselCreation();
    static void reservationCreation();
};
