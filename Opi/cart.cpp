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
void showProductInBasket(const vector<Cart>& dbCart, int idUser, const vector<Products>& db);



void showProductForChoose( const vector<Products>& db, vector<Cart>& dbCart, int idUser) {
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

		cin >> continus;
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
			return -1 ;
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

void addToCart (vector<Cart>& dbCart, const Products& product, int idUser) {
	if (product.quantity == 0) {
		cout << "Товару немає в наявності" << endl;
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
		else if (chooseQuantity > product.quantity) {
			cout << "Товару не вистачає такою кількістю" << endl;
		}
		else {
			rightQuantity = false;
		}
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
	cout << "Ваший кошик" << endl;
	showProductInBasket(dbCart, idUser, db);
}

int findProductIndex(const vector<Products>& db, int idProduct) {
	for (int i = 0; i < db.size(); i++) {
		if (db[i].id == idProduct) {
			return i;
		}
	}
	return -1 ;
}

vector<string> cartToRow(const Cart& c, const Products& product) {
	return {
		to_string(c.id),
		product.name,
		to_string(product.price),
		to_string(c.quantity),
	};
}

void showProductInBasket(const vector<Cart>& dbCart, int idUser, const vector<Products>& db) {
	//if (dbAccount.id != idUser) {}
	vector<vector<string>> rows;

	for (const Cart& c : dbCart) {
		if (c.idUser != idUser) {
			cout << "У вас пустий кошик" << endl;
			continue;
		}


		int index = findProductIndex(db, c.idProduct);
		if (index == -1) {
			continue;
		}
		rows.push_back(cartToRow(c, db[index]));
	}

	printTable({ "ID", "Назва", "Ціна", "К-сть" }, { 3, 13, 12, 8 }, rows);

}



