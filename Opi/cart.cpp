#include "cart.h"
#include "data.h"
#include "product.h"
#include "table.h"

void addToCart(vector<Cart>& dbCart, const Products& product, int idUser);
int chooseProductIndex(const vector<Products>& db);
void showProductForChoose(const vector<Products>& db, vector<Cart>& dbCart, int idUser);
void basket(int idUser);
vector<string> cartToRow(const Cart& c, const Products& product);
int findProductIndex(const vector<Products>& db, int idProduct);
int showProductInBasket(const vector<Cart>& dbCart, int idUser, const vector<Products>& db);



void showProductForChoose(const vector<Products>& db, vector<Cart>& dbCart, int idUser) {
	cout << "(0) Вихід" << endl << endl;

	if (idUser == -1) {
		cout << "Ви не війшли в акаунт!!" << endl;
		system("pause");
		return;
	}

	goodsList(db);
	int continus = 0;
	do {
		int index = chooseProductIndex(db);//відбувається присвоння та одночасно викли функції
		if (index == -1) {
			return;// якщо функція поертає -1 и виходимо із програми
		}
		addToCart(dbCart, db[index], idUser);
		cout << "(1) Добавиати ще елемент" << endl;
		cout << "(2) Перейти до кошика" << endl << endl;

		cout << "(0) Вихід" << endl << endl;

		continus = inputNumber("Оберіть варіант: ");
		if (continus == 2) {
			system("cls");
			basket(idUser);

		}

	} while (continus == 1);

}

int chooseProductIndex(const vector<Products>& db) {
	int idProduct = -1;
	int foundIndex;
	bool isError;
	do {
		cout << "Введи id товару:";
		cin >> idProduct;
		if (cin.fail()) {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "Не вірний id" << endl;
			isError = true;
			continue;
		}

		if (idProduct == 0) {
			return -1;
		}
		foundIndex = -1;
		for (int i = 0; i < db.size(); i++) {
			if (db[i].id == idProduct) {
				foundIndex = i;
				break;//це для того аби закінчити цикл 
			}
		}

		if (foundIndex == -1) {
			cout << "Такого товару немає" << endl;
			isError = true;
		}
		else {
			isError = false;
		}
	} while (isError);


	return foundIndex;
}

void addToCart(vector<Cart>& dbCart, const Products& product, int idUser) {
	if (product.quantity == 0) {
		cout << "Товару немає в наявності" << endl;
		return;
	}

	// скільки цього товару вже лежить у кошику
	int cartIndex = findCartIndex(dbCart, idUser, product.id);
	int available = product.quantity;
	if (cartIndex != -1) {
		available = product.quantity - dbCart[cartIndex].quantity;
	}
	if (available <= 0) {
		cout << "Весь товар вже у вашому кошику" << endl;
		return;
	}

	Cart newCart;
	int chooseQuantity = 0;
	bool rightQuantity = true;

	while (rightQuantity) {
		cout << "Введи кількість товарів ";
		cin >> chooseQuantity;
		if (cin.fail()) {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "Кількість має бути числом" << endl;
		}
		else if (chooseQuantity <= 0) {
			cout << "Кількість має бути більше 0" << endl;
		}
		else if (chooseQuantity > available) {
			cout << "Товару не вистачає такою кількістю (доступно: " << available << ")" << endl;
		}
		else {
			rightQuantity = false;
		}
	}

	// якщо товар вже є в кошику, то просто збільшуємо кількість
	if (cartIndex != -1) {
		dbCart[cartIndex].quantity += chooseQuantity;
		cout << "Товар добавлено!" << endl;
		return;
	}

	if (dbCart.empty()) {
		newCart.id = 1;
	}
	else {
		newCart.id = dbCart.back().id + 1;
	}
	newCart.idUser = idUser;
	newCart.idProduct = product.id;
	newCart.quantity = chooseQuantity;
	dbCart.push_back(newCart);
	cout << "Товар добавлено!" << endl;
}

