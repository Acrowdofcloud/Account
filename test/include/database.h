#pragma once

#include <string>
#include <vector>
#include "class.h"

int insertRecord(record);

std::vector<record> searchRecord(std::string file,std::string field,std::string searchword);

int deleteRecord(record);

int getNumofRecords(std::string);

record stringtoRecord(std::string&);

std::string remove_all_space(std::string);

std::string remove_preceding_space(std::string input);

