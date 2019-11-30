#include <cstdlib>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <mysql/mysql.h>

#include "BankTransaction.h"
#include "BankAccount.h"
 
BankTransaction::BankTransaction(const string HOST,
   const string USER, const string PASSWORD,
   const string DATABASE)
{
   db_conn = mysql_init(NULL);
   if(!db_conn)
      message("MySQL initialization failed! ");
   db_conn = mysql_real_connect(db_conn, HOST.c_str(),
      USER.c_str(), PASSWORD.c_str(), DATABASE.c_str(), 0,
         NULL, 0);
   if(!db_conn)
      message("Connection Error! ");
}//End BankTransaction
 
BankTransaction::~BankTransaction()
{
   mysql_close(db_conn);
}//End ~BankTransaction
 
BankAccount* BankTransaction::getAccount(int acno)
{
   BankAccount* b = NULL;
   MYSQL_RES* rset;
   MYSQL_ROW row;
   stringstream sql;
   sql << "SELECT * FROM bank_account WHERE acc_no=" << acno;
 
   if(!mysql_query(db_conn, sql.str().c_str())) {
      b = new BankAccount();
      rset = mysql_use_result(db_conn);
      row = mysql_fetch_row(rset);
      b->setAccountNumber(atoi(row[0]));
      b->setFirstName(row[1]);
      b->setLastName(row[2]);
      b->setBalance(atof(row[3]));
   }//End if
   mysql_free_result(rset);
   return b;
}//End getAccount
 
void BankTransaction::withdraw(int acno, double amount)
{
   BankAccount* b = getAccount(acno);
   if(b != NULL) {
      if(b->getBalance() < amount)
         message("Cannot withdraw. Try lower amount.");
      else {
         b->setBalance(b->getBalance() - amount);
         stringstream sql;
         sql << "UPDATE bank_account SET balance=" << b->getBalance() << " WHERE acc_no=" << acno;
         if(!mysql_query(db_conn, sql.str().c_str())) {
            message("Cash withdraw successful. Balance updated.");
         } else {
            message("Cash deposit unsuccessful! Update failed");
         }//End if
      }//End if
   }//End if
}//End withdraw
 
void BankTransaction::deposit(int acno, double amount)
{
   stringstream sql;
   sql << "UPDATE bank_account SET balance=balance+" << amount << " WHERE acc_no=" << acno;
   if(!mysql_query(db_conn, sql.str().c_str())) {
      message("Cash deposit successful. Balance updated.");
   } else {
      message("Cash deposit unsuccessful! Update failed");
   }//End if
}//End deposit
 
void BankTransaction::createAccount(BankAccount* ba)
{
   stringstream ss;
   ss << "INSERT INTO bank_account(acc_no, fname, lname, balance)" << "values (" << ba->getAccountNumber() << ", '" << ba->getFirstName() + "','" << ba->getLastName() << "'," << ba->getBalance() << ")";
   if(mysql_query(db_conn, ss.str().c_str()))
      message("Failed to create account! ");
   else
      message("Account creation successful.");
}//End createAccount
 
void BankTransaction::closeAccount(int acno)
{
   stringstream ss;
   ss << "DELETE FROM bank_account WHERE acc_no=" << acno;
   if(mysql_query(db_conn, ss.str().c_str()))
      message("Failed to close account! ");
   else
      message("Account close successful.");
}//End closeAccount
 
void BankTransaction::message(string msg)
{
   cout << msg << endl;
}//End message

void BankTransaction::printAllAccounts()
{
   MYSQL_RES* rset;
   MYSQL_ROW rows;
   string sql = "SELECT * FROM bank_account";
   if(mysql_query(db_conn, sql.c_str())) {
      message("Error printing all accounts! ");
      return;
   }//End if
 
   rset = mysql_use_result(db_conn);
 
   cout << left << setw(10) << setfill('-') << left << '+' << setw(21) << setfill('-') << left << '+' << setw(21) << setfill('-') << left << '+' << setw(21) << setfill('-') << '+' << '+' << endl;
   cout << setfill(' ') << '|' << left << setw(9) << "Account" << setfill(' ') << '|' << setw(20) << "First Name" << setfill(' ') << '|' << setw(20) << "Last Name" << setfill(' ') << '|' << right << setw(20) << "Balance" << '|' << endl;
   cout << left << setw(10) << setfill('-') << left << '+' << setw(21) << setfill('-') << left << '+' << setw(21) << setfill('-') << left << '+' << setw(21) << setfill('-') << '+' << '+' << endl;
   
   if(rset) {
      while((rows = mysql_fetch_row(rset))) {
         cout << setfill(' ') << '|' << left << setw(9) << rows[0] << setfill(' ') << '|' << setw(20) << rows[1] << setfill(' ') << '|' << setw(20) << rows[2] << setfill(' ') << '|' << right << setw(20) << rows[3] << '|' << endl;
      }//End while

      cout << left << setw(10) << setfill('-') << left << '+' << setw(21) << setfill('-') << left << '+' << setw(21) << setfill('-') << left << '+' << setw(21) << setfill('-') << '+' << '+' << endl;
   }//End if

   mysql_free_result(rset);
}//End printAllAccounts

void BankTransaction::find(int acno)
{
   MYSQL_RES* rset;
   MYSQL_ROW rows;
   stringstream ss;
   ss << "SELECT * FROM bank_account WHERE acc_no=" << acno;
   if(mysql_query(db_conn, ss.str().c_str())) {
      message("Error printing account! ");
      return;
   }//End if
 
   rset = mysql_use_result(db_conn);
 
   cout << left << setw(10) << setfill('-') << left << '+' << setw(21) << setfill('-') << left << '+' << setw(21) << setfill('-') << left << '+' << setw(21) << setfill('-') << '+' << '+' << endl;
   cout << setfill(' ') << '|' << left << setw(9) << "Account" << setfill(' ') << '|' << setw(20) << "First Name" << setfill(' ') << '|' << setw(20) << "Last Name" << setfill(' ') << '|' << right << setw(20) << "Balance" << '|' << endl;
   cout << left << setw(10) << setfill('-') << left << '+' << setw(21) << setfill('-') << left << '+' << setw(21) << setfill('-') << left << '+' << setw(21) << setfill('-') << '+' << '+' << endl;
   
   if(rset) {
      while((rows = mysql_fetch_row(rset))) {
         cout << setfill(' ') << '|' << left << setw(9) << rows[0] << setfill(' ') << '|' << setw(20) << rows[1] << setfill(' ') << '|' << setw(20) << rows[2] << setfill(' ') << '|' << right << setw(20) << rows[3] << '|' << endl;
      }//End while

      cout << left << setw(10) << setfill('-') << left << '+' << setw(21) << setfill('-') << left << '+' << setw(21) << setfill('-') << left << '+' << setw(21) << setfill('-') << '+' << '+' << endl;
   }//End if

   mysql_free_result(rset);
}//End find

int BankTransaction::login(string username, string password)
{
   BankAccount* b = NULL;
   MYSQL_RES* rset;
   MYSQL_ROW row;
   stringstream sql;
   sql << "SELECT COUNT(*) FROM users WHERE username='" << username << "' AND password='" << password << "'";
   
   int rvalue = 0;
   if(!mysql_query(db_conn, sql.str().c_str())) {
      rset = mysql_use_result(db_conn);
      row = mysql_fetch_row(rset);
      
      rvalue = atoi(row[0]);                
   }//End if

   mysql_free_result(rset);
   return rvalue;
}//End login
