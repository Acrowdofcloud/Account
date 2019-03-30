#pragma once
#include "class.h"
#include <vector>

using namespace std;

void editrecord(record &records);

void show10();

std::vector<record> searchAndSelectRecord();     //Interface for user to choose parameters for searchRecord(),
                                                    //and for user to select from the search result
                                                    //returns the selected records in a vector
bool fileExist(string);

void separation(int);
