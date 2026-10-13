// Opi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

 // ostringstream для форматування ціни
#include "table.h"
#include "acount.h"
#include "data.h"
#include "product.h"
#include "cart.h"


using namespace std;


void tasksList() {
	cout << "(1) Виведи весь товар" << endl;
	cout << "(2) Товар, що в наявності" << endl;
	cout << "(3) Добавити товар до кошику" << endl;
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
	int idUser = -1;
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

			system("cls");
			showProductForChoose(db, dbCart, idUser);
			system("cls");
			break;
		case 4:
			system("cls");
			basket(idUser);
			system("pause");
			break;

		case 5:
		
			
			break;
		case 6: 
			idUser = account();
			break;

		
		default:
			break;
		}
	} while (numberTask > 0);
	

    return 0;
}