## Makefile.am -- Process this file with automake to produce Makefile.in
AM_CPPFLAGS=-I include/
LIBS = -lmysqlclient

bin_PROGRAMS = bank
bank_SOURCES = src/main.cpp src/BankAccount.cpp src/BankTransaction.cpp 

dist_pkgdata_DATA = bootstrap.sh configure.ac bank.sql Doxyfile Makefile.am README.md docs/
