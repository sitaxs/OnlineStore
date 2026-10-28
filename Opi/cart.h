#pragma once
#include "data.h"


void addToCart(vector<Cart>& dbCart, const Products& product, int idUser);
int chooseProductIndex(const vector<Products>& db);
void showProductForChoose(const vector<Products>& db, vector<Cart>& dbCart, int idUser);
void basket(int idUser);
vector<string> cartToRow(const Cart& c, const Products& product);
int findProductIndex(const vector<Products>& db, int idProduct);
int showProductInBasket(const vector<Cart>& dbCart, int idUser, const vector<Products>& db);
int findCartIndex(const vector<Cart>& dbCart, int idUser, int idProduct);
void removeFromCart(vector<Cart>& dbCart, int idUser);
void clearCart(vector<Cart>& dbCart, int idUser);
void makeOrder(vector<Cart>& dbCart, vector<Order>& dbOrder, vector<Products>& db, int idUser);
vector<string> orderToRow(const Order& o, const string& name);
void showOrders(const vector<Order>& dbOrder, int idUser, const vector<Products>& db);