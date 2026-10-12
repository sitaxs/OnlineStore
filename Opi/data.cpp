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


//Перевторення масирів в масив рядком 
vector<string> productToRow(const Products& p) {
	return{ to_string(p.id), p.name, to_string(p.price), to_string(p.quantity) };
}

vector<string> accountToRow(const Account& a) {
	return{ a.login, to_string(a.password) };
}
