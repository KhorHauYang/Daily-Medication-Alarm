# Daily Medication Alarm System

> **A multithreaded C++ console application designed to manage patient data and schedule precise daily medication alerts.**

This project was developed as a collaborative effort by Group 10 for the EEE 123 (Computer Programming for Engineers) course at Universiti Sains Malaysia. The system addresses a critical healthcare issue by providing timely, reliable reminders to patients managing complex treatment plans, thereby reducing the risk of missed doses and improving treatment efficacy.

---

## 🚀 Key Features

* **Robust Patient Management:** Add, edit, and safely store patient information (ID, Name, Age).
* **Intelligent Medication Tracking:** Track individual medication schedules down to the minute, including frequency/period details.
* **Real-Time Multithreaded Alarm:** Utilizes background processing to continuously monitor the system clock and trigger alerts at the exact specified times without blocking user interactions.
* **Persistent Data Storage:** Implements seamless C++ File I/O to save and load patient data using a custom `Data.txt` format, ensuring no information is lost between sessions.
* **Modular Architecture:** Designed with clean object-oriented principles, separating the interface (`display.h`), logic (`patient.h`), and execution (`Main.cpp`).

## 🛠️ Technology Stack

* **Language:** C++
* **Concepts Applied:**
    * Object-Oriented Programming (OOP)
    * File Input/Output (I/O) Parsing
    * Multithreading & Concurrency
    * Dynamic Data Structures (Vectors/Maps)
    * Error Handling & Input Validation

## 💻 System Architecture

The project is divided into specialized modules for maintainability and scalability:

* **`Main.cpp`**: The core driver of the application, responsible for initializing the system and managing the data load/save lifecycle.
* **`patient.cpp` / `patient.h`**: Manages the core data structures (Patient and Medication objects) and contains the logic for the `saveDataToFile` and `loadDataFromFile` functions.
* **`display.cpp` / `display.h`**: Handles all user interface elements, menu rendering, and input sanitization.
* **`alarm.cpp` / `alarm.h`**: Manages the multithreaded clock monitoring and alert execution.
* **`Data.txt`**: The localized database utilizing a custom CSV-style parsing structure.
