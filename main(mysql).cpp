#include <iostream>
#include <unistd.h>
#include <string>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <limits>
#include <string.h>
using namespace std;
char HOST[]="localhost";
char USER[]="root";
char PASS[]="1234456";// ENTER YOUR DB PASSWOD
 MYSQL* conn;
 MYSQL_ROW row;
 MYSQL_RES* res;
  stringstream st;
 int query_stat;
 string money_dep;
 float t_money;

 void update(string dep,string user){

           string query2 = "UPDATE user_data SET balance = " + dep + " WHERE username = \"" + user +"\";";
            const char *g =query2.c_str();

            query_stat = mysql_query(conn,g);

}

 void inline pressEnter(){
 cin.ignore();
 char j;
 cin.get(j);
 }
 void adduser()
{
    char username[30];
    int password;
    int balance;
    int account;
             cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n');

        cout << "\nEnter username:";

        cin.getline(username, 30);
        cout<<"\nAccount Number";
        cin>>account;
        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n');
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
            string user=username;
    string svt = "INSERT INTO user_data(username,balance,pin,account) VALUES('" + user + "','" + to_string(balance)+"','"+to_string(password)+"','" + to_string(account)+"')";
    const char *g =svt.c_str();
    query_stat = mysql_query(conn,g);

    if(query_stat == 0){
    cout<<"\nSuccessfully Registered\n";
     pressEnter();
    }else{
    cout<<"ERROR:"<<mysql_error(conn)<<endl;
    cout<<"Account is Taken, Please Create Another Account Number\n";sleep(3);pressEnter();system("cls");}

}

// View Users
void viewallusers()
{
    query_stat = mysql_query(conn,"SELECT * FROM user_data");

        if(!query_stat){
                system("cls");

            cout<<"User Name\tBalance\tPin\tAccount Number"<<endl;

            res = mysql_store_result(conn);
           while(row = mysql_fetch_row(res)){
                cout<<row[0]<<"\t"<<row[1]<<"\t"<<row[2]<<"\t"<<row[3]<<endl;
           }}

        pressEnter();
}
int deleteuser(char* uname)
{
query_stat = mysql_query(conn,"SELECT * FROM user_data");

        if(!query_stat){

            res = mysql_store_result(conn);
            // Till end of file is reached
           while(row = mysql_fetch_row(res)){

        if (!strcmp(row[0],uname)) {
            char c;
            cout<<"Are You Sure !! Y/N";
            cin>>c;
            if(c=='y' || c=='Y'){

                stringstream sr;

                sr << "DELETE FROM user_data WHERE username=\""<< uname <<"\";";
                string query = sr.str();
                const char *g =query.c_str();
                sr.clear();
            query_stat = mysql_query(conn,g);
            if(query_stat == 0){
                          cout<<endl;
                cout<<"\tPending.....\n\n";sleep(3);
                cout<<"\tDeleting is successful\n";sleep(4);
                system ("cls");
                viewallusers();
                }else
                  cout<<"ERROR:"<<mysql_error(conn);
            }
        }
  }
}
}

int searchspecificuser( char* uname, int pass)
{
    query_stat = mysql_query(conn,"SELECT * FROM user_data");

        if(!query_stat){

            res = mysql_store_result(conn);
           while(row = mysql_fetch_row(res)){

        if (!strcmp(row[0],uname)) {

            if (stoi(row[2]) == pass) {
                return 1;
            }}
        }}
}

 // Function to update user by
// depositing money
void updateuserasdeposit(char* uname){
    query_stat = mysql_query(conn,"SELECT * FROM user_data");

        if(!query_stat){
            res = mysql_store_result(conn);
            // Till end of file is reached
             while(row = mysql_fetch_row(res)){

            if (!strcmp(row[0],uname)) {
            int b;
            cout << "\nEnter amount "
                 << "to deposit:";
            cin >> b;
            money_dep = to_string(stoi(*(row+1))+ b);
             update(money_dep,uname);
            if(query_stat == 0){
              cout<<endl;
            cout<<"Deposit "<<b<<" birr is succeed\n"; }
            else
            cout<<"ERROR:"<<mysql_error(conn);}

             }
            }
}


