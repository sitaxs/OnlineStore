#pragma once
#include "data.h"


void addToCart(vector<Cart>& dbCart, const Products& product, int idUser);
int chooseProductIndex(const vector<Products>& db);
void showProductForChoose(const vector<Products>& db, vector<Cart>& dbCart, int idUser);
void basket(int idUser);
vector<string> cartToRow(const Cart& c, const Products& product);
int findProductIndex(const vector<Products>& db, int idProduct);
void showProductInBasket(const vector<Cart>& dbCart, int idUser, const vector<Products>& db);