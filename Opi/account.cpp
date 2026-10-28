#include "acount.h"
#include "table.h"

using namespace std;


int createAccount(vector<Account>& dbAccount) {
	Account addNewAccont;
	if (dbAccount.empty()) {
		// якщо немає ніяких даних в головному масиві
		addNewAccont.id = 1;
	}
	else {
		addNewAccont.id = dbAccount.back().id + 1;
		//переглядає останній елемент в масиві 
	}

	bool isBusy = false;
	// перевірка аби логін не був зайнятий
	do {
		cout << "Ім'я = ";
		cin >> addNewAccont.login;
		isBusy = false;
		for (const Account& a : dbAccount) {
			if (a.login == addNewAccont.login) {
				isBusy = true;
				cout << "Такий логін вже зайнятий" << endl;
				break;
			}
		}
	} while (isBusy);

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
		return -1;
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
					searchPassword = inputNumber("Введіть пароль: ");
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
		int numberChoose = 0;
		cout << "(1) Вийти з акаунта" << endl;
		cout << "(0) Назад" << endl;

		numberChoose = inputNumber("Оберіть варіант: ");
		if (numberChoose == 1) {
			idUser = -1; // кошик зберігається за id, тому після входу він повернеться
			cout << "Ви вийшли з акаунта" << endl;
			system("pause");
		}
	}
	else {
		cout << "Ви не є зареєстоварні в системі." << endl;
		int numberChoose = 0;
		cout << "(1) Вхід" << endl;
		cout << "(2) Реєстрація" << endl;
		cout << "(3) Назад " << endl;

		numberChoose = inputNumber("Оберіть варіант: ");
		switch (numberChoose)
		{
		case 1:
			idUser = exitAccount(dbAccount);
			system("pause");
			break;

		case 2:
			idUser = createAccount(dbAccount);
			system("pause");
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