//
// Created by denis on 14.03.2021.
//

#include "CheckString.h"
#include "regex"

bool CheckString::isDouble(const std::string& data) {
    auto checkDouble = std::regex("[-]?[\\d]+,?[\\d]*");
    return std::regex_match(data, checkDouble);
}
