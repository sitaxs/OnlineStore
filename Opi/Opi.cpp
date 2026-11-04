// Opi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

 // ostringstream для форматування ціни
#include "table.h"
#include "acount.h"
#include "data.h"
#include "product.h"
#include "cart.h"
#include "admin.h"


using namespace std;


// шапка головної сторінки: назва бренду та привітання
void showHeader() {
	cout << "==========================================" << endl;
	cout << "               URBAN STYLE                " << endl;
	cout << "         Інтернет-магазин одягу           " << endl;
	cout << "==========================================" << endl;

	if (idUser == -1) {
		cout << "Вітаємо! Увійдіть в акаунт, щоб робити покупки" << endl << endl;
	}
	else {
		// шукаємо логін користувача, який увійшов
		for (const Account& a : dbAccount) {
			if (a.id == idUser) {
				cout << "Вітаємо, " << a.login << "! Раді бачити вас знову" << endl << endl;
				break;
			}
		}
	}
}

void tasksList() {
	showHeader();
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
			// АДМІН: вхід у панель адміністратора
			system("cls");
			adminPanel();
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