#pragma once
#include "class.h"
#include <vector>

using namespace std;

void editrecord(record &records);

void show10();

std::vector<record> search_and_select_record();

bool file_exist(string);

void separation(int);
