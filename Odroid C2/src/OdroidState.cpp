#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "OdroidState.h"
#include <unistd.h>

/*
 * Configures GPIO ping 228 for input operation on a Linux system, used for button reading. 
 * It exports GPIO pin 228, making it available for use and then sets the direction to input
 * allowing it to read signals.
 */
void ActivateButton() {
    // Export GPIO pin 228
    std::ofstream export_file("/sys/class/gpio/export");
    if (export_file.is_open()) {
        export_file << "228";  // Export GPIO pin 228
        export_file.close();
        std::cout << "GPIO pin 228 exported." << std::endl;
    } else {
        std::cerr << "Failed to open /sys/class/gpio/export for writing!" << std::endl;
    }

    // Set GPIO pin 228 as input
    std::ofstream direction_file("/sys/class/gpio/gpio228/direction");
    if (direction_file.is_open()) {
        direction_file << "in";  // Set direction to input
        direction_file.close();
        std::cout << "GPIO pin 228 set as input." << std::endl;
    } else {
        std::cerr << "Failed to open /sys/class/gpio/gpio228/direction for writing!" << std::endl;
    }
}

/*
 * Reads the raw ADC value from the file /sys/class/saradc/ch0. It returns the ADC value as a
 * floating point number. The function pauses briefly to avoid frying the resistor on the PCB 
 * board.
 */
float ReadVoltage(){
    std::string adc_file_path = "/sys/class/saradc/ch0";
    std::ifstream adc_file(adc_file_path);
    float adc_value = 0;
    adc_file >> adc_value;
    sleep(0.1);
    adc_file.close();
    return adc_value;
}

/*
 * This function reads the current state of a button connected to GPIO pin 228. The function reads
 * GPIO's pin value from the file /sys/class/gpio/gpio228/value and returns false if the button is
 * pressed and true if the button is not pressed.
 */
bool ButtonState(){
    std::string bouton_file_path = "/sys/class/gpio/gpio228/value";
    std::ifstream bouton_file(bouton_file_path);
    bool bouton_value = 0;
    bouton_file >> bouton_value;
    bouton_file.close();
    return bouton_value;
}


/*
 * Find in which state the server is depending if the button is pressed or if the photoresistor
 * is active or not. This function returns a char depending in which states it's in.
 */
char StateMachine(float ADC, bool Bouton) {
    // Populate message based on ADC and Bouton
    if (ADC < 1000 && !Bouton) {
        return 'z';
    }
    else if (ADC < 1000) {
        return 'b';
    }
    else if (ADC > 1000) {
        return 'n';
    }
}