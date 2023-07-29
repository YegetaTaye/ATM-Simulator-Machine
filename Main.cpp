// C++ code to implement an ATM and
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
