//Compiled by Tan Kian Aik
#include "alarm.h"
#include "display.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#endif

void checkAlarms() {
    int lastCheckedDay = -1; // Track the last day the alarms were checked

    while (true) {
        time_t now = time(0);
        tm* localTime = localtime(&now);
        int currentDay = localTime->tm_mday; // Get the current day of the month

        // Reset alarmRang flags at the start of a new day
        if (currentDay != lastCheckedDay) {
            for (auto& patient : patients) {
                for (auto& med : patient.second.medications) {
                    med.alarmRang = false; // Reset the alarm flag
                }
            }
            lastCheckedDay = currentDay; // Update the last checked day
        }

        // Check for alarms
        for (auto& patient : patients) {
            for (auto& med : patient.second.medications) {
                if (!med.alarmRang) {
                    int currentHour = localTime->tm_hour;
                    int currentMinute = localTime->tm_min;
                    std::string currentPeriod = (currentHour < 12) ? "AM" : "PM";

                    // Convert to 12-hour format
                    if (currentHour > 12) currentHour -= 12;
                    if (currentHour == 0) currentHour = 12;

                    if (currentHour == med.hour && currentMinute == med.minute && currentPeriod == med.period) {
                        // Mark the alarm as rang immediately
                        med.alarmRang = true;

                        // Display the alarm message
                        std::cout << "\n";
                        displayBox(patient.second.name + " needs to take " + med.name + "!");

                        // Cross-platform beep sound
#ifdef _WIN32
                        Beep(1000, 3000);  // Beep on Windows
#else
                        std::cout << "\a";  // Beep on Linux/Mac
#endif

                        // Add a small delay to prevent multiple triggers
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                    }
                }
            }
        }

        // Check every second
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}