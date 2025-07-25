//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// Ui.cpp
//************************************************************
// Purpose: Implements the UI class for the Ferry Reservation System.
// This file contains the user interface logic, including main and submenus.
// July 20, 2025 Version 1
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
// Main user interface loop
//************************************************************
void UI::userInterface()
{
    int choice;
    do
    {
        displayMainMenu();
        choice = getUserChoice(0, 5); // Get user choice from main menu
        switch (choice)
        {
        case 1:
            displayCreateMenu(); // Display create menu
            break;
        case 2:
            displayDeleteMenu(); // Display delete menu
            break;
        case 3:
            CheckInVehicle(); // Check-in vehicle
            break;
        case 4:
            displayQuery(); // Query sailing
            break;
        case 5:
            displaySailingReport(); // Print sailing report
            break;
        case 0:
            cout << "Exiting the application.Thank You for using Automobile FerryReserver!" << endl; // Exit message
            break;
        default:
            cout << "Invalid choice. Please try again.\n"
                 << endl; // Error message for invalid
            break;
        }
    } while (choice != 0); // Loop until user chooses to exit
}

//************************************************************
// Displays the main menu
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
// Displays the create menu
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
    choice = getUserChoice(0, 3); // Get user choice from create menu
    do
    {
        switch (choice)
        {
        
        case 1://user chooses to create new vessel
        {
            char cont = 'y';
            while (cont == 'y' || cont == 'Y')
            {
                vesselCreation();
                string in = getInput("Do you want to create another vessel? (y/n): ");
                cont = in[0];
            }
            break;
        }

        case 2: // user chooses to create new sailing
        {
            char cont = 'y';
            while (cont == 'y' || cont == 'Y')
            {
                sailingCreation();
                string in = getInput("Do you wish to create another sailing? (y/n): ");
                cont = in[0];
            }
            break;
        }

        case 3:
        {

            char cont = 'y';
            while (cont == 'y' || cont == 'Y')
            {
                reservationCreation();
                string in = getInput("Do you wish to create another reservation? (y/n): ");
                cont = in[0];
            }
            break;
            ;
        }

        case 0:
        {
            cout << "Returning to Main Menu..." << endl;
            displayMainMenu(); // Return to main menu
            break;
        }
        default:
        {
            cout << "Invalid choice. Please try again.\n"
                 << endl;        // Error message for invalid choice
            displayCreateMenu(); // Redisplay create menu
            break;
        }
        }
    } while (choice != 0); // Loop until user chooses to return to main menu
}
//************************************************************
// Displays the delete menu
//************************************************************
void UI::displayDeleteMenu()
{
    cout << "======================== Delete Menu ======================" << endl;
    cout << "[1] Delete Sailing " << endl;
    cout << "[2] Delete Reservation " << endl;
    cout << "[3] Cancel " << endl;
    cout << "Choose an option [1-3] and press Enter: " << endl;

    int choice;
    choice = getUserChoice(0, 2); // Get user choice from delete menu
    do
    {
        switch (choice)
        {
        case 1:
        {
            string sailingId = getInput("Enter the sailing ID to delete (format: xxx-dd-hh): ");
            if (SailingControl::deleteSailing(sailingId))
            {
                cout << "Sailing successfully deleted." << endl;
            }
            else
            {
                cout << "Failed to delete sailing." << endl;
            }
        }
        break;
        case 2:
        {
            string sailingId = getInput("Enter Sailing ID (format: xxx-dd-hh): ");
            if (OtherControls::deleteReservation(sailingId))
            {
                cout << "Reservation successfully deleted." << endl;
            }
            else
            {
                cout << "Failed to delete reservation." << endl;
            }
        }
        break;
        case 3:
        {
            cout << "Returning to Main Menu..." << endl;
            displayMainMenu(); // Return to main menu
            break;
        }

        default:
        {
            cout << "Invalid choice. Please try again.\n"
                 << endl;        // Error message for invalid choice
            displayDeleteMenu(); // Redisplay delete menu
            break;
        }
        }
    } while (choice != 0); // Loop until user chooses to return to main menu
}

//************************************************************
// Check-in vehicle
//************************************************************
void UI::CheckInVehicle()
{

    cout << "======================== Check-in Vehicle ======================\n"
         << endl;
    string licensePlate = getInput("Enter vehicle License Plate: ");
    string sailingId = getInput("Enter the sailing Id for check-in (ttt-dd-hh): ");

    if (OtherControls::checkIn(licensePlate, sailingId))
    {
        cout << "Vehicle with license plate " << licensePlate << " has been successfully checked in." << endl;
    }
    else
    {
        cout << "Failed to check in vehicle with license plate " << licensePlate << "." << endl;
    }
}

//************************************************************
// Displays query options for sailings
//************************************************************
void UI::displayQuery()
{
    cout << "================== Inquiry =======================" << endl;
    string sailingId = getInput("Enter the sailing id (ttt-dd-hh): ");

    SailingControl::querySailing(sailingId); // Query the sailing
}

//************************************************************
// Print sailing report
//************************************************************
void UI::displaySailingReport()
{
    SailingControl::printSailingReport(); // Print the sailing report
}

//************************************************************
// Get user choice within a specified range
//************************************************************
int UI::getUserChoice(int min, int max)
{
    int choice;
    while (true)
    {
        cin >> choice; // Get user input
        if (cin.fail() || choice < min || choice > max)
        {
            cin.clear();                                         // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
            return choice;                                       // Return valid choice
        }
    }
}

//************************************************************
// Get input from user with a prompt
//************************************************************
string UI::getInput(const string &prompt)
{
    string input;
    cout << prompt;      // Display the prompt
    getline(cin, input); // Get the entire line of input
    return input;        // Return the input string
}

//helper funtion that communicates with OtherControls module to create vessel
void UI::sailingCreation() 
{
    string vesselName = getInput("Enter Vessel name (max: 25 characters): ");  // getting input from useer for the name of vessel for which sailing is beingcreated
    string sailingId = getInput("Enter the sailing Id (format: xxx-dd-hh): "); // getting user input for the sailing id of this new sailing
    if (SailingControl::createSailing(sailingId, vesselName))                  // sailing successfully created
    {
        cout << "Sailing with vessel name " << vesselName << " successfully created." << endl;
    }
    else // failed to create the sailing
    {
        cout << "Failed to create sailing with vessel name " << vesselName << "." << endl;
    }
}
void UI::vesselCreation(){
    string vesselName = getInput("Enter Vessel Name (max: 25 characters): ");
    int LCLL = stod(getInput("Enter LCLL (Positive integer, max: 3600): "));
    int HCLL = stod(getInput("Enter HCLL (Positive integer, max: 3600): "));
    if (OtherControls::createVessel(vesselName, HCLL, LCLL))
    {
        cout << "Vessel successfully created." << endl;
    }
    else
    {
        cout << "Failed to create vessel." << endl;
    }
}
void UI::reservationCreation()
{
    int phoneNumber = stoi(getInput("Enter Customer Phone Number (format: 10 digits): "));
    string LicensePlate = getInput("Enter Vehicle License Number (max: 10 characters): ");
    string sailingId = getInput("Enter Sailing ID (format: xxx-dd-hh): ");
    if (OtherControls::createReservation(phoneNumber, sailingId, LicensePlate))
    {
        cout << "Reservation successfully created." << endl;
    }
    else
    {
        cout << "Failed to create reservation." << endl;
    }
}