#pragma once
#include <string>

///@brief Filters the text read from the QR code by removing all characters except alphanumeric ones or spaces. It also transforms all upper case characters to lower case.
///@param input QR code text
///@returns The filtered text
std::string FilterText(const std::string input);