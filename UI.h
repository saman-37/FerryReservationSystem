//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*********************************************************
// Ui.h
//*********************************************************
// Purpose: Top-level UI class for the Ferry Reservation
// System.
// This is the user interface layer responsible for
// managing all menus, taking user input, and routing
// commands to mid-level control modules.
// July 24, 2025 Version 2 - All team members
// Aug 5, 2025   Version 3 - Noble added enum classes,
//                           getIntInput function
//*********************************************************

#pragma once

#include <string>

class UI
{
public:
    UI(); // Default Constructor

    //*********************************************************
    // Launches the main user interface loop
    //*********************************************************
    static void userInterface();

    //*********************************************************
    // Displays the main menu with options for different
    // operations
    //*********************************************************
    static void displayMainMenu();

    //*********************************************************
    // Displays the menu for creating records (vessel, sailing,
    // reservation)
    //*********************************************************
    static void displayCreateMenu();

    //*********************************************************
    // Displays the menu for deleting records (sailing,
    // reservation)
    //*********************************************************
    static void displayDeleteMenu();

    //*********************************************************
    // Handles the check-in process for a vehicle
    //*********************************************************
    static void CheckInVehicle();

    //*********************************************************
    // Displays a menu to query a sailing's details
    //*********************************************************
    static void displayQuery();

    //*********************************************************
    // Displays a report of all sailings
    //*********************************************************
    static void displaySailingReport();

    //*********************************************************
    // Utility method to safely get user input for menu choices
    // in: min - minimum valid choice
    // in: max - maximum valid choice
    // out: validated choice within range
    //*********************************************************
    static int getUserChoice(int min, int max);

    //*********************************************************
    // Prompts the user for string input
    // in: prompt - message to display
    // out: user input string
    //*********************************************************
    static std::string getInput(const std::string &prompt);

    //*********************************************************
    // Prompts the user for character input
    // in: prompt - message to display
    // out: user input character
    //*********************************************************
    static char getCharInput(const std::string &prompt);

    //*********************************************************
    // Prompts the user for integer input
    // in: prompt - message to display
    // out: user input integer
    //*********************************************************
    static int getIntInput(const std::string &prompt);

    //*********************************************************
    // Helper method to facilitate sailing creation
    //*********************************************************
    static void sailingCreation();

    //*********************************************************
    // Helper method to facilitate vessel creation
    //*********************************************************
    static void vesselCreation();

    //*********************************************************
    // Helper method to facilitate reservation creation
    //*********************************************************
    static void reservationCreation();
};

enum class MainMenuOption
{
    Quit = 0,
    Create = 1,
    Delete = 2,
    Query = 3,
    Report = 4,
    CheckIn = 5
};

enum class CreateMenuOption
{
    Back = 0,
    Vessel = 1,
    Sailing = 2,
    Reservation = 3
};

enum class DeleteMenuOption
{
    Back = 0,
    Sailing = 1,
    Reservation = 2
};
