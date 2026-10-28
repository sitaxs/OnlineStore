//Запис у веторах

#include"data.h"

#include <iostream>
#include <vector>

int idUser = -1;

vector<Account> dbAccount = {
	{1, "Лока", 123},
	{2, "sof", 123},
};

vector<Products> db = {
	{1, "Футболка", 500.0 , 10},
	{2, "Кофта", 600.0, 20},
	{3, "Штани", 1000.0 , 30},
	{4, "Куртки", 3000.0 , 0},
};

vector<Cart> dbCart;

vector<Order> dbOrder;

// форматування ціни: 500 -> 500.00
string priceToString(double price) {
	ostringstream out;
	out << fixed << setprecision(2) << price;
	return out.str();
}

// введення числа з перевіркою, поки не введуть число
int inputNumber(const string& text) {
	int number = 0;
	bool isError = false;
	do {
		cout << text;
		cin >> number;
		isError = cin.fail();
		if (isError) {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "Потрібно ввести число" << endl;
		}
	} while (isError);
	return number;
}

//Перевторення масирів в масив рядком
vector<string> productToRow(const Products& p) {
	return{ to_string(p.id), p.name, priceToString(p.price), to_string(p.quantity) };
}

vector<string> accountToRow(const Account& a) {
	return{ to_string(a.id), a.login };
}


vector<string> cartToRow(const Cart& c) {
	return { to_string(c.id), to_string(c.idUser), to_string(c.idProduct), to_string(c.quantity) };
}