
#pragma once
#include "data.h"

// Вхід адміна: перевіряє логін і пароль у dbAdmin, повертає true, якщо все правильно
bool adminLogin(const vector<Admin>& dbAdmin);

// Головна панель адміна: вхід + меню (товари / нові замовлення)
void adminPanel();

// Меню товарів: показ таблиці та дії додати / видалити / змінити кількість
void adminProducts(vector<Products>& db);

// Додає новий товар (назва, ціна, кількість) у кінець масиву db
void addProduct(vector<Products>& db);

// Видаляє товар за id з магазину та з усіх кошиків
void deleteProduct(vector<Products>& db, vector<Cart>& dbCart);

// Змінює кількість товару на складі за id
void changeQuantity(vector<Products>& db);

// Показує таблицю замовлень зі статусом "Створено", повертає їх кількість
int showNewOrders(const vector<Order>& dbOrder, const vector<Products>& db);

// Меню нових замовлень: підтвердити або скасувати замовлення за номером
void adminOrders();

// Показує всі замовлення всіх покупців з їх статусами
void showOrderHistory(const vector<Order>& dbOrder, const vector<Products>& db);
