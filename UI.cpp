//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// Ui.cpp
//************************************************************
// Purpose: Implements the UI class for the Ferry Reservation System.
// This file contains the user interface logic, including main and submenus.
// July 20, 2025 Version 1 - Noble Sekhon
//************************************************************

#include <iostream>
#include <limits>
#include "UI.h"
#include "OtherControls.h"
#include "SailingControl.h"
#include "Util.h"

using namespace std;

//************************************************************
// Default Constructor
//************************************************************
UI::UI()
{
    // placeholder for initialization if needed
}

//************************************************************
// Main user interface loop that handles menu interaction
//************************************************************
void UI::userInterface()
{
    int choice;

    displayMainMenu();            // Show main menu options
    choice = getUserChoice(0, 5); // Get validated choice between 0 and 5
    do
    {

        switch (choice)
        {
        case 1:
            displayCreateMenu();          // Navigate to create menu
            displayMainMenu();            // Show main menu options
            choice = getUserChoice(0, 5); // Get validated choice between 0 and 5
            break;
        case 2:
            displayDeleteMenu();          // Navigate to delete menu
            displayMainMenu();            // Show main menu options
            choice = getUserChoice(0, 5); // Get validated choice between 0 and 5
            break;
        case 3:
            displayQuery();               // Query sailing info
            displayMainMenu();            // Show main menu options
            choice = getUserChoice(0, 5); // Get validated choice between 0 and 5
            break;

        case 4:
            displaySailingReport();       // Show sailing report
            displayMainMenu();            // Show main menu options
            choice = getUserChoice(0, 5); // Get validated choice between 0 and 5
            break;
        case 5:
            CheckInVehicle();             // Call check-in process
            displayMainMenu();            // Show main menu options
            choice = getUserChoice(0, 5); // Get validated choice between 0 and 5
            break;
        case 0:
            cout << "Exiting the application.Thank You for using Automobile FerryReserver!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            displayMainMenu();            // Show main menu options
            choice = getUserChoice(0, 5); // Get validated choice between 0 and 5
            break;
        }
    } while (choice > 0); // Repeat until user exits

    Util::shutdown(); // shutdown the system after user quits the program
}

//************************************************************
// Displays the main menu to the user
//************************************************************
void UI::displayMainMenu()
{
    cout << "======================== Main Menu ========================" << endl;
    cout << "1) Create " << endl;
    cout << "2) Delete " << endl;
    cout << "3) Query a sailing " << endl;
    cout << "4) Display sailing report " << endl;
    cout << "5) Check-in Vehicle " << endl;
    cout << "0) Quit " << endl;
    cout << "Choose an option [0-5] and press Enter. " << endl;
}

