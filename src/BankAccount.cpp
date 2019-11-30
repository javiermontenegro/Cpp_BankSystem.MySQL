#include "BankAccount.h"
 
#include <string>
#include <cstring>
 
using std::string;
 
BankAccount::BankAccount(int accno, string fname,
   string lname, double bal)
{
   setAccountNumber(accno);
   setFirstName(fname);
   setLastName(lname);
   setBalance(bal);
}//End BankAccount
 
void BankAccount::setAccountNumber(int accno)
{
   accountNumber = accno;
}//End setAccountNumber
 
void BankAccount::setLastName(string lname)
{
   const char* ln = lname.data();
   int len = lname.size();
   len = (len < MAX_SIZE ? len : MAX_SIZE - 1);
   strncpy(lastName, ln, len);
   lastName[len] = '\0';
}//End setLastName
 
void BankAccount::setFirstName(string fname)
{
   const char* fn = fname.data();
   int len = fname.size();
   len = (len < MAX_SIZE ? len : MAX_SIZE - 1);
   strncpy(firstName, fn, len);
   firstName[len] = '\0';
}//End setFirstName
 
void BankAccount::setBalance(double bal)
{
   balance = bal;
}//End setBalance
 
int BankAccount::getAccountNumber() const
{
   return accountNumber;
}//End getAccountNumber
 
string BankAccount::getFirstName() const
{
   return firstName;
}//End getFirstName
 
string BankAccount::getLastName() const
{
   return lastName;
}//End getLastName
 
double BankAccount::getBalance() const
{
   return balance;
}//End getBalance
 
BankAccount::~BankAccount(){} //End BankAccount