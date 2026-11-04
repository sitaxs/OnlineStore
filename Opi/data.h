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

//Товар
struct  Products {
	int id = 0;
	string  name;
	double price = 0;
	int quantity = 0;
};

//Акаунти користувачів
struct Account {
	int id = 0;
	string login;
	int password = 0;
};


//Товари в кошику
struct Cart {
	int id = 0;
	int idUser = 0;
	int idProduct = 0;
	int quantity = 0;
};



//Замовлення 
struct Order {
	int id = 0;
	int numberOrder = 0; 
	int idUser = 0;
	int idProduct = 0;
	int quantity = 0;
	double price = 0;
	int status = 0;
};

// Адміни
struct Admin {
	int id = 0;
	string login;
	int password = 0;
};


//Створення масивів з даними
extern vector<string> statusOrder;
extern vector<Products> db;
extern vector<Account> dbAccount;
extern vector<Cart> dbCart;
extern vector<Order> dbOrder;
extern vector<Admin> dbAdmin; 
extern int idUser;

//Перетворення даних з масиву в string, для подальшого виводу даних
extern vector<string> productToRow(const Products& p);
extern vector<string> accountToRow(const Account& a);
extern vector<string> cartToRow(const Cart& c);
extern string priceToString(double price);
extern int inputNumber(const string& text);
// дані снують в інших файлах