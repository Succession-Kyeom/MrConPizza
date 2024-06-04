#pragma once
#include <string>
#include <queue>

#include "pizza.h"

//재료 개수 0일 때
#define NONE 0

using namespace std;

//주문 클래스
class Order {
private:
	wchar_t* place;
	Pizza pizza;
	wchar_t* delivery;
	wchar_t* special;
public:
	Order(int orderCase);
	wchar_t* GetPlace();
	wchar_t* GetPizza();
	wchar_t* GetDelivery();
	wchar_t* GetSpecial();
};

class UI {
private:
	int star;
	int day;
	queue<Order*> list;
public:
	UI();
	void GetOrder(); //주문 받는 함수
	void PrintList(HDC hdc);
};