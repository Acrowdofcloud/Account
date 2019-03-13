#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

struct record{
    string date;
    string account;
    string usage;
    bool exist = false;
    double amount;
    char type;
};

void printrecords(struct record records[]){
    for (int i = 0; i <20000; i++){
        if (records[i].exist == true){
            cout << setw(8) << records[i].date << " ";
            cout << setw(2) << records[i].type;
            cout << setw(20) << records[i].usage;
            printf("  %.2f", records[i].amount);
            cout << endl;
        }
    }
    cout << "\n";
}

void writetorecord(double budget, struct record records[]){
    ofstream fout;
    fout.open("record.txt");
    fout << budget << endl;
    for (int i = 0; i <20000; i++){
        if (records[i].exist == true){
            fout << setw(8) << records[i].date << " ";
            fout << setw(2) << records[i].type;
            fout << setw(20) << records[i].usage;
            fout << setw(8) << records[i].amount << endl;
        }
    }
    fout.close();
}

void alarm(double budget, struct record records[]){
    double totalincome, totalexpense;
    for (int i = 0; i<20000; i++){
        if (records[i].exist == true){
            if (records[i].type == 'R'){
                totalincome += records[i].amount;
            }
            else{
                totalexpense += records[i].amount;
            }
        }
    }
    if (totalexpense >= budget*0.7){
        cout << "**************************************************" << endl;
        cout << "Alert! Your expense this month is " << setprecision(3) <<  totalexpense/budget * 100 << "% of your budget!" << endl;
        cout << "**************************************************" << endl;
    }

}

int main(){
    int budget = 0;
    string tempdate, tempaccount, tempusage;
    double tempamount;
    char temptype;
    int command;
    int x;
    struct record records[20000];

    while (true){
        ifstream fin;
        int index = 0;
        fin.open("record.txt");
        fin >> budget;
        if (budget == 0){
            cout << "Whats your monthly budget?";
            cin >> budget;
        }
        while (fin >> records[index].date >> records[index].type >> records[index].usage >> records[index].amount){
            records[index].exist = true;
            index++;
        }
        fin.close();

        for (int i = 0; i<10000; i++){
            if (records[i].exist == false){
                x = i;
                break;
            }
        }

        cout << "What do you want to do?\n";
        cout << "1. Display records 2. New Expense 3. New Income 4. Edit Record 5. Statistic reports 6. Change budget 7. Exit" << endl;
        cin >> command;

        if (command == 1){
            printrecords(records);
        }
        if (command == 2){
            temptype = 'E';
            cout << "Amount?\t";
            cin >> tempamount;
            cout << "Usage?\t";
            cin.ignore();
            getline(cin, tempusage);
            if(tempamount != 0){
                records[x].date = "20190313";
                records[x].amount = tempamount;
                records[x].exist = true;
                records[x].usage = tempusage;
                records[x].type = temptype;

            }
            printrecords(records);
            cout << "\n";
        }

        if (command == 3){
            temptype = 'R';
            cout << "Amount?\n";
            cin >> tempamount;
            cout << "Usage?\n";
            cin.ignore();
            getline(cin, tempusage);
            if (tempamount != 0){
                records[x].date = "20190313";
                records[x].amount = tempamount;
                records[x].exist = true;
                records[x].usage = tempusage;
                records[x].type = temptype;
            }

            printrecords(records);
            cout << "\n";
        }



        if (command == 7){
            break;
        }

        alarm(budget, records);
        writetorecord(budget, records);
    }
    return 0;
}
