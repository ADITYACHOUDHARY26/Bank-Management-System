#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

class Temp
{
    fstream file, file1;

public:
    void CreateAccount();
    void DepositAmount();
    void WithdrawalAmount();
    void CheckInfo();
    void DeleteAccount();
} obj;

int main()
{
    char choice;
    char option;
    long long ACCNO;

    cout << " " << endl;
    cout << "======================= BANK MANAGEMENT SYSTEM =======================" << endl;
    cout << " " << endl;
    cout << "\n# CREATE ACCOUNT :: PRESS 1 ::" << endl;
    cout << "\n# LOGIN ACCOUNT  :: PRESS 2 ::" << endl;
    cout << "\n# EXIT           :: PRESS 0 ::" << endl;
    cout << " " << endl;
    cout << "======================================================================" << endl;
    cout << " " << endl;
    cout << "* Please Select An Option From Above => ";

    cin >> choice;
    cin.ignore();
    cout << " " << endl;

    switch (choice)
    {
    case '1':
        obj.CreateAccount();
        break;

    case '2':
    {
        cout << "* Enter your Account Number :: ";
        cin >> ACCNO;

        ifstream file("6BankData.txt");

        if (!file)
        {
            cout << "FILE NOT OPEN....!" << endl;
            return 0;
        }

        string line;
        bool found = false;

        while (getline(file, line))
        {
            if (line.length() < 20)
                continue;

            long long Accno = stoll(line.substr(0, 20));

            if (ACCNO == Accno)
            {
                found = true;

                cout << " " << endl;
                cout << "----------------------------------------------------------------------" << endl;
                cout << "                      ACCOUNT LOGIN SUCCESSFULLY                      " << endl;
                cout << " " << endl;
                cout << "Your Account Number :: " << Accno << endl;
                cout << " " << endl;
                cout << "\n# DEPOSIT AMOUNT            :: PRESS 1 :: " << endl;
                cout << "\n# WITHDRAWAL AMOUNT         :: PRESS 2 :: " << endl;
                cout << "\n# CHECK ACCOUNT INFORMATION :: PRESS 3 :: " << endl;
                cout << "\n# DELETE ACCOUNT            :: PRESS 4 :: " << endl;
                cout << "\n# EXIT                      :: PRESS 0 :: " << endl;
                cout << " " << endl;
                cout << "----------------------------------------------------------------------" << endl;
                cout << " " << endl;
                cout << "* Please Select An Option From Above => ";

                cin >> option;
                cin.ignore();
                cout << " " << endl;

                switch (option)
                {
                case '1':
                    obj.DepositAmount();
                    break;
                case '2':
                    obj.WithdrawalAmount();
                    break;
                case '3':
                    obj.CheckInfo();
                    break;
                case '4':
                    obj.DeleteAccount();
                    break;
                case '0':
                    return 0;
                    break;
                default:
                    cout << "Invalid Selection...!";
                    break;
                }

                break;
            }
        }

        if (!found)
            cout << "\nAccount Not Found...!" << endl;

        file.close();
    }
    break;

    case '0':
        return 0;
        break;

    default:
        cout << "Invalid Selection...!";
        break;
    }

    return 0;
}

void Temp::CreateAccount()
{

    long long Accno = 0;
    string Ifsc = "SBI";

    char Name[25];
    char Fname[25];
    char Pno[11];
    char Email[30];
    char Pin[5];
    float Amount;

    srand(time(0));
    for (int i = 0; i < 12; i++)
    {
        Accno = Accno * 10 + rand() % 10;
    }

    srand(time(0));
    for (int i = 0; i < 7; i++)
    {
        Ifsc += to_string(rand() % 10);
    }

    cout << "----------------------------------------------------------------------" << endl;
    cout << "                           CREATING ACCOUNT                           " << endl;
    cout << "                     Please Enter your Information                    " << endl;
    cout << " " << endl;
    cout << "Enter name             :: ";
    cin.getline(Name, 25);

    cout << "Enter Father name      :: ";
    cin.getline(Fname, 25);

    cout << "Enter Phone Number     :: ";
    cin >> Pno;

    cout << "Enter Email ID         :: ";
    cin >> Email;

    cout << "Enter your 4-digit PIN :: ";
    cin >> Pin;

    cout << "Enter Amount           :: ";
    cin >> Amount;

    cout << " " << endl;
    cout << "----------------------------------------------------------------------" << endl;
    cout << " " << endl;
    cout << "YOUR ACCOUNT IS SUCCESSFULLY CREATED....!" << endl;
    cout << " " << endl;
    cout << "Account Number :: " << Accno << endl;
    cout << "IFSC CODE :: " << Ifsc << endl;
    cout << "Please Save It....!" << endl;
    cout << " " << endl;
    cout << "THANK YOU FOR YOUR VISIT TODAY...!" << endl;
    cout << " " << endl;
    cout << "----------------------------------------------------------------------" << endl;
    cout << " " << endl;

    fstream file;

    file.open("6BankData.txt", ios ::out | ios ::app);
    file << left
         << setw(20) << Accno
         << setw(12) << Ifsc
         << setw(6) << Pin
         << setw(25) << Name
         << setw(25) << Fname
         << setw(15) << Pno
         << setw(25) << Email
         << setw(10) << Amount << endl;
    file.close();
}

void Temp::DepositAmount()
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
}

void Temp::WithdrawalAmount()
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
        return;
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
}

void Temp::CheckInfo()
{
    long long searchAcc;
    int searchPin;

    cout << "Enter Account Number :: ";
    cin >> searchAcc;

    cout << "Enter your 4-digit PIN :: ";
    cin >> searchPin;

    ifstream file("6BankData.txt");

    if (!file)
    {
        cout << "FILE NOT OPEN....!" << endl;
        return;
    }

    bool found = false;
    string line;

    while (getline(file, line))
    {
        if (line.length() < 100)
            continue;

        long long Accno = stoll(line.substr(0, 20));
        string Ifsc = line.substr(20, 12);
        int Pin = stoi(line.substr(32, 6));
        string Name = line.substr(38, 25);
        string Fname = line.substr(63, 25);
        string Pno = line.substr(88, 15);
        string Email = line.substr(103, 25);
        float Amount = stof(line.substr(128, 10));

        if (Accno == searchAcc && Pin == searchPin)
        {

            cout << " --------------- ACCOUNT DETAILS ---------------\n";
            cout << " " << endl;
            cout << "Account Number :: " << Accno << endl;
            cout << "IFSC Code      :: " << Ifsc << endl;
            cout << "Name           :: " << Name << endl;
            cout << "Father Name    :: " << Fname << endl;
            cout << "Phone Number   :: " << Pno << endl;
            cout << "Email ID       :: " << Email << endl;
            cout << "Amount         :: " << Amount << endl;
            cout << "------------------------------------------------\n";

            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "\nINVALID ACCOUNT NUMBER OR PASSWORD....!\n";
    }
    file.close();
}

void Temp::DeleteAccount()
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
        return;
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
}
