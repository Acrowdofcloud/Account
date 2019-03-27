#pragma once

#include <string>
#include <vector>
#include "class.h"

int insertRecord(record);

std::vector<record> searchRecord(std::string,std::string);

int deleteRecord(record);

int getNumofRecords(std::string);

record stringtoRecord(std::string&);

std::string remove_all_space(std::string);

