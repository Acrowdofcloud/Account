#include "filemanip.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "structs.h"
#include "getdate.h"

using namespace std;

void writetorecord(struct record records[]){
    ofstream fout;
    system("rm record.txt");
    fout.open("record.txt");
    for (int i = 0; i <2000; i++){
        if (records[i].exist == true){
            fout << setw(8) << records[i].date << " ";
            fout << setw(12) << records[i].account << " ";
            fout << setw(2) << records[i].type;
            fout << setw(20) << records[i].usage;
            fout << setw(8) << records[i].amount;
            fout << records[i].notes << endl;
        }
    }
    fout.close();
}

void writeexpense(double statexpense, double Entertainment, double Transport, double Food, double Bill, double Others, double budget){
    string filename, cat;
    filename = getmonth() + "stat.txt";
    system(("rm " + filename).c_str());
    ofstream fout;
    fout.open(filename);
    fout << "Entertainment\t" << setw(8) << Entertainment << "\t\t" << setprecision(3) << (Entertainment/statexpense) * 100 << "%\n";
    fout << "    Transport\t" << setw(8) << Transport << "\t\t" << setprecision(3) << (Transport/statexpense) * 100 << "%\n";
    fout << "         Food\t" << setw(8) << Food << "\t\t" << setprecision(3) << (Food/statexpense) * 100 << "%\n";
    fout << "         Bill\t" << setw(8) << Bill << "\t\t" << setprecision(3) << (Bill/statexpense) * 100 << "%\n";
    fout << "       Others\t" << setw(8) << Others << "\t\t" <<  setprecision(3) << (Others/statexpense) * 100 << "%\n";
    fout.close();
    cout << "Expenses for " << getmonth() << ": \n";
    system(("cat " + filename).c_str());
}


