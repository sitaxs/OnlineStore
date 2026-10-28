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
	int id = 0;
	string  name;
	double price = 0;
	int quantity = 0;
};

struct Account {
	int id = 0;
	string login;
	int password = 0;
};

struct Cart {
	int id = 0;
	int idUser = 0;
	int idProduct = 0;
	int quantity = 0;
};

struct Order {
	int id = 0;
	int numberOrder = 0; // номер замовлення (один на всі товари з одного оформлення)
	int idUser = 0;
	int idProduct = 0;
	int quantity = 0;
	double price = 0; // ціна на момент оформлення
};


extern vector<Products> db;
extern vector<Account> dbAccount;
extern vector<Cart> dbCart;
extern vector<Order> dbOrder;
extern int idUser;
extern vector<string> productToRow(const Products& p);
extern vector<string> accountToRow(const Account& a);
extern vector<string> cartToRow(const Cart& c);
extern string priceToString(double price);
extern int inputNumber(const string& text);
// дані снують в інших файлах