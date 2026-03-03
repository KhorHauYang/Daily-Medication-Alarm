#include "patient.h"
#include "display.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::unordered_map<std::string, Patient> patients;

void registerPatient() {
    Patient patient;
    std::string id;

    displayBox("--- REGISTER PATIENT ---");
    std::cout << "Enter patient's ID number: ";
    std::cin >> id;

    // Check if patient already exists
    if (patients.find(id) != patients.end()) {
        displayBox("Patient already exists.");
        return;
    }

    std::cout << "Enter patient's name: ";
    std::cin.ignore();
    std::getline(std::cin, patient.name);

    std::cout << "Enter patient's age: ";
    std::cin >> patient.age;

    patient.id = id;
    patients[id] = patient;
    displayBox("Patient registered successfully!");
}

void accessPatient() {
    std::string id;

    displayBox("--- ACCESS PATIENT ---");
    std::cout << "Enter patient's ID number: ";
    std::cin >> id;

    if (patients.find(id) == patients.end()) {
        displayBox("Patient not found.");
        return;
    }

    int choice;
    while (true) {
        displayAddMedicationPage(id);
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Medication med;
                std::string time;

                std::cout << "Enter the name of the medication: ";
                std::cin.ignore();
                std::getline(std::cin, med.name);

                std::cout << "Enter the time for the alarm (e.g., 08:00 AM): ";
                std::getline(std::cin, time);

                // Parse the time
                if (time.length() != 8 || time[2] != ':' || time[5] != ' ') {
                    displayBox("Invalid time format. Please use HH:MM AM/PM.");
                    break;
                }

                med.hour = std::stoi(time.substr(0, 2));
                med.minute = std::stoi(time.substr(3, 2));
                med.period = time.substr(6, 2);
                med.alarmRang = false;

                patients[id].medications.push_back(med);
                displayBox("Medication added successfully!");
                break;
            }
            case 2: {
                displayBox("--- MEDICATION SCHEDULE ---");
                for (const auto& med : patients[id].medications) {
                    std::cout << "Medication: " << med.name << " | Time: " << med.hour << ":" << std::setw(2) << std::setfill('0') << med.minute << " " << med.period << "\n";
                }
                break;
            }
            case 3: {
                std::string medName;
                std::cout << "Enter the name of the medication to remove: ";
                std::cin.ignore();
                std::getline(std::cin, medName);

                auto& meds = patients[id].medications;
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
                break;
            }
            case 4: {
                patients.erase(id);
                displayBox("Patient removed successfully!");
                return;
            }
            case 5:
                return;
            default:
                displayBox("Invalid choice. Please try again.");
        }
    }
}

void saveDataToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        displayBox("Error: Unable to save data to file.");
        return;
    }

    // Add a header to describe the file format
    file << "Patient Data Format:\n";
    file << "Patient ID, Name, Age\n";
    file << "  Medication: Name, Hour, Minute, Period, Alarm Rang\n";
    file << "----------------------------------------------------\n";

    for (const auto& patient : patients) {
        // Save patient details
        file << patient.second.id << ", " << patient.second.name << ", " << patient.second.age << "\n";

        // Save medications for the patient
        for (const auto& med : patient.second.medications) {
            file << "  Medication: " << med.name << ", " << med.hour << ", " << med.minute << ", " << med.period << ", " << (med.alarmRang ? "Yes" : "No") << "\n";
        }

        file << "\n"; // Add a blank line between patients
    }

    file.close();
    displayBox("Data saved to file successfully!");
}

void loadDataFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        displayBox("Error: Unable to load data from file.");
        return;
    }

    patients.clear(); // Clear existing data

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, name, ageStr;
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, ageStr, ',');

        // Skip empty lines or lines with missing data
        if (id.empty() || name.empty() || ageStr.empty()) {
            continue;
        }

        // Validate age (must be a valid integer)
        int age = 0;
        try {
            age = std::stoi(ageStr);
        } catch (const std::invalid_argument& e) {
            displayBox("Invalid age in data file. Skipping patient: " + id);
            continue;
        }

        Patient patient;
        patient.id = id;
        patient.name = name;
        patient.age = age;

        while (ss.good()) {
            Medication med;
            std::string medName, hourStr, minuteStr, period, alarmRangStr;
            std::getline(ss, medName, ',');
            std::getline(ss, hourStr, ',');
            std::getline(ss, minuteStr, ',');
            std::getline(ss, period, ',');
            std::getline(ss, alarmRangStr, ',');

            // Skip if medication data is incomplete
            if (medName.empty() || hourStr.empty() || minuteStr.empty() || period.empty() || alarmRangStr.empty()) {
                continue;
            }

            // Validate hour, minute, and alarmRang
            try {
                med.name = medName;
                med.hour = std::stoi(hourStr);
                med.minute = std::stoi(minuteStr);
                med.period = period;
                med.alarmRang = (alarmRangStr == "1" || alarmRangStr == "Yes");
            } catch (const std::invalid_argument& e) {
                displayBox("Invalid medication data in file. Skipping medication for patient: " + id);
                continue;
            }

            patient.medications.push_back(med);
        }

        patients[id] = patient;
    }

    file.close();
    displayBox("Data loaded from file successfully!");
}