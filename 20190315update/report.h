#include <iostream>
#include <fstream>
using namespace std;

void profitstat(double budget, double statexpense, struct record records[]){
    double Entertainment = 0;
    double Food = 0;
    double Bill = 0;
    double Others = 0;
    double Transport = 0;
    string types;
    double statincome = calin(records);
    for (int i = 0; i < 20000; i++){
        if (records[i].exist == true){
            if (records[i].usage == "Entertainment"){
                Entertainment += records[i].amount;
            }
            if (records[i].usage == "Others"){
                Others += records[i].amount;
            }
            if (records[i].usage == "Bill"){
                Bill += records[i].amount;
            }
            if (records[i].usage == "Transport"){
                Transport += records[i].amount;
            }
            if (records[i].usage == "Food"){
                Food += records[i].amount;
            }
        }
    }
    if (statexpense == 0){
        cout << "You've got no expenses for this month.\n";
    }
    else{
        writeexpense(statexpense, Entertainment, Transport, Food, Bill, Others, budget);
        cout << "\nTotal expense: " << setw(9) << statexpense << "     Budget: " << setw(9) << budget << endl;
        cout << "Your expense this month is " << setprecision(4) << (statexpense/budget) * 100 << "% of your budget.\n";
    }
    if (statincome < statexpense){
        cout << "You have a net loss of $" << setprecision(8) << statexpense - statincome  << " this month.\n";
    }
    else if(statincome > statexpense){
        cout << "You have a new profit of $" << setprecision(8) << statincome - statexpense << " this month.\n";
    }
    else{
        cout << "You are even this month.\n";
    }
    cout << "***************************************************************************\n";


}

void report(double budget, struct record records[]){
    double statexpense = calout(records);
    profitstat(budget, statexpense, records);

}
