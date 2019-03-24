#pragma once

#include <string>
#include "test.h"

int insertRecord(record);

//int searchRecord(std::string,std::string);

int deleteRecord(record);

int getNumofRecords(std::string);

record stringtoRecord(std::string&);

std::string remove_all_space(std::string);

