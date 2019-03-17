#pragma once

#include <structs.h>

void writetorecord(std::string todaymonth, std::string filename, struct record records[]);

void writereport(std::string todaymonth, double statincome, double statexpense, double Entertainment, double Transport, double Food, double Bill, double Others, double creditlim, double budget);

void writecredit(std::string, double, struct record records[]);

void writeaccount(std::string, double, double, double, double, double, double, double);
