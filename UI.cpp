//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*********************************************************
// Ui.cpp
//*********************************************************
// Purpose: Implements the UI class for the Ferry
// Reservation System.
// This file contains the user interface logic, including
// main and submenus.
// July 20, 2025 Version 1 - Noble Sekhon, original
// July 29, 2025 Version 2 - Noble Sekhon, edited the Display
// functions for smooth flow as mentioned in User Manual
// Aug 05, 2025 Version 3 - Noble, changed the switch cases
// into enums for better readability
//*********************************************************

#include <iostream>
#include <limits>
#include "UI.h"
#include "OtherControls.h"
#include "SailingControl.h"
#include "Util.h"

using namespace std;

//*********************************************************
// Default Constructor
//*********************************************************
UI::UI()
{
    // placeholder for initialization if needed
}

//*********************************************************
// Main user interface loop that handles menu interaction
//*********************************************************
void UI::userInterface()
{
    int input;
    MainMenuOption choice;
    // Show main menu options
    displayMainMenu();
    // Get validated input between 0 and 5
    input = getUserChoice(0, 5);
    // cast it into enum
    choice = static_cast<MainMenuOption>(input);
    do
    {

        switch (choice)
        {
        case MainMenuOption::Create:
            // Navigate to create menu
            displayCreateMenu();
            cout << "Returning to Main Menu..." << endl;
            // Show main menu options
            displayMainMenu();
            // Get validated input between 0 and 5
            input = getUserChoice(0, 5);
            // cast it into enum
            choice = static_cast<MainMenuOption>(input);
            break;
        case MainMenuOption::Delete:
            // Navigate to delete menu
            displayDeleteMenu();
            cout << "Returning to Main Menu..." << endl;
            // Show main menu options
            displayMainMenu();
            // Get validated input between 0 and 5
            input = getUserChoice(0, 5);
            // cast it into enum
            choice = static_cast<MainMenuOption>(input);
            break;
        case MainMenuOption::Query:
            displayQuery(); // Query sailing info
            cout << "Returning to Main Menu..." << endl;
            // Show main menu options
            displayMainMenu();
            // Get validated input between 0 and 5
            input = getUserChoice(0, 5);
            // cast it into enum
            choice = static_cast<MainMenuOption>(input);
            break;

        case MainMenuOption::Report:
            // Show sailing report
            displaySailingReport();
            cout << "Returning to Main Menu..." << endl;
            // Show main menu options
            displayMainMenu();
            // Get validated input between 0 and 5
            input = getUserChoice(0, 5);
            // cast it into enum
            choice = static_cast<MainMenuOption>(input);
            break;
        case MainMenuOption::CheckIn:
            // Call check-in process
            CheckInVehicle();
            cout << "Returning to Main Menu..." << endl;
            // Show main menu options
            displayMainMenu();
            // Get validated input between 0 and 5
            input = getUserChoice(0, 5);
            // cast it into enum
            choice = static_cast<MainMenuOption>(input);
            break;
        case MainMenuOption::Quit:
            break;
        default:
            cout << "Invalid choice. Please try again."
                 << endl;
            // Show main menu options
            displayMainMenu();
            // Get validated input between 0 and 5
            input = getUserChoice(0, 5);
            // cast it into enum
            choice = static_cast<MainMenuOption>(input);
            break;
        }
    } while (input > 0); // Repeat until user exits
    cout << "Exiting the application."
         << " Thank You for using Automobile "
         << "FerryReserver!" << endl;
}

//*********************************************************
// Displays the main menu to the user
//*********************************************************
void UI::displayMainMenu()
{
    cout << "======================== Main Menu ========================" << endl;
    cout << "1) Create " << endl;
    cout << "2) Delete " << endl;
    cout << "3) Query a sailing " << endl;
    cout << "4) Display sailing report " << endl;
    cout << "5) Check-in Vehicle " << endl;
    cout << "0) Quit " << endl;
    cout << "Choose an option [0-5] and press Enter. "
         << endl;
}

