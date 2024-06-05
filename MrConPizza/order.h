#pragma once
#include <string>
#include <queue>

//��� ���� 0�� ��
#define NONE 0

using namespace std;

//���� Ŭ����
class Pizza {
private:
	//���� �̸�
	wchar_t* name;
	//���� ���̽�
	bool dough;
	bool sauce;
	bool cheese;
	bool* base[3];
	//���� ����
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

//�ֹ� Ŭ����
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
	void GetOrder(); //�ֹ� �޴� �Լ�
	void PrintList(HDC hdc);
};