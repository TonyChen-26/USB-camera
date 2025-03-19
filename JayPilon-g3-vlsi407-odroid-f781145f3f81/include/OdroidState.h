
#pragma once

/// @brief Activates the bouton on the Odroid
void ActivateButton();

/// @brief Reads the voltage value on the board
/// @return Returns the voltage value 
float ReadVoltage();

///@brief Verifies the state of the button
///
///@return true if the button hasn't been pressed
///@return false if the button has been pressed
bool ButtonState();

/// @brief Find in which state the Odroid is in
/// @param ADC The voltage value converted into digital
/// @param Bouton the button state
/// @return A caracter that defines in which state the Odroid is
char StateMachine(float ADC,bool Bouton);