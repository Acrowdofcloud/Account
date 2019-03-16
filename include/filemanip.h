#pragma once

#include <structs.h>

void writetorecord(std::string todaymonth, std::string filename, struct record records[]);

void writeexpense(std::string todaymonth, double statincome, double statexpense, double Entertainment, double Transport, double Food, double Bill, double Others, double budget);