//*********************************************************
// Displays the create submenu and handles creation logic
//*********************************************************
void UI::displayCreateMenu()
{
    cout << "======================== Create Menu ======================" << endl;
    cout << "[1] Create Vessel " << endl;
    cout << "[2] Create Sailing " << endl;
    cout << "[3] Create Reservation " << endl;
    cout << "[0] Back to Main Menu " << endl;
    cout << "Choose an option [0-3] and press Enter. "
         << endl;

    int input;
    CreateMenuOption choice;
    // getting a validated user input
    input = getUserChoice(0, 3);
    // explicitly casting input to enum
    choice = static_cast<CreateMenuOption>(input);
    char cont;

    switch (choice)
    {
    case CreateMenuOption::Back:
        cout << "Returning to Main Menu..." << endl;
        break;
    case CreateMenuOption::Vessel:
    {
        string vesselName;
        int LCLL, HCLL;
        cont = 'y';
        while (cont == 'y' || cont == 'Y')
        {
            // Collect info and create vessel
            vesselCreation();
            cont = getCharInput("Do you want to create another vessel? (y/n): ");
        }

        break;
    }
    case CreateMenuOption::Sailing:
    {
        cont = 'y';
        while (cont == 'y' || cont == 'Y')
        {
            // Collect info and create sailing
            sailingCreation();
            cont = getCharInput("Do you wish to create another sailing? (y/n): ");
        }
        break;
    }
    case CreateMenuOption::Reservation:
    {
        cont = 'y';
        while (cont == 'y' || cont == 'Y')
        {
            // Collect info and create reservation
            reservationCreation();
            cont = getCharInput("Do you wish to create another reservation? (y/n): ");
        }
        break;
    }

    default:
    {
        cout << "Invalid choice." << endl;
        displayCreateMenu(); // Redisplay menu
        break;
    }
    }
}

//*********************************************************
// Displays delete menu and handles reservation or sailing
// deletion
//*********************************************************
void UI::displayDeleteMenu()
{
    cout << "======================== Delete Menu ======================" << endl;
    cout << "[1] Delete Sailing " << endl;
    cout << "[2] Delete Reservation " << endl;
    cout << "[0] Back to main menu " << endl;
    cout << "Choose an option [0-2] and press Enter: "
         << endl;

    int input;
    DeleteMenuOption choice;
    // getting validated input from user
    input = getUserChoice(0, 2);
    // explicitly casting input to enum
    choice = static_cast<DeleteMenuOption>(input);

    switch (choice)
    {
    case DeleteMenuOption::Back:
        cout << "Returning to Main Menu..." << endl;
        displayMainMenu(); // Exit to main
        break;

    case DeleteMenuOption::Sailing:
    {
        string sailingId = getInput("Enter the sailing ID to delete (format: xxx-dd-hh): ");
        if (SailingControl::deleteSailing(sailingId))
            cout << "Sailing successfully deleted."
                 << endl;
        else
            cout << "Failed to delete sailing." << endl;
        break;
    }
    case DeleteMenuOption::Reservation:
    {
        string sailingId = getInput("Enter Sailing ID (format: xxx-dd-hh): ");
        string license = getInput("Enter License (max: 10): ");
        string cont = getInput("Are you sure you want to delete this reservation? [y/n]: ");
        // Validating user input to continue performing operation
        if (cont[0] == 'y' || cont[0] == 'Y')
        {
            if (OtherControls::deleteReservation(license, sailingId))
                cout << "Reservation successfully deleted."
                     << endl;
            else
                cout << "Failed to delete reservation."
                     << endl;
        }
        else
        {
            cout << "Deletion Terminated." << endl;
        }
        break;
    }
    default:
        cout << "Invalid choice. Please try again.\n"
             << endl;
        displayDeleteMenu(); // Show menu again
        break;
    }
}

