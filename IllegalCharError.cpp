#include <iostream>
#include <sstream>
#include "IllegalCharError.h"

using namespace std;

IllegalCharError::IllegalCharError(string details) {
    IllegalCharError::error_details = details;
}

IllegalCharError::IllegalCharError(char details) {
    IllegalCharError::error_details = string(1, details);
}

IllegalCharError::IllegalCharError() {
    IllegalCharError::error_details = "";
}

string IllegalCharError::as_string() {
    ostringstream result;
    result << "IllegalCharError : " << IllegalCharError::error_details;
    return result.str();
}
