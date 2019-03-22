#include <fstream>
#include "test.h"
#include "getdate.h"
using namespace std;

void toRecord(record records){
    ofstream fout;
    fout.open(records.getDate().substr(0,6) + ".txt", ios::app);
    fout << records.toString() << endl;
    fout.close();
}
