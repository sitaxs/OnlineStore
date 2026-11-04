//Запис у веторах

#include"data.h"

#include <iostream>
#include <vector>

int idUser = -1;

//Мінібаза даних користувачів
vector<Account> dbAccount = {
	{1, "Лока", 123},
	{2, "sof", 123},
};


//Товари
vector<Products> db = {
	{1, "Футболка", 500.0 , 10},
	{2, "Кофта", 600.0, 20},
	{3, "Штани", 1000.0 , 30},
	{4, "Куртки", 3000.0 , 0},
};


// Статуси замовлення: номер у масиві = статус
vector<string> statusOrder = {
	"Створено",  
	"Прийнято",  
	"Скасовано", 
};

//Створені замовлення 
vector<Order> dbOrder = {
	{1, 1, 1, 1, 2, 500.0,  1}, 
	{2, 1, 1, 3, 1, 1000.0, 1},
	{3, 2, 2, 2, 1, 600.0,  2}, 
	{4, 3, 2, 1, 1, 500.0,  0}, 
	{5, 3, 2, 3, 2, 1000.0, 0}, 
};

//База даних товарів в кошику
vector<Cart> dbCart;


// Адміністратор
vector<Admin> dbAdmin = {
	{1, "admin", 1111},
};

// форматування ціни:
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

//Перевторення  масив в рядком для продукутів
vector<string> productToRow(const Products& p) {
	return{ to_string(p.id), p.name, priceToString(p.price), to_string(p.quantity) };
}

//Перевторення  масив в рядком для акаунтів
vector<string> accountToRow(const Account& a) {
	return{ to_string(a.id), a.login };
}

//Перевторення  масив в рядком для товарів 
vector<string> cartToRow(const Cart& c) {
	return { to_string(c.id), to_string(c.idUser), to_string(c.idProduct), to_string(c.quantity) };
}