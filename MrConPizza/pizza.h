#pragma once
#include <iostream>

//���� Ŭ����
class Pizza {
private:
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
	//���� ���̽� & ���� �� �缳��
	void ResetPizza(int* setting);
	friend bool operator == (Pizza ordered, Pizza made);
};