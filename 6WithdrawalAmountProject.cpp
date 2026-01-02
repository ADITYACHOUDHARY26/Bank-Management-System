#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
    long long seraccno;
    int serPin;
    float Amount;
    float Newamount;

    cout << " " << endl;
    cout << "Enter Your Account Number :: ";
    cin >> seraccno;

    cout << " " << endl;
    cout << "Enter your 4-digit PIN :: ";
    cin >> serPin;

    ifstream file("6BankData.txt");
    ofstream file1("6BnakDataCopy.txt");

    if (!file || !file1)
    {
        cout << "FILE NOT OPEN...!" << endl;
        return 0;
    }

    string line;
    bool update = false;

    while (getline(file, line))
    {
        long long Accno = stoll(line.substr(0, 20));
        int Pin = stoi(line.substr(32, 6));
        float Withdrawal;

        if (Accno == seraccno && Pin == serPin)
        {

            Amount = stof(line.substr(128, 10));
            cout << "\nCurrent Amount :: " << Amount;

            cout << " " << endl;
            cout << "\nEnter Your Withdrawal Amount :: ";
            cin >> Withdrawal;

            Amount -= Withdrawal;

            cout << "\nUpdated Amount :: " << Amount;
            file1 << line.substr(0, 128)
                  << left << setw(10) << Amount << endl;
            update = true;
        }
        else
        {
            file1 << line << endl;
        }
    }

    file.close();
    file1.close();

    remove("6BankData.txt");
    rename("6BnakDataCopy.txt", "6BankData.txt");

    if (update)
    {
        cout << " " << endl;
        cout << "\nWithdrawal Amount Successfully...!" << endl;
        cout << " " << endl;
    }
    else
        cout << "\nAccount Number || Pin Number worng...!" << endl;

    return 0;
}