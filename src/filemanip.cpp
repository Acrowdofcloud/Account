#include "filemanip.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "structs.h"
#include "getdate.h"

using namespace std;

void writetorecord(string todaymonth, string filename, struct record records[]){
    ofstream fout;
    system(("rm " + filename).c_str());
    fout.open(filename);
    for (int i = 0; i <2000; i++){
        if (records[i].exist == true){
            fout << setw(8) << records[i].date << " ";
            fout << setw(12) << records[i].account << " ";
            fout << setw(2) << records[i].type;
            fout << setw(20) << records[i].usage;
            fout << setw(8) << records[i].amount;
            fout << " " << records[i].notes << endl;
        }
    }
    fout.close();
}

void writeexpense(string todaymonth, double statincome, double statexpense, double Entertainment, double Transport, double Food, double Bill, double Others, double budget){
    string filename, cat;
    filename = todaymonth + "stat.txt";
    system(("rm " + todaymonth + "stat.txt").c_str());
    ofstream fout;
    fout.open(filename);
    fout << "Expenses for " << todaymonth << ": \n";
    fout << "Entertainment\t" << setw(15) << setprecision(6) << Entertainment << setw(20) << setprecision(3) << (Entertainment/statexpense) * 100 << "%\n";
    fout << "    Transport\t" << setw(15) << setprecision(6) << Transport << setw(20) << setprecision(3) << (Transport/statexpense) * 100 << "%\n";
    fout << "         Food\t" << setw(15) << setprecision(6) << Food << setw(20) << setprecision(3) << (Food/statexpense) * 100 << "%\n";
    fout << "         Bill\t" << setw(15) << setprecision(6) << Bill << setw(20) << setprecision(3) << (Bill/statexpense) * 100 << "%\n";
    fout << "       Others\t" << setw(15) << setprecision(6) << Others << setw(20) <<  setprecision(3) << (Others/statexpense) * 100 << "%\n";
    fout << "***************************************************************************\n";
    fout << "Budget: " << setprecision(6) << budget;
    fout << "\nTotal expense: " << setw(9) << setprecision(6) << statexpense << "       Total income:" << setw(8) << setprecision(6) << statincome << endl;
    fout << "Your expense in " << todaymonth << " is " << setprecision(2) << (statexpense/budget) * 100 << "% of your budget.\n";
    if (statincome < statexpense){
        fout << "You have a net loss of $" << setprecision(8) << statexpense - statincome  << " in " << todaymonth << ".\n";
    }
    else if(statincome > statexpense){
        fout << "You have a new profit of $" << setprecision(8) << statincome - statexpense << " in " << todaymonth << ".\n";
    }
    else{
        fout << "You are even this month.\n";
    }
    fout.close();
    system(("cat " + filename).c_str());
}


