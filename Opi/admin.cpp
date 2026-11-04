// АДМІН: усі дії адміністратора
#include "admin.h"
#include "table.h"
#include "product.h" // goodsList - таблиця товарів
#include "cart.h"    // findProductIndex, orderToRow, confirmOrder, cancelOrder

// АДМІН: вхід в адмін-панель
bool adminLogin(const vector<Admin>& dbAdmin) {
	string login;
	cout << "Логін адміна: ";
	cin >> login;
	int password = inputNumber("Пароль адміна: ");

	// шукаємо адміна з таким логіном і паролем
	for (const Admin& a : dbAdmin) {
		if (a.login == login && a.password == password) {
			cout << "Вітаємо, " << a.login << "! Ви увійшли як адміністратор" << endl;
			return true;
		}
	}
	cout << "Неправильний логін або пароль адміна" << endl;
	return false;
}

// АДМІН: головне меню адміна
void adminPanel() {
	if (!adminLogin(dbAdmin)) {
		system("pause");
		return; // не пускаємо в панель без правильного пароля
	}
	system("pause");

	int numberChoose = 0;
	do {
		system("cls");
		cout << "===== ПАНЕЛЬ АДМІНІСТРАТОРА =====" << endl;
		cout << "(1) Товари" << endl;
		cout << "(2) Нові замовлення" << endl << endl;
		cout << "(3) Історія замовлень" << endl << endl;
		cout << "(0) Вийти з адмінки" << endl << endl;

		numberChoose = inputNumber("Оберіть варіант: ");
		switch (numberChoose)
		{
		case 1:
			adminProducts(db);
			break;
		case 2:
			adminOrders();
			break;
		case 3:
			system("cls");
			cout << "Історія замовлень" << endl;
			showOrderHistory(dbOrder, db);
			system("pause");
			break;
		case 0:
			break;
		default:
			cout << "Такої дії немає" << endl;
			system("pause");
			break;
		}
	} while (numberChoose != 0);
}

// АДМІН: меню роботи з товарами
void adminProducts(vector<Products>& db) {
	int numberChoose = 0;
	do {
		system("cls");
		cout << "Товари магазину" << endl;
		goodsList(db);
		cout << "(1) Додати товар" << endl;
		cout << "(2) Видалити товар" << endl;
		cout << "(3) Змінити кількість" << endl << endl;
		cout << "(0) Назад" << endl << endl;

		numberChoose = inputNumber("Оберіть варіант: ");
		switch (numberChoose)
		{
		case 1:
			addProduct(db);
			break;
		case 2:
			deleteProduct(db, dbCart);
			break;
		case 3:
			changeQuantity(db);
			break;
		case 0:
			break;
		default:
			cout << "Такої дії немає" << endl;
			break;
		}
		if (numberChoose != 0) {
			system("pause");
		}
	} while (numberChoose != 0);
}

// АДМІН: додавання товару
void addProduct(vector<Products>& db) {
	Products newProduct;
	if (db.empty()) {
		newProduct.id = 1;
	}
	else {
		newProduct.id = db.back().id + 1; // id = останній id + 1
	}

	cout << "Назва товару: ";
	cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // прибираємо Enter після попереднього вводу
	getline(cin, newProduct.name); // getline, щоб назва могла бути з пробілами

	// перевірка, щоб ціна була числом більше 0
	bool isError = false;
	do {
		cout << "Ціна: ";
		cin >> newProduct.price;
		isError = cin.fail() || newProduct.price <= 0;
		if (isError) {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "Ціна має бути числом більше 0" << endl;
		}
	} while (isError);

	// кількість не може бути від'ємною
	do {
		newProduct.quantity = inputNumber("Кількість: ");
		if (newProduct.quantity < 0) {
			cout << "Кількість не може бути менше 0" << endl;
		}
	} while (newProduct.quantity < 0);

	db.push_back(newProduct);
	cout << "Товар \"" << newProduct.name << "\" додано!" << endl;
}