// Function to update user by
// depositing withdrawing money
void updateuseraswithdraw(char* uname)
{
     query_stat = mysql_query(conn,"SELECT * FROM user_data");

        if(!query_stat){

            res = mysql_store_result(conn);
            // Till end of file is reached
           while(row = mysql_fetch_row(res)){

        if (!strcmp(row[0],uname)) {
            int b,counter=3;
            bn:
            cout << "\nEnter amount "
                 << "to withdraw:";
            cin >> b;
            if (stoi(row[1]) < b) {
                cout
                    << "\nInsufficient "
                    << "balance to withdraw";
                    --counter;
                    cout<<counter<<" Trial left\n";
                    if(counter<0){
                        cout<<"You lost your 3 trial\n";
                        sleep(5);
                        system("cls");
                        break;
                    }
                    goto bn;
            }
            else {
                money_dep = to_string(stoi(*(row+1))- b);
                 update(money_dep,uname);
                if(query_stat == 0){
                          cout<<endl;
                cout<<"\tPending.....\n\n";sleep(3);
                cout<<"\tYou withdraw "<<b<<" birr\n";
                cout<<"\tTake your money\n";
                }else
                  cout<<"ERROR:"<<mysql_error(conn);}}
           }}
}
//check both receiver and sender account
void transfer_check(int num,int a,float mon=0){

    bool flag=false;
    query_stat = mysql_query(conn,"SELECT * FROM user_data");

        if(!query_stat){

            res = mysql_store_result(conn);
           while(row = mysql_fetch_row(res)){
        if(a==4 && num==stoi(row[3]) && mon!=0){ // RECEIVER ACCOUNT

                money_dep = to_string(stoi(*(row+1))+ mon);
                update(money_dep,row[0]);

                    if(query_stat == 0){
                    cout<<endl<<endl;
                    cout<<"\tPending...\n\n";sleep(3);
                    cout<<"\t"<<mon<<" Birr transfer to ";cout<<row[0];
                    cout<<"'s account"<<endl;
                    cout<<"\tTransfer is completed!!\n";
                   pressEnter();
                }else
                  cout<<"ERROR:"<<mysql_error(conn);
                }
            else if(a==5 && num==stoi(row[3])){ //SENDER ACCCONT

            float tMoney;int counter=1;
               if(stoi(row[1])<mon){
                        g:
                         cout<<endl;
                        cout<<"Insufficient Balance\nPlease first check you balance or\n"
                        "Input Again\n"; sleep(2);
                    cout<<"How Much Money Do You Want Transfer:";
                    cin>>tMoney;
                    if(stoi(row[1]) < tMoney && counter<2){counter++;goto g;}
                    else if(stoi(row[1]) < tMoney && counter>=2){cout<<" You lost your 3 trial\n";}
                    else{mon=tMoney; flag=true;}}
            if(stoi(row[1])>= mon || flag){
                    money_dep = to_string(stoi(*(row+1))- mon);
                    update(money_dep,row[0]);
                    t_money=mon;
                if(query_stat == 0){
                          continue;}
                else
                  {cout<<"ERROR:"<<mysql_error(conn);}
            }}}}
}

 //function to transfer money
void transfer(char* uname,int transfer ){
    t_money=0;
     float receiver,tmoney;
    bool flag=false;
    l:
    cout<<"Enter receiver account number:";
    cin>>receiver;

    query_stat = mysql_query(conn,"SELECT * FROM user_data");

        if(!query_stat){

            res = mysql_store_result(conn);
           while(row = mysql_fetch_row(res)){
                if(receiver==stoi(row[3]) && receiver!=transfer){
                    cout<<"How much money do you want transfer:";
                 cin>>tmoney;
                   flag=true;}
 }
    if(flag){transfer_check(transfer,5,tmoney);
            transfer_check(receiver,4,t_money);}
    else{cout<<"Sorry Receiver Account Doesn't Found,\tPlease Input Correctly\n";
        sleep(2);goto l;}
}}

// Search specific user
int searchallusertodisplay(
    char* uname)
{
    query_stat = mysql_query(conn,"SELECT * FROM user_data");

        if(!query_stat){

            res = mysql_store_result(conn);
           while(row = mysql_fetch_row(res)){
                if(!strcmp(row[0],uname)){

             cout << "Username:" << row[0]<<endl;
             cout<<"Account Number:"<<row[3]<<endl;
            cout << "Password:" << row[2]<<endl;
             cout<< " Balance:" << row[1]<<endl;}}}
}


// Function to implement functionality of ATM User
void atmUser()
{


    char uname[30];
    int pass, ch, ch1, ch2, found = 0;

mainmenu:

     system("cls");
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
             system("cls");
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
                adduser();
                goto admin;

            case 2:
                cout << "\nEnter the "
                     << "Username to be "
                        "deleted : ";
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n');
                cin.getline(uname, 30);
                deleteuser(uname);
                goto admin;

            case 3:
                viewallusers();
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
         system("cls");
        cout << "\n Enter details to"
             << " login as User\n";

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n');
        cout << "Enter username:";
        cin.getline(uname, 30);
        cout << "\nEnter password:";

        cin >> pass;
        found = searchspecificuser(
            uname, pass);
            cout<<found<<endl;

        if (found) {
        user:
             system("cls");
            cout << "\nWelcome "
                 << uname;
            cout << "\nWelcome to"
                 << " User Menu";
            cout << "\n1. Deposit\n2."
                 << " Withdraw\n3. View "
                    "Account\n4. "
                 << "Tansfer\n5.Exit\nEnter your choice:";
            cin >> ch2;

            switch (ch2) {
            case 1:
                updateuserasdeposit(uname);pressEnter();
                goto user;
            case 2:
                updateuseraswithdraw(uname);pressEnter();
                goto user;
            case 3:
                searchallusertodisplay(uname);pressEnter(); goto user;
                // sleep(4);

            case 4:
                if(true){query_stat = mysql_query(conn,"SELECT * FROM user_data");

            if(!query_stat){

            res = mysql_store_result(conn);
           while(row = mysql_fetch_row(res)){
                if (!strcmp(row[0],uname)) {

                transfer(uname,stoi(row[3]));}}};
                    pressEnter();
                       goto user;}
            case 5:
                cout << "Thank you";
                sleep(2);
                break;
            }
        }
        else {
                system("cls");
            cout << "\nNo account found"
                 << " with this username "
                    ":(\n\nPlease try again to continue. \n";pressEnter();
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

int main()
{
  conn = mysql_init(0);
  conn = mysql_real_connect(conn,HOST,USER,PASS,"bankData",0,NULL,0);

  if(conn){
     atmUser();
  }
  else cout<<"Connection Not Established";

    system("pause>0");
}
