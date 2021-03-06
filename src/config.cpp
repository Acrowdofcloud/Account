#include <iostream>
#include <fstream>
#include "config.h"
#include "getdate.h"
#include "global.h"

using namespace std;

void changebudget();
void changecredit();

void configmenu(){
    int con = -1;
    while (con != 0){
        separation(105);
        printf("Configuration Menu: \n");
        printf("0. Return\n");
        printf("1. Change budget   2. Change Credit Limit\n");
        separation(105);
        cin >> con;

        if (con == 1){
            changebudget();
        }
        else if( con== 2){
            changecredit();
        }
    }
}

void changebudget(){//allow user to change the budget for current month
    double oldbud, oldcre, newbud;
    ifstream fin(getmonth() + "budget.txt");
    fin >> oldbud >> oldcre;//get original budget and credit limit
    fin.close();
    cout << "Old budget: " << oldbud << endl;
    cout << "New budget: ";
    cin >> newbud; //get new budget

    ofstream fout(getmonth()+"budget.txt");//cover the old budget and credit limit
    fout << newbud << " " << oldcre;
    fout.close();
    separation(105);
    cout << "Budget changed\n";
}

void changecredit(){//comments are pretty much the same as function changebudget()
    double oldbud, oldcre, newcre;
    ifstream fin(getmonth() + "budget.txt");
    fin >> oldbud >> oldcre;
    fin.close();
    cout << "Old Credit Limit: " << oldcre << endl;
    cout << "New Credit Limit: ";
    cin >> newcre;

    ofstream fout(getmonth()+"budget.txt");
    fout << oldbud << " " << newcre;
    fout.close();
    separation(105);
    cout << "Budget changed\n";
}
