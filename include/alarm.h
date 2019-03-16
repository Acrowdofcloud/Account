#pragma once  
/* ^^^ prevent redfining the same thing,
eg struct record is already defined by including structs.h in account.cpp,
    so the #include <structs.h> below should be ignored to prevent defining struct record again
*/

#include <structs.h>

double calin(struct record records[]);

double calout(struct record records[]);

void alarm(double budget, struct record records[]);

