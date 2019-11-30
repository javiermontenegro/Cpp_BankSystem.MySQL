#include <iostream>
#include <sstream>
#include <iomanip>
 
#include <string>
#include <termios.h>
#include <unistd.h>

#include <cstdlib>
#include <mysql/mysql.h>
 
#include "BankAccount.h"
#include "BankTransaction.h"
 
using namespace std;
 
enum Options { PRINT = 1, NEW, WITHDRAW, DEPOSIT,
               CLOSE, FIND, END };
 
void clear() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    cout << "\x1B[2J\x1B[H";
}//End clear

int mainMenu()
{
   cout << "System Options: \n"
        << "[1] Print All Account \n" 
        << "[2] Open New Account \n" 
        << "[3] Withdraw \n" 
        << "[4] Deposit \n"  
        << "[5] Close Account \n" 
        << "[6] Find Account \n" 
        << "[7] End Transaction \n" << endl;
   int ch;
   cin >> ch;
   return ch;
}//End mainMenu
 
int main(int argc, char** argv)
{
   BankTransaction* bt =
      new BankTransaction("localhost", "root",
                          "mysql", "bank");
 
   int choice;
   int acno;
   string fname, lname;
   double bal;
   string username, password;
 
   clear();

   cout << "\nEnter your username: " << endl;
   cin >> username;

   termios oldt;
   tcgetattr(STDIN_FILENO, &oldt);
   termios newt = oldt;
   newt.c_lflag &= ~ECHO;
   tcsetattr(STDIN_FILENO, TCSANOW, &newt);

   cout << "\nEnter password: " << endl;
   cin >> password; 

   tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    if( bt->login(username, password) == 0 ) {
       cout << "Fail to login." << endl;
       return 0;
    }//End if  

   clear(); 
   while(1) {
      choice = mainMenu();
      if(choice == END)
         break;
      switch(choice) {
      case PRINT:
         bt->printAllAccounts();
         break;
      case NEW:
         cout << "\nEnter account no: " << endl;
         cin >> acno;
         cout << "\nEnter first name: " << endl;
         cin >> fname;
         cout << "\nEnter last name: " << endl;         
         cin >> lname;
         cout << "\nEnter balance: " << endl;         
         cin >> bal;

         if(acno < 1) {
            cout << "Invalid account number." << endl;
            break;
         }//End if
         bt->createAccount(new BankAccount(acno, fname, lname,
                                           bal));
         break;
      case WITHDRAW:
         cout << "\nEnter account no: " << endl;
         cin >> acno;
         cout << "\nEnter amount to withdraw: " << endl;
         cin >> bal;

         if(bal < 0) {
            cout << "Invalid amount." << endl;
            break;
         }
         bt->withdraw(acno, bal);
         break;
      case DEPOSIT:
         cout << "\nEnter account no: " << endl;
         cin >> acno;
         cout << "\nEnter amount to deposit: " << endl;
         cin >> bal;

         if(bal < 0) {      
            cout << "Invalid amount." << endl;
            break;
         }
         bt->deposit(acno, bal);
         break;
     case CLOSE:
         cout << "\nEnter account no to close account: " << endl;
         cin >> acno;

         bt->closeAccount(acno);
         break;
      case FIND:
         cout << "\nEnter account no: " << endl;
         cin >> acno;

         if(acno < 0) {
            cout << "Invalid account no." << endl;
            break;
         }
         bt->find(acno);
         break;         
      default:
         cerr << "Invalid choice!" << endl;
         break;
      }//End switch
   }//End while
   return 0;
}//End main