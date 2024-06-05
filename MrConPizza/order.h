#pragma once
#include <string>
#include <queue>

#include "pizza.h"

//��� ���� 0�� ��
#define NONE 0

using namespace std;

//�ֹ� Ŭ����
class Order {
private:
	wchar_t* place;
	wchar_t* menu;
	Pizza pizza;
	wchar_t* delivery;
	wchar_t* special;
public:
	Order(int difficult);
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