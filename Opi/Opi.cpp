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
	int numberTask = 0;

	do {
		system("cls");
		tasksList();
		numberTask = inputNumber("Обери дію: ");
		switch (numberTask)
		{
		case 1:
			system("cls");
			goodsList(db);
			system("pause");
			break;
		case 2:
			system("cls");
			searchProductsQuantity(db);
			system("pause");
			break;
		case 3:

			system("cls");
			showProductForChoose(db, dbCart, idUser);
			break;
		case 4:
			system("cls");
			basket(idUser);
			break;

		case 5:
			system("cls");
			showOrders(dbOrder, idUser, db);
			system("pause");
			break;
		case 6:
			system("cls");
			idUser = account();
			break;
		case 7:
			cout << "Адмінка ще в розробці" << endl;
			system("pause");
			break;
		case 8:
			cout << "До побачення!" << endl;
			break;

		default:
			cout << "Такої дії немає" << endl;
			system("pause");
			break;
		}
	} while (numberTask != 8);


	return 0;
}