// Opi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

#include <limits>//для cin.ignore(

#include <windows.h>
#include <iomanip>  // setw, setfill, left, fixed, setprecision
#include <sstream>  // ostringstream для форматування ціни

using namespace std;

struct  Products{
	int id;
	string  name;
	double price;
	int quantity;
};

struct Account {
	int id =0;
	string login;
	int password= 0;
};


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

int idUser =-1;

void printLine (const vector<int>& widths) {
	int total = 1;
	for (int w : widths) {
		total += w +2 ;
	}
	cout << setfill('-') << setw(total) << "" << setfill(' ') << '\n';
}
//це розмір рядка та значення які будут записуватися в кожному рядку 
void printRow(const vector<string>& value , const vector<int>& widths) {
	cout << left;
	for (int i = 0; i < value.size(); i++) {
		cout << "| " << setw(widths[i]) << value[i];
	}
	cout << endl;
}

// самий вівід таблиці 
void printTable(const vector<string>& headers, 
	const vector<int>& widths,
	const vector<vector<string>>& rows) {
	printLine(widths);
	printRow(headers, widths);   // заголовок — такий самий рядок
	printLine(widths);
	for (const vector<string>& row : rows) {
		printRow(row, widths);
	}
	printLine(widths);
}

vector<string> productToRow(const Products& p) {
	return{ to_string(p.id), p.name, to_string(p.price), to_string(p.quantity) };
}

vector<string> accountToRow(const Account& a) {
	return{ a.login, to_string(a.password) };
}


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

int createAccount(vector<Account>& dbAccount) {
	Account addNewAccont;
	if (dbAccount.empty()){
		// якщо немає ніяких даних в головному масиві
		addNewAccont.id=1;
	}
	else {
		addNewAccont.id = dbAccount.back().id + 1;
		//переглядає останній елемент в масиві 
	}

	cout << "Ім'я = ";
	cin >> addNewAccont.login;
	
	bool isError = false;
	// первірка аби пароль був цифри 
	do {
		cout << "Пароль = ";
		cin >> addNewAccont.password;
		isError = cin.fail();
		if (isError) {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "Пароль має бути числом" << endl;
		}
	} while (isError);
	
	dbAccount.push_back(addNewAccont);
	cout << "Акаунт успішно створено" << endl;
	return  addNewAccont.id;
}

int exitAccount(const vector<Account>& dbAccount) {
	int currentUserId = -1;
	if (dbAccount.empty()) {
		cout << "В базі даних немає акаунтів!!" << endl;
		return -1 ;
	}
	string searchLogin;
	bool rightLogin;
	do {
		cout << " Введи логін для входу в акаунт: ";
		cin >> searchLogin;
		rightLogin = true; // 1. на початку вважаємо, що логін не знайдено

		for (const Account& a : dbAccount) {
			if (searchLogin == a.login) {
				int searchPassword;
				bool rightPassword;
				rightLogin = false;
				do {
					cout << "Введіть пароль: ";
					cin >> searchPassword;
					if (searchPassword == a.password) {
						currentUserId = a.id;
						cout << "Все успішно, ви ввійшли в акаунт!!" << endl;
						rightPassword = false;
					}
					else {
						rightPassword = true;
						cout << "Помилка, неправильний пароль" << endl;
					}
				} while (rightPassword);
				break; // 2. акаунт знайдено, далі не шукаємо
			}
		}

		// 3. else винесено з for, перевірка після пошуку
		if (rightLogin) {
			cout << "Помилка, такого логіна немає!" << endl;
		}
	} while (rightLogin);

	return currentUserId;
}

void showAccount(const int idUser) {
	vector<vector<string>> rows;
	for (const Account& a : dbAccount) {
		if (a.id == idUser) {
			rows.push_back(accountToRow(a));
		}
		
	}
	printTable({ "ID", "Login" }, { 5,20 }, rows);
}

int  account() {
	if (idUser != -1) {
		cout << "Ви війшли в акаунт!!" << endl;
		showAccount(idUser);
		system("pause");
	}
	else {
		cout << "Ви не є зареєстоварні в системі." << endl;
		int numberChoose = 0;
		cout << "(1) Вхід" << endl;
		cout << "(2) Реєстрація" << endl;
		cout << "(3) Назад " << endl;

		cout << "Оберіть варіант: ";
		cin >> numberChoose;
		switch (numberChoose)
		{
		case 1:
			idUser = exitAccount(dbAccount);
			break;

		case 2:
			idUser = createAccount(dbAccount);
			break;
		case 3:
			system("cls");
			return -1;
			break;
		default:
			break;
		}
	}

	return idUser;
}

void tasksList() {
	cout << "(1) Виведи весь товар" << endl;
	cout << "(2) Товар, що в наявності" << endl;
	cout << "(3) Купити товар" << endl;
	cout << "(4) Кошик" << endl;
	cout << "(5) Акаунт (вхід / реєстрація)" << endl;
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
			account();
			
			break;
		case 6: 
			
			break;

		
		default:
			break;
		}
	} while (numberTask > 0);
	

    return 0;
}