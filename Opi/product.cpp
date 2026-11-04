#include "product.h"
#include "table.h"

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