//Compiled by Tan Kian Aik
#include "display.h"
#include "patient.h"
#include "alarm.h"
#include <iostream>
#include <iomanip>
#include <thread>

void displayTitle() {
    std::cout << R"(
  ███╗   ███╗███████╗██████╗     ████████╗██████╗  █████╗  ██████╗██╗  ██╗
  ████╗ ████║██╔════╝██╔══██╗    ╚══██╔══╝██╔══██╗██╔══██╗██╔════╝██║ ██╔╝
  ██╔████╔██║█████╗  ██║  ██║       ██║   ██████╔╝███████║██║     █████╔╝ 
  ██║╚██╔╝██║██╔══╝  ██║  ██║       ██║   ██╔══██╗██╔══██║██║     ██╔═██╗ 
  ██║ ╚═╝ ██║███████╗██████╔╝       ██║   ██║  ██║██║  ██║╚██████╗██║  ██╗
  ╚═╝     ╚═╝╚══════╝╚═════╝        ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝
    )" << std::endl;
}      



void displayBox(const std::string& message) {
    std::cout << "+-----------------------------------+" << std::endl;
    std::cout << message << std::endl;
    std::cout << "+-----------------------------------+" << std::endl;
}

void displayMainMenu() {
    displayBox("             MAIN MENU");
    std::cout << "| 1. Register Patient              |" << std::endl;
    std::cout << "| 2. Access Patient                |" << std::endl;
    std::cout << "| 3. Save Data to File             |" << std::endl;
    std::cout << "| 4. Exit                          |" << std::endl;
    std::cout << "+-----------------------------------+" << std::endl;
    std::cout << "Enter your choice: ";
}

void displayAddMedicationPage(const std::string& patientId) {
    displayBox("--- PATIENT: " + patients[patientId].name + " ---");
    std::cout << "| 1. Add Medication                |" << std::endl;
    std::cout << "| 2. View Schedule                 |" << std::endl;
    std::cout << "| 3. Remove Medication             |" << std::endl;
    std::cout << "| 4. Remove Patient                |" << std::endl;
    std::cout << "| 5. Return to Main Menu           |" << std::endl;
    std::cout << "+-----------------------------------+" << std::endl;
    std::cout << "Enter your choice: ";
}

// Define mainMenu
void mainMenu() {
    int choice;

    // Start the alarm system in a separate thread
    std::thread alarmThread(checkAlarms);
    alarmThread.detach();

    while (true) {
        displayTitle(); // Display fancy title
        displayMainMenu(); // Display main menu
        std::cin >> choice;

        switch (choice) {
            case 1:
                registerPatient();
                break;
            case 2:
                accessPatient();
                break;
            case 3:
                saveDataToFile("data.txt"); // Save data to file
                break;
            case 4:
                displayBox("Exiting program...");
                saveDataToFile("data.txt"); // Save data before exiting
                return;
            default:
                displayBox("Invalid choice. Please try again.");
        }
    }
}