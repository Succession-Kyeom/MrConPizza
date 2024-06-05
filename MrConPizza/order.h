#pragma once
#include <string>
#include <queue>

//재료 개수 0일 때
#define NONE 0

using namespace std;

//피자 클래스
class Pizza {
private:
	//피자 이름
	wchar_t* name;
	//피자 베이스
	bool dough;
	bool sauce;
	bool cheese;
	bool* base[3];
	//피자 토핑
	int pepperoni;
	int tomato;
	int paprika;
	int pepper;
	int onion;
	int olive;
	int shrimp;
	int mushroom;
	int* toppings[8];
public:
	Pizza();
	wchar_t* GetPizza();
	friend bool operator == (Pizza ordered, Pizza made);
};

//주문 클래스
class Order {
private:
	wchar_t* place;
	Pizza pizza;
	wchar_t* delivery;
	wchar_t* special;
public:
	Order();
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