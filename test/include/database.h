#pragma once

#include <string>
#include "test.h"

void insertRecord(record);

int deleteRecord(record);

int getNumofRecords(std::string);

record stringtoRecord(std::string&);

std::string remove_all_space(std::string);

