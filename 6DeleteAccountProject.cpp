#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
    long long SerAcc;
    int SerPin;

    cout << " " << endl;
    cout << "Enter Your Account Number :: ";
    cin >> SerAcc;

    cout << "Enter your 4-digit PIN :: ";
    cin >> SerPin;

    ifstream file("6BankData.txt");
    ofstream file1("6CopyBankData.txt");

    if (!file || !file1)
    {
        cout << "FILE NOT OPEN..!" << endl;
        return 0;
    }

    string line;
    bool deleted = false;

    while (getline(file, line))
    {
        long long Accno = stoll(line.substr(0, 20));
        int Pin = stoi(line.substr(32, 6));

        if (Accno == SerAcc && Pin == SerPin)
        {

            deleted = true;
            continue;
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

    if (deleted)
    {

        cout << "\nAccount Deleted Successfully...!" << endl;
    }
    else
    {
        cout << "\n\nAccount Number || Pin Number worng...!" << endl;
    }

    return 0;
}