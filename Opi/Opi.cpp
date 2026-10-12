// Opi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

 // ostringstream для форматування ціни
#include "table.h"
#include "acount.h"
#include "data.h"


using namespace std;


void goodsList(const vector<Products>& db) {
	vector<vector<string>> rows;//створємо локальний двовирірний масив для побудови таблиці
	for (const Products& p : db) {
		rows.push_back(productToRow(p));
	}
	printTable({ "ID", "Назва", "Ціна", "В наявності" }, { 3, 13, 12, 11 }, rows);
}

void searchProductsQuantity(const vector<Products>& db) {
	vector<vector<string>> rows;
	for (const Products& p : db) {
		if (p.quantity > 0) {
			rows.push_back(productToRow(p));
		}
	}
	printTable({ "ID", "Назва", "Ціна", "В наявності" }, { 3, 13, 12, 11 }, rows);

}


void tasksList() {
	cout << "(1) Виведи весь товар" << endl;
	cout << "(2) Товар, що в наявності" << endl;
	cout << "(3) Купити товар" << endl;
	cout << "(4) Кошик" << endl;
	cout << "(5) Мої замовлення" << endl;
	cout << "(6) Акаунт (вхід / реєстрація)" << endl;
	cout << "(7) Адмін" << endl;
	cout << "(8) Вихід" << endl;

}


int main()
{
	
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int numberTask = 0;
	
	do {
		tasksList();
		cout << "Обери дію: ";
		cin >> numberTask;
		switch (numberTask)
		{
		case 1:
			goodsList(db);
			//system("pause");
			break;
		case 2:
			searchProductsQuantity(db);
			break;
		case 3:
			account();
			system("pause");
			break;
		case 4:
			break;

		case 5:
		
			
			break;
		case 6: 
			account();
			break;

		
		default:
			break;
		}
	} while (numberTask > 0);
	

    return 0;
}