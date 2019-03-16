#pragma once

#include <string>
#include "structs.h"

std::string typeofexpense();

std::string typeofincome();

void addexpense(std::string todaymonth, std::string todaydate, struct record &records);

void addincome(std::string todaymonth, std::string todaydate, struct record &records);