void basket(int idUser) {
	if (idUser == -1) {
		cout << "Ви не війшли в акаунт!!" << endl;
		system("pause");
		return;
	}
	int numberChoose = 0;
	do {
		system("cls");
		cout << "Ваший кошик" << endl;
		int count = showProductInBasket(dbCart, idUser, db);
		if (count == 0) {
			system("pause");
			return;
		}

		cout << "(1) Видалити товар" << endl;
		cout << "(2) Очистити кошик" << endl;
		cout << "(3) Оформити замовлення" << endl << endl;
		cout << "(0) Назад" << endl << endl;

		numberChoose = inputNumber("Оберіть варіант: ");
		switch (numberChoose)
		{
		case 1:
			removeFromCart(dbCart, idUser);
			break;
		case 2:
			clearCart(dbCart, idUser);
			cout << "Кошик очищено" << endl;
			system("pause");
			return;
		case 3:
			makeOrder(dbCart, dbOrder, db, idUser);
			system("pause");
			return;
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

int findProductIndex(const vector<Products>& db, int idProduct) {
	for (int i = 0; i < db.size(); i++) {
		if (db[i].id == idProduct) {
			return i;
		}
	}
	return -1;
}

vector<string> cartToRow(const Cart& c, const Products& product) {
	return {
		to_string(c.id),
		product.name,
		priceToString(product.price),
		to_string(c.quantity),
		priceToString(product.price * c.quantity),
	};
}

int showProductInBasket(const vector<Cart>& dbCart, int idUser, const vector<Products>& db) {
	vector<vector<string>> rows;
	double total = 0;

	for (const Cart& c : dbCart) {
		if (c.idUser != idUser) {
			continue;
		}


		int index = findProductIndex(db, c.idProduct);
		if (index == -1) {
			continue;
		}
		rows.push_back(cartToRow(c, db[index]));
		total += db[index].price * c.quantity;
	}

	// перевірка після циклу, аби повідомлення було один раз
	if (rows.empty()) {
		cout << "У вас пустий кошик" << endl;
		return 0;
	}

	printTable({ "ID", "Назва", "Ціна", "К-сть", "Сума" }, { 3, 13, 12, 8, 12 }, rows);
	cout << "Разом: " << priceToString(total) << " грн" << endl << endl;
	return rows.size();
}

// шукає товар у кошику конкретного користувача
int findCartIndex(const vector<Cart>& dbCart, int idUser, int idProduct) {
	for (int i = 0; i < dbCart.size(); i++) {
		if (dbCart[i].idUser == idUser && dbCart[i].idProduct == idProduct) {
			return i;
		}
	}
	return -1;
}

void removeFromCart(vector<Cart>& dbCart, int idUser) {
	int idCart = inputNumber("Введи id з кошика (0 - назад): ");
	if (idCart == 0) {
		return;
	}
	for (int i = 0; i < dbCart.size(); i++) {
		if (dbCart[i].id == idCart && dbCart[i].idUser == idUser) {
			dbCart.erase(dbCart.begin() + i);
			cout << "Товар видалено з кошика" << endl;
			return;
		}
	}
	cout << "Такого товару в кошику немає" << endl;
}

void clearCart(vector<Cart>& dbCart, int idUser) {
	// йдемо з кінця, аби erase не зсував ще не перевірені елементи
	for (int i = dbCart.size() - 1; i >= 0; i--) {
		if (dbCart[i].idUser == idUser) {
			dbCart.erase(dbCart.begin() + i);
		}
	}
}

void makeOrder(vector<Cart>& dbCart, vector<Order>& dbOrder, vector<Products>& db, int idUser) {
	int numberOrder = 1;
	if (!dbOrder.empty()) {
		numberOrder = dbOrder.back().numberOrder + 1;
	}

	double total = 0;
	for (const Cart& c : dbCart) {
		if (c.idUser != idUser) {
			continue;
		}
		int index = findProductIndex(db, c.idProduct);
		if (index == -1) {
			continue;
		}

		Order newOrder;
		if (dbOrder.empty()) {
			newOrder.id = 1;
		}
		else {
			newOrder.id = dbOrder.back().id + 1;
		}
		newOrder.numberOrder = numberOrder;
		newOrder.idUser = idUser;
		newOrder.idProduct = c.idProduct;
		newOrder.quantity = c.quantity;
		newOrder.price = db[index].price;
		dbOrder.push_back(newOrder);

		db[index].quantity -= c.quantity; // списуємо товар зі складу
		total += newOrder.price * newOrder.quantity;
	}

	clearCart(dbCart, idUser);
	cout << "Замовлення №" << numberOrder << " оформлено! Сума: " << priceToString(total) << " грн" << endl;
}

vector<string> orderToRow(const Order& o, const string& name) {
	return {
		to_string(o.numberOrder),
		name,
		priceToString(o.price),
		to_string(o.quantity),
		priceToString(o.price * o.quantity),
	};
}

void showOrders(const vector<Order>& dbOrder, int idUser, const vector<Products>& db) {
	if (idUser == -1) {
		cout << "Ви не війшли в акаунт!!" << endl;
		return;
	}
	cout << "Мої замовлення" << endl;

	vector<vector<string>> rows;
	double total = 0;
	for (const Order& o : dbOrder) {
		if (o.idUser != idUser) {
			continue;
		}
		string name = "Видалений товар";
		int index = findProductIndex(db, o.idProduct);
		if (index != -1) {
			name = db[index].name;
		}
		rows.push_back(orderToRow(o, name));
		total += o.price * o.quantity;
	}

	if (rows.empty()) {
		cout << "У вас ще немає замовлень" << endl;
		return;
	}

	printTable({ "№", "Назва", "Ціна", "К-сть", "Сума" }, { 3, 13, 12, 8, 12 }, rows);
	cout << "Всього витрачено: " << priceToString(total) << " грн" << endl;
}