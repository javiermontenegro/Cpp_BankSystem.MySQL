#ifndef BANKTRANSACTION_H
#define BANKTRANSACTION_H

/*! \file BankTransaction.h
 *  \brief Definitions for bank transaction manipulation.
 *
 *  The BankTransaction class is a implementation of public and private methods.
 */
 
#include <mysql/mysql.h>
#include <string>
 
class BankAccount;
 
using namespace std;
class BankTransaction
{
public:
   BankTransaction(const string = "localhost",
      const string = "",
   const string = "", const string = "");
   ~BankTransaction();
   void createAccount(BankAccount*);
   void closeAccount(int);
   void deposit(int, double);
   void withdraw(int, double);
   BankAccount* getAccount(int);
   void printAllAccounts();
   void find(int);
   int login(string, string);
   void message(string);
 
private:
   MYSQL* db_conn;
}; //End BankTransaction
 
#endif   // BANKTRANSACTION_H