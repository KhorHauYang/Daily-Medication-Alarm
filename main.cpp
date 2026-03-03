//Compiled by Tan Kian Aik
#include "patient.h"
#include "display.h"
#include <iostream>
#include <fstream>

int main() {
    // Load data from file at program start
    loadDataFromFile("data.txt");

    mainMenu();

    // Save data to file at program exit
    saveDataToFile("data.txt");

    return 0;
}