// АДМІН: видалення товару
void deleteProduct(vector<Products>& db, vector<Cart>& dbCart) {
	int idProduct = inputNumber("Введи id товару для видалення (0 - назад): ");
	if (idProduct == 0) {
		return;
	}
	int index = findProductIndex(db, idProduct);
	if (index == -1) {
		cout << "Такого товару немає" << endl;
		return;
	}

	// прибираємо цей товар з кошиків усіх користувачів (йдемо з кінця через erase)
	for (int i = dbCart.size() - 1; i >= 0; i--) {
		if (dbCart[i].idProduct == idProduct) {
			dbCart.erase(dbCart.begin() + i);
		}
	}

	cout << "Товар \"" << db[index].name << "\" видалено" << endl;
	db.erase(db.begin() + index);
}

// АДМІН: зміна кількості товару
void changeQuantity(vector<Products>& db) {
	int idProduct = inputNumber("Введи id товару (0 - назад): ");
	if (idProduct == 0) {
		return;
	}
	int index = findProductIndex(db, idProduct);
	if (index == -1) {
		cout << "Такого товару немає" << endl;
		return;
	}

	int newQuantity = 0;
	do {
		newQuantity = inputNumber("Нова кількість: ");
		if (newQuantity < 0) {
			cout << "Кількість не може бути менше 0" << endl;
		}
	} while (newQuantity < 0);

	cout << db[index].name << ": було " << db[index].quantity << " -> стало " << newQuantity << endl;
	db[index].quantity = newQuantity;
}

// АДМІН: таблиця нових замовлень (статус "Створено")
int showNewOrders(const vector<Order>& dbOrder, const vector<Products>& db) {
	vector<vector<string>> rows;
	for (const Order& o : dbOrder) {
		if (o.status != 0) {
			continue; // показуємо тільки нові ("Створено")
		}
		string name = "Видалений товар";
		int index = findProductIndex(db, o.idProduct);
		if (index != -1) {
			name = db[index].name;
		}
		rows.push_back(orderToRow(o, name));
	}

	if (rows.empty()) {
		cout << "Нових замовлень немає" << endl;
		return 0;
	}

	printTable({ "№", "Назва", "Ціна", "К-сть", "Сума", "Статус" }, { 3, 13, 12, 8, 12, 10 }, rows);
	return rows.size();
}

// АДМІН: меню нових замовлень
void adminOrders() {
	int numberChoose = 0;
	do {
		system("cls");
		cout << "Нові замовлення" << endl;
		int count = showNewOrders(dbOrder, db);
		if (count == 0) {
			system("pause");
			return;
		}

		cout << "(1) Підтвердити замовлення" << endl;
		cout << "(2) Скасувати (видалити) замовлення" << endl << endl;
		cout << "(0) Назад" << endl << endl;

		numberChoose = inputNumber("Оберіть варіант: ");
		if (numberChoose == 1 || numberChoose == 2) {
			int numberOrder = inputNumber("Введи № замовлення: ");
			if (numberChoose == 1) {
				confirmOrder(dbOrder, numberOrder);   // статус -> "Прийнято"
			}
			else {
				cancelOrder(dbOrder, db, numberOrder); // статус -> "Скасовано" + товар назад
			}
			system("pause");
		}
		else if (numberChoose != 0) {
			cout << "Такої дії немає" << endl;
			system("pause");
		}
	} while (numberChoose != 0);
}


// АДМІН: історія всіх замовлень (усі покупці, усі статуси)
void showOrderHistory(const vector<Order>& dbOrder, const vector<Products>& db) {
	vector<vector<string>> rows;
	double total = 0;
	for (const Order& o : dbOrder) {
		string name = "Видалений товар";
		int index = findProductIndex(db, o.idProduct);
		if (index != -1) {
			name = db[index].name;
		}

		// шукаємо логін покупця за idUser
		string login = "Невідомий";
		for (const Account& a : dbAccount) {
			if (a.id == o.idUser) {
				login = a.login;
				break;
			}
		}

		vector<string> row = orderToRow(o, name);
		row.insert(row.begin() + 1, login); // стовпець "Покупець" після номера
		rows.push_back(row);

		if (o.status == 1) { // рахуємо тільки прийняті
			total += o.price * o.quantity;
		}
	}

	if (rows.empty()) {
		cout << "Замовлень ще немає" << endl;
		return;
	}

	printTable({ "№", "Покупець", "Назва", "Ціна", "К-сть", "Сума", "Статус" },
		{ 3, 10, 13, 12, 8, 12, 10 }, rows);
	cout << "Сума прийнятих замовлень: " << priceToString(total) << " грн" << endl;
}