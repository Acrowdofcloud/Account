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

void printrecords(struct record records[]){
    int index = 1;
    for (int i = 0; i <20000; i++){
        if (records[i].exist == true){
            cout << index << ". ";
            cout << setw(8) << records[i].date << " ";
            cout << setw(2) << records[i].type;
            cout << setw(20) << records[i].usage;
            printf("  %.2f", records[i].amount);
            cout << endl;
            index++;
        }
    }
    cout << "\n";
}


void alarm(double budget, struct record records[]){
    double totalincome = 0;
    double totalexpense = 0;
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
    cout << "Total income : $";
    printf("%.2f\n", totalincome);
    cout << "Total expense: $";
    printf("%.2f\n", totalexpense);

    if (totalexpense >= budget*0.7){
        cout << "***************************************************************************" << endl;
        cout << "Alert! Your expense this month is " << setprecision(3) <<  totalexpense/budget * 100 << "% of your budget!" << endl;
    }
    cout << "***************************************************************************" << endl;
}

int main(){
    int budget = 0;
    string tempdate, tempaccount, tempusage;
    double tempamount;
    char temptype;
    int command;
    int x;

    while (true){
        struct record records[20000] = {};
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
        cout << "1. Display records 2. New Expense      3. New Income       4. Edit Record\n";
        cout << "5. Delete Record   6. Statistic report 7. Change budget    8. Exit" << endl;
        cout << "***************************************************************************\n";
        cin >> command;

        if (command == 1){
            printrecords(records);
            alarm(budget, records);
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
            alarm(budget, records);
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
            alarm(budget, records);
        }
        if (command == 5){
            int del;
            cout << "Which record?\n";
            cout << "0. Return\n";
            printrecords(records);
            cin >> del;
            if(del != 0){
                records[del-1].exist = false;
                cout << "***************************************************************************\n";
                cout << "Record deleted\n";
                cout << "***************************************************************************\n";
            }

        }
        if (command == 8){
            break;
        }

        writetorecord(budget, records);
    }
    return 0;
}

