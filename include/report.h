#pragma once

#include "structs.h"

void profitstat(std::string todaymonth, double budget, double statexpense, struct record records[]);

void accountstat(std::string, double, struct record*);

void report(std::string todaymonth, double creditlim, double budget, struct record records[]);