//************************************************************
// Displays the create submenu and handles creation logic
//************************************************************
void UI::displayCreateMenu()
{
    cout << "======================== Create Menu ======================" << endl;
    cout << "[1] Create Vessel " << endl;
    cout << "[2] Create Sailing " << endl;
    cout << "[3] Create Reservation " << endl;
    cout << "[0] Back to Main Menu " << endl;
    cout << "Choose an option [0-3] and press Enter. " << endl;

    int choice;
    choice = getUserChoice(0, 3);
    char cont;

    switch (choice)
    {
    case 0:
        cout << "Returning to Main Menu..." << endl;
        break;
    case 1:
    {
        string vesselName;
        int LCLL, HCLL;
        cont = 'y';
        while (cont == 'y' || cont == 'Y')
        {
            // Collect info and create vessel
            vesselName = getInput("Enter Vessel Name (max: 25 characters): ");
            LCLL = stoi(getInput("Enter LCLL (Positive integer, max: 3600): "));
            HCLL = stoi(getInput("Enter HCLL (Positive integer, max: 3600): "));
            if (OtherControls::createVessel(vesselName, HCLL, LCLL))
                cout << "Vessel successfully created." << endl;
            else
                cout << "Failed to create vessel." << endl;
            cont = getCharInput("Do you want to create another vessel? (y/n): ");
        }

        break;
    }
    case 2:
    {
        cont = 'y';
        while (cont == 'y' || cont == 'Y')
        {
            sailingCreation(); // Collect info and create sailing
            cont = getCharInput("Do you wish to create another sailing? (y/n): ");
        }
        break;
    }
    case 3:
    {
        cont = 'y';
        while (cont == 'y' || cont == 'Y')
        {
            reservationCreation(); // Collect info and create reservation
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
    // Keep showing menu until user exits
}

//************************************************************
// Displays delete menu and handles reservation or sailing deletion
//************************************************************
void UI::displayDeleteMenu()
{
    cout << "======================== Delete Menu ======================" << endl;
    cout << "[1] Delete Sailing " << endl;
    cout << "[2] Delete Reservation " << endl;
    cout << "[0] Back to main menu " << endl;
    cout << "Choose an option [0-2] and press Enter: " << endl;

    int choice;
    choice = getUserChoice(0, 2);
    do
    {
        switch (choice)
        {
        case 1:
        {
            string sailingId = getInput("Enter the sailing ID to delete (format: xxx-dd-hh): ");
            if (SailingControl::deleteSailing(sailingId))
                cout << "Sailing successfully deleted." << endl;
            else
                cout << "Failed to delete sailing." << endl;
            break;
        }
        case 2:
        {
            string sailingId = getInput("Enter Sailing ID (format: xxx-dd-hh): ");
            string license = getInput("Enter License (max: 10): ");
            string cont = getInput("Are you sure you want to delete this reservation? [y/n]: ");
            if (cont[0] == 'y' || cont[0] == 'Y')
            {
                if (OtherControls::deleteReservation(license, sailingId))
                    cout << "Reservation successfully deleted." << endl;
                else
                    cout << "Failed to delete reservation." << endl;
            }
            else
            {
                cout << "Deletion Terminated." << endl;
            }
            break;
        }
        case 3:
            cout << "Returning to Main Menu..." << endl;
            displayMainMenu(); // Exit to main
            break;
        default:
            cout << "Invalid choice. Please try again.\n"
                 << endl;
            displayDeleteMenu(); // Show menu again
            break;
        }
    } while (choice != 0);
}

//************************************************************
// Allows check-in of a vehicle for a sailing
//************************************************************
void UI::CheckInVehicle()
{
    cout << "======================== Check-in Vehicle ======================\n"
         << endl;
    string licensePlate = getInput("Enter vehicle License Plate: ");
    string sailingId = getInput("Enter the sailing Id for check-in (ttt-dd-hh): ");

    if (OtherControls::checkIn(licensePlate, sailingId))
        cout << "Vehicle with license plate " << licensePlate << " has been successfully checked in." << endl;
    else
        cout << "Failed to check in vehicle with license plate " << licensePlate << "." << endl;
}

//************************************************************
// Queries sailing based on user input
//************************************************************
void UI::displayQuery()
{
    cout << "================== Inquiry =======================" << endl;
    string sailingId = getInput("Enter the sailing id (ttt-dd-hh): ");
    SailingControl::querySailing(sailingId);
}

//************************************************************
// Displays summary report of all sailings
//************************************************************
void UI::displaySailingReport()
{
    SailingControl::printSailingReport(); // Generate report
}

//************************************************************
// Gets an integer choice between [min, max] from user
//************************************************************
int UI::getUserChoice(int min, int max)
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail() || choice < min || choice > max)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
    }
}

//************************************************************
// Gets input string from user with prompt
//************************************************************
string UI::getInput(const string &prompt)
{
    string input;
    cout << prompt;
    cin >> input;

    return input;
}

char UI::getCharInput(const string &prompt)
{
    char input;
    cout << prompt;
    cin >> input;
    return input;
}
//************************************************************
// Creates a sailing by prompting user for input
//************************************************************
void UI::sailingCreation()
{
    string vesselName = getInput("Enter Vessel name (max: 25 characters): ");
    string sailingId = getInput("Enter the sailing Id (format: xxx-dd-hh): ");
    if (SailingControl::createSailing(sailingId, vesselName))
        cout << "Sailing with sailing ID " << sailingId << " successfully created." << endl;
    else
        cout << "Failed to create sailing with sailing ID " << sailingId << "." << endl;
}

//************************************************************
// Creates a vessel by prompting user for name and capacities
//************************************************************
void UI::vesselCreation()
{
    string vesselName = getInput("Enter Vessel Name (max: 25 characters): ");
    int LCLL = stoi(getInput("Enter LCLL (Positive integer, max: 3600): "));
    int HCLL = stoi(getInput("Enter HCLL (Positive integer, max: 3600): "));
    if (OtherControls::createVessel(vesselName, HCLL, LCLL))
        cout << "Vessel successfully created." << endl;
    else
        cout << "Failed to create vessel." << endl;
}

//************************************************************
// Creates a reservation by gathering required info
//************************************************************
void UI::reservationCreation()
{
    string phoneNumber = getInput("Enter Customer Phone Number (format: 14 characters): ");
    string LicensePlate = getInput("Enter Vehicle License Number (max: 10 characters): ");
    string sailingId = getInput("Enter Sailing ID (format: xxx-dd-hh): ");
    if (OtherControls::createReservation(phoneNumber, sailingId, LicensePlate) == true)
        cout << "Reservation successfully created." << endl;
    else
        cout << "Failed to create reservation." << endl;
}
