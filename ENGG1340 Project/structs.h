#include <string>
using namespace std;

struct record{
    string date;
    string account;
    string usage;
    bool exist = false;
    double amount;
    char type;
    string notes;
};
