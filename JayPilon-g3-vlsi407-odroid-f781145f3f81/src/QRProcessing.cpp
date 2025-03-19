#include <map>
#include <fstream>
#include <thread>
#include <chrono>
#include <iostream>
#include "QRProcessing.h"
std::map<char, std::string> morse_code = {
    {'a', ".-"}, {'b', "-..."}, {'c', "-.-."}, {'d', "-.."}, {'e', "."},
    {'f', "..-."}, {'g', "--."}, {'h', "...."}, {'i', ".."}, {'j', ".---"},
    {'k', "-.-"}, {'l', ".-.."}, {'m', "--"}, {'n', "-."}, {'o', "---"},
    {'p', ".--."}, {'q', "--.-"}, {'r', ".-."}, {'s', "..."}, {'t', "-"},
    {'u', "..-"}, {'v', "...-"}, {'w', ".--"}, {'x', "-..-"}, {'y', "-.--"},
    {'z', "--.."},
    {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"}, {'5', "....."},
    {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."}, {'0', "-----"},
    {' ', "/"}  
};

const auto DIT_DURATION = 60;        // Durée d'un "dit"
const auto DAH_DURATION = 180;       // Durée d'un "dah"
const auto CHARACTER_PAUSE = 300;   // Pause entre les caractères (5 dits)
const auto WORD_PAUSE = 480;        // Pause entre les mots (8 dits)
const auto INTER_SYMBOL_PAUSE = 120;

// Enables the buzzer on the Odroid
void EnableBuzzer() {
    std::ofstream enable_file("/sys/devices/pwm-ctrl.42/enable0");
    enable_file << "1"; 
    enable_file.close();
}

// Disables the buzzer on the Odroid
void DisableBuzzer() {
    std::ofstream enable_file("/sys/devices/pwm-ctrl.42/enable0");
    enable_file << "0";
    enable_file.close();
}

// Sets the frequency on the buzzer
void SetBuzzerFrequency(int freq) {
    std::ofstream freq_file("/sys/devices/pwm-ctrl.42/freq0");
    freq_file << freq; 
    freq_file.close();
}

void setDutyCycle(int duty) {
    std::ofstream duty_file("/sys/devices/pwm-ctrl.42/duty0");
    duty_file << duty;
    duty_file.close();

}

// Plays a dit or dah 
void PlaySymbol(char symbol) {
    if (symbol == '.') {
        EnableBuzzer();
        std::this_thread::sleep_for(std::chrono::milliseconds(DIT_DURATION));
        DisableBuzzer();
    } else if (symbol == '-') {
        EnableBuzzer();
        std::this_thread::sleep_for(std::chrono::milliseconds(DAH_DURATION));
        DisableBuzzer();
    }
}

// Transforms the character into a morse code and calls PlaySymbol for every dits and dahs
void SeperateMorseCode(char c) {
    auto morse = morse_code[c];
    
    for (char symbol : morse) {
        PlaySymbol(symbol); 
        std::this_thread::sleep_for(std::chrono::milliseconds(INTER_SYMBOL_PAUSE)); 
    }
}

// Seperates the QR text into individual characters and calls SeperateMorseCode to output a dit or dah on 
// the buzzer
void PlayMorse(const std::string& text) {
    SetBuzzerFrequency(660);
    setDutyCycle(512);
    for (char c : text) {
        if (morse_code.find(c) != morse_code.end()) { 
            SeperateMorseCode(c); 
            std::this_thread::sleep_for(std::chrono::milliseconds(CHARACTER_PAUSE)); 
        }
        else if (c == ' ') {
            std::this_thread::sleep_for(std::chrono::milliseconds(WORD_PAUSE));
        }
    }
    EnableBuzzer();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    DisableBuzzer();
}