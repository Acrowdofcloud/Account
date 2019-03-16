#pragma once

#include <string>

struct record{
    std::string date;
    std::string account;
    std::string usage;
    bool exist = false;
    double amount;
    char type;
    std::string notes;
};

