//Compiled by Tan Kian Aik
#include "medication.h"
#include "display.h"
#include <iostream>
#include <iomanip>

void addMedication(const std::string& patientId) {
    Medication med;
    std::string time;

    std::cout << "Enter the name of the medication: ";
    std::cin.ignore();
    std::getline(std::cin, med.name);

    // Loop until a valid time is entered
    while (true) {
        std::cout << "Enter the time for the alarm (e.g., 08:00 AM): ";
        std::getline(std::cin, time);

        // Validate the time format
        if (time.length() != 8 || time[2] != ':' || time[5] != ' ' ) {
            displayBox("Invalid time format. Please use HH:MM AM/PM.");
            continue; // Ask for input again
        }

        // Extract hour, minute, and period
        std::string hourStr = time.substr(0, 2);
        std::string minuteStr = time.substr(3, 2);
        std::string period = time.substr(6, 2);

        // Convert hour and minute to integers
        int hour = std::stoi(hourStr);
        int minute = std::stoi(minuteStr);

        // Validate hour (01-12)
        if (hour < 1 || hour > 12) {
            displayBox("Invalid hour. Please use a value between 01 and 12.");
            continue; // Ask for input again
        }

        // Validate minute (00-59)
        if (minute < 0 || minute > 59) {
            displayBox("Invalid minute. Please use a value between 00 and 59.");
            continue; // Ask for input again
        }

        // Validate period (AM or PM)
        if (period != "AM" && period != "PM") {
            displayBox("Invalid period. Please use AM or PM.");
            continue; // Ask for input again
        }

        // If all checks pass, break the loop
        break;
    }

    // Parse the time
    med.hour = std::stoi(time.substr(0, 2));
    med.minute = std::stoi(time.substr(3, 2));
    med.period = time.substr(6, 2);
    med.alarmRang = false;

    // Add the medication to the patient's list
    patients[patientId].medications.push_back(med);
    displayBox("Medication added successfully!");
}


void viewSchedule(const std::string& patientId) {
    if (patients.find(patientId) == patients.end()) {
        displayBox("Patient not found.");
        return;
    }

    const auto& medications = patients[patientId].medications;

    if (medications.empty()) {
        displayBox("There is no medication alarm set.");
    } else {
        displayBox("     --- MEDICATION SCHEDULE ---");
        for (const auto& med : medications) {
            std::cout << "Medication: " << med.name << " | Time: " << med.hour << ":" 
                      << std::setw(2) << std::setfill('0') << med.minute << " " << med.period << "\n";
        }
    }
}

/*void removeMedication(const std::string& patientId) {
    std::string medName;
    std::cout << "Enter the name of the medication to remove: ";
    std::cin.ignore();
    std::getline(std::cin, medName);

    auto& meds = patients[patientId].medications;
    auto it = meds.begin();
    while (it != meds.end()) {
        if (it->name == medName) {
            it = meds.erase(it);
            displayBox("Medication removed successfully!");
            break;
        } else {
            ++it;
        }
    }
    if (it == meds.end()) {
        displayBox("Medication not found.");
    }
}*/

void removeMedication(const std::string& patientId) {
    if (patients.find(patientId) == patients.end()) {
        displayBox("Patient not found.");
        return;
    }

    auto& meds = patients[patientId].medications;

    // Check if there are any medications to remove
    if (meds.empty()) {
        displayBox("There are no medications to remove.");
        return;
    }

    // Display all medications for the patient
    displayBox("--- MEDICATION SCHEDULE ---");
    for (size_t i = 0; i < meds.size(); i++) {
        std::cout << (i + 1) << ". Medication: " << meds[i].name 
                  << " | Time: " << meds[i].hour << ":" 
                  << std::setw(2) << std::setfill('0') << meds[i].minute 
                  << " " << meds[i].period << "\n";
    }

    // Ask the user which medication to remove
    int choice;
    std::cout << "Enter the number of the medication to remove (or 0 to cancel): ";
    std::cin >> choice;

    // Validate the user's choice
    if (choice == 0) {
        displayBox("Medication removal canceled.");
    } else if (choice > 0 && choice <= static_cast<int>(meds.size())) {
        // Remove the selected medication
        meds.erase(meds.begin() + (choice - 1));
        displayBox("Medication removed successfully!");
    } else {
        displayBox("Invalid choice. Please try again.");
    }
}