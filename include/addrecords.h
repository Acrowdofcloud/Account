#pragma once

#include <string>
#include "structs.h"

std::string typeofexpense();

std::string typeofincome();

void addexpense(std::string todaydate, struct record &records);

void addincome(std::string todaydate, struct record &records);
