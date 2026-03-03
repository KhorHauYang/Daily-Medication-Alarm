#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <vector>
#include <unordered_map>


struct Medication {
    std::string name;
    int hour;
    int minute;
    std::string period;
    bool alarmRang;
};

struct Patient {
    std::string name;
    int age;
    std::string id;
    std::vector<Medication> medications;
};

extern std::unordered_map<std::string, Patient> patients;

//Wong Shou Bin
void registerPatient();
void accessPatient();

//Lock Hao Feng
void saveDataToFile(const std::string& filename);
void loadDataFromFile(const std::string& filename);

#endif