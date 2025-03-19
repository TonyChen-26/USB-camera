#include <string>

/*
 * Filters the text from by removing all characaters that aren't alphanumeric or space. It also
 * converts upper case letters to lower case.
 */
std::string FilterText(const std::string input){

    std::string filtered;
    for (char c : input) {
        if (std::isalnum(c) || c == ' ') {  // Keep alphanumeric characters and spaces
            filtered += tolower(c);   // Convert to lowercase if it is a letter
        }
    }
    return filtered;
}