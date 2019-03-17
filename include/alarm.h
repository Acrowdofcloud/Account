#pragma once
/* ^^^ prevent redfining the same thing,
eg struct record is already defined by including structs.h in account.cpp,
    so the #include <structs.h> below should be ignored to prevent defining struct record again
*/

#include <structs.h>

double calin(std::string todaymonth, struct record records[]);

double calout(std::string todaymonth, struct record records[]);

double calcre(std::string todaymonth, struct record records[]);

void creditalarm(std::string todaymonth, double creditlim, struct record records[]);

void alarm(std::string todaymonth, double creditlim, double budget, struct record records[]);

