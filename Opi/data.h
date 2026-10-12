//Файл із структурами 
#pragma once
#include <iostream>
#include <string>
#include <vector>

#include <limits>//для cin.ignore(

#include <windows.h>
#include <iomanip>  // setw, setfill, left, fixed, setprecision
#include <sstream>  // ostringstream для форматування ціни

using namespace std;

struct  Products {
	int id;
	string  name;
	double price;
	int quantity;
};

struct Account {
	int id = 0;
	string login;
	int password = 0;
};

extern vector<Products> db;
extern vector<Account> dbAccount;
extern int idUser;
extern vector<string> productToRow(const Products& p);
extern vector<string> accountToRow(const Account& a);
// дані снують в інших файлах