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
	int id = 0 ;
	string  name;
	double price = 0;
	int quantity  = 0;
};

struct Account {
	int id = 0;
	string login;
	int password = 0;
};

struct Cart {
	int id = 0;
	int idUser =0 ;
	int idProduct =0;
	int quantity = 0;
};


extern vector<Products> db;
extern vector<Account> dbAccount;
extern vector<Cart> dbCart;
extern int idUser;
extern vector<string> productToRow(const Products& p);
extern vector<string> accountToRow(const Account& a);
extern vector<string> cartToRow(const Cart& c);
// дані снують в інших файлах