//*********************************************************
// Allows check-in of a vehicle for a sailing
//*********************************************************
void UI::CheckInVehicle()
{
    cout << "======================== Check-in Vehicle ======================\n"
         << endl;
    string licensePlate = getInput("Enter vehicle License Plate: ");
    string sailingId = getInput("Enter the sailing Id for check-in (ttt-dd-hh): ");

    if (OtherControls::checkIn(licensePlate, sailingId))
        cout << "Vehicle with license plate " << licensePlate
             << " has been successfully checked in." << endl;
    else
        cout << "Failed to check in vehicle with "
             << "license plate: " << licensePlate << "."
             << endl;
}

//*********************************************************
// Queries sailing based on user input
//*********************************************************
void UI::displayQuery()
{
    cout << "================== Inquiry =======================" << endl;
    string sailingId = getInput("Enter the sailing id (ttt-dd-hh): ");
    SailingControl::querySailing(sailingId);
}

//*********************************************************
// Displays summary report of all sailings
//*********************************************************
void UI::displaySailingReport()
{
    // Generate report
    SailingControl::printSailingReport();
}

//*********************************************************
// Gets an integer choice between [min, max] from user
//*********************************************************
int UI::getUserChoice(int min, int max)
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail() || choice < min || choice > max)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),
                       '\n');
            cout << "Invalid input. Please enter a number"
                 << " between " << min << " and " << max
                 << ": ";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(),
                       '\n');
            return choice;
        }
    }
}

//*********************************************************
// Gets input string from user with prompt
//*********************************************************
string UI::getInput(const string &prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);

    return input;
}
//*********************************************************
// Gets input character from user with prompt
//*********************************************************
char UI::getCharInput(const string &prompt)
{
    char input;
    cout << prompt;
    cin >> input;
    return input;
}
//************************************************************
// Gets input from user with prompt and checks it for integer
//************************************************************
int UI::getIntInput(const string &prompt)
{
    string input;

    // continue asking for a number until an integer is entered
    while (true)
    {
        cout << prompt;
        getline(cin, input);
        bool allDigits = true;
        for (char c : input)
        {
            if (!isdigit(c))
            {
                allDigits = false;
                break;
            }
        }
        // if the number is  not an integer prompt again for input
        if (!allDigits)
        {
            cout << "Invalid input! Please enter a valid number." << endl;
            continue; // to avoid invalid conversion of string to int
        }

        // the input is integer so return the input

        return stoi(input);
    }
}
//*********************************************************
// Creates a sailing by prompting user for input
//*********************************************************
void UI::sailingCreation()
{
    string vesselName = getInput("Enter Vessel name (max: 25 characters): ");
    string sailingId = getInput("Enter the sailing Id (format: xxx-dd-hh): ");
    if (SailingControl::createSailing(sailingId, vesselName))
        cout << "Sailing with sailing ID " << sailingId
             << " successfully created." << endl;
    else
        cout << "Failed to create sailing with sailing ID "
             << sailingId << "." << endl;
}

//*********************************************************
// Creates a vessel by prompting user for name and capacities
//*********************************************************
void UI::vesselCreation()
{
    string vesselName = getInput("Enter Vessel Name (max: 25 characters): ");
    int LCLL = getIntInput("Enter LCLL (Positive number, max: 3600): ");
    int HCLL = getIntInput("Enter HCLL (Positive number, max: 3600): ");
    if (OtherControls::createVessel(vesselName, HCLL, LCLL))
        cout << "Vessel successfully created." << endl;
    else
        cout << "Failed to create vessel." << endl;
}

//*********************************************************
// Creates a reservation by gathering required info
//*********************************************************
void UI::reservationCreation()
{
    string phoneNumber = getInput("Enter Customer Phone Number (format: 14 characters): ");
    string LicensePlate = getInput("Enter Vehicle License Number (max: 10 characters): ");
    string sailingId = getInput("Enter Sailing ID (format: xxx-dd-hh): ");
    if (OtherControls::createReservation(phoneNumber,
                                         sailingId,
                                         LicensePlate) == true)
        cout << "Reservation successfully created."
             << endl;
    else
        cout << "Failed to create reservation."
             << endl;
}
