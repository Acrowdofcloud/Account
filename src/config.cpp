#include <iostream>
#include <fstream>
#include "config.h"
#include "getdate.h"

using namespace std;

void changebudget();
void changecredit();

void configmenu(){
    int con = -1;
    while (con != 0){
        printf("0. return\n");
        printf("1. Change budget   2. Change Credit Limit   3. Manage Usages   4. Manage Accounts\n");
        cin >> con;

        if (con == 1){
            changebudget();
        }
    }
}

void changebudget(){
    double oldbud, oldcre, newbud;
    ifstream fin(getmonth() + "budget.txt");
    fin >> oldbud, oldcre;
    fin.close();
    cout << "Old budget: " << oldbud << endl;
    cout << "New budget: ";
    cin >> newbud;

    ofstream fout(getmonth()+"budget.txt");
    fout << newbud << " " << oldcre;
    fout.close();

    cout << "Budget changed\n";
}
