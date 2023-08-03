you// C++ code to implement an ATM and
// its basic functions
#include <fstream>
#include <iostream>
#include <limits>
#include <string.h>
#include <unistd.h>
using namespace std;

// Class ATM to get user details
class atm {
private:
    char username[30];
    int password;
    int balance;

public:
    char* usernames(void)
    {
        // Return username
        return username;
    }

    int passwords(void)
    {
        // Return the password
        return password;
    }

    // Function to get the data
    void getData(void)
    {
        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n');
        cout << "\nEnter username:";

        cin.getline(username, 30);
        cout << "\nEnter 4-digit "
             << "password:";

        cin >> password;
        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n');
        cout << "\nEnter initial"
             << " balance:";

        cin >> balance;
        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n');
    }

    // Function displaying the data
    void showData(void)
    {
        cout << "Username:" << username
             << ", Password:" << password
             << ", Balance:" << balance
             << endl;
    }

    // Member Functions
    int adduser();
    int viewallusers();
    int deleteuser(char*);
    void updateuserasdeposit(char*);
    void updateuseraswithdraw(char*);
    int searchspecificuser(char*, int);
    int searchallusertodisplay(char*);
};

// Function to implement functionality of ATM User
void atmUser()
{
    atm a;

    char uname[30];
    int pass, ch, ch1, ch2, found = 0;

mainmenu:

    // System("cls");
    cout << "\nWelcome to Vision ATM";
    cout << "\nLogin as :\n1. Admin\n2."
         << " User\n3. "
            "Exit\nChoose one : ";
    cin >> ch;

    switch (ch) {
    case 1:
    rerun:
        // System("cls");
        cout << "\nEnter details to"
             << " login as Admin\n";
        cout << "\nEnter password:";
        cin >> pass;
        if (pass == 1234) {
        admin:
            // System("cls");
            cout << "\nWelcome to"
                 << " Admin Menu";
            cout << "\n1. Add User\n2."
                 << " Delete User\n3. "
                    "View All User\n4. "
                 << "Exit";
            cout << "\nSelect one : ";
            cin >> ch1;
            switch (ch1) {
            case 1:
                a.adduser();
                goto admin;

            case 2:
                cout << "\nEnter the "
                     << "Username to be "
                        "deleted : ";
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n');
                cin.getline(uname, 30);
                a.deleteuser(uname);
                goto admin;

            case 3:
                a.viewallusers();
                // sleep(4);
                goto admin;

            case 4:
                break;
            }
        }
        else {
            cout << "\nDetails are "<< "incorrect ! Please"
                    " try again";
            cin.get();
            goto rerun;
        }
        goto mainmenu;

    case 2:
        // System("cls");
        cout << "\n Enter details to"
             << " login as User\n";

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n');
        cout << "Enter username:";
        cin.getline(uname, 30);
        cout << "\nEnter password:";

        cin >> pass;
        found = a.searchspecificuser(
            uname, pass);

        if (found) {
        user:
            // System("cls");
            cout << "\nWelcome "
                 << uname;
            cout << "\nWelcome to"
                 << " User Menu";
            cout << "\n1. Deposit\n2."
                 << " Withdraw\n3. View "
                    "Account\n4. "
                 << "Exit\nEnter your choice:";
            cin >> ch2;

            switch (ch2) {
            case 1:
                a.updateuserasdeposit(uname);
                goto user;
            case 2:
                a.updateuseraswithdraw(uname);
                goto user;
            case 3:
                a.searchallusertodisplay(uname);
                // sleep(4);
                goto user;
            case 4:
                cout << "Thank you";
                break;
            }
        }
        else {
            cout << "\nNo account found"
                 << " with this username "
                    ":(\n\nPlease try again to continue. \n";
        }
        goto mainmenu;

    case 3:
        cout << "\nThank you for "
             << "banking with "
             << "Vision";
        cin.get();
        break;
    }
}
// Function to add user
int atm::adduser()
{
    atm a;

    ofstream file;

    // Open file in write mode
    file.open("aaa.txt", ios::out | ios::app);
    if (!file) {
        cout << "Error in creating "
             << "file.." << endl;
        return 0;
    }

    // Read from user
    a.getData();

    // Write into file
    file.write((char*)&a, sizeof(a));

    // Close the file
    file.close();

    return 0;
}

// View Users
int atm::viewallusers()
{

    atm a;

    ifstream file1;

    // Open file in read mode
    file1.open("aaa.txt", ios::in);
    if (!file1) {
        cout << "Error in opening file..";
        return 0;
    }
