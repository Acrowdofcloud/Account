#pragma once

#include <structs.h>

void deleterecord(struct record &records);

void printallrecords(std::string todaymonth, struct record records[]);

void printsinglerecord(struct record records);

void editrecord(struct record &records);

