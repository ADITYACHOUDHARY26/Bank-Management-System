#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
    long long seraccount;
    float newamount;
    float Amount;

    cout << "Enter Your Account Number :: ";
    cin >> seraccount;

    cout << "Enter Amount To Deposit   :: ";
    cin >> newamount;

    ifstream file("6BankData.txt");
    ofstream file1("6CopyBankData.txt");

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

        if (Accno == seraccount)
        {
            Amount = stof(line.substr(128, 10));
            cout << "\nCurrent Amount :: " << Amount;

            Amount += newamount;

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
    rename("6CopyBankData.txt", "6BankData.txt");

    if (update)
    {
        cout << "\n Amount Updated Successfully...!" << endl;
    }
    else
        cout << "\nAccount Number worng...!" << endl;

    return 0;
}