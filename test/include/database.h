#pragma once

#include <string>
#include <vector>
#include "class.h"

int insertRecord(record);

std::vector<record> searchRecord(std::string file,std::string field,std::string searchword);

int deleteRecord(record);

int getNumofRecords(std::string file);

record stringtoRecord(std::string&);

std::string removeAllSpace(std::string);

std::string removePrecedingSpace(std::string);

