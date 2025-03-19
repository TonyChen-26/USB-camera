#pragma once

#include <map>
#include <fstream>
#include <thread>
#include <chrono>

/// @brief Activates the buzzer
void EnableBuzzer();

/// @brief Disables the buzzer
void DisableBuzzer(); 

/// @brief Configures the frequency of the buzzer
/// @param freq The frequency of the buzzer
void SetBuzzerFrequency(int freq);

/// @brief Sets the duty cycle for the buzzer
/// @param duty Duty cycle value
void setDutyCycle(int duty);

/// @brief Plays the morse code of a caracter
/// @param symbol The character
void PlaySymbol(char symbol);

/// @brief Seperate the morse code into dot and dashes
/// @param c the character
void SeperateMorseCode(char c);

/// @brief Seperates each character from a string
/// @param text The string sent from the client
void PlayMorse(const std::string& text) ;