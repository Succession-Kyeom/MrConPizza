#pragma once
#include <iostream>

//���� Ŭ����
class Pizza {
private:
	//���� ���̽�
	bool base[3];
	//���� ����
	int toppings[8];
public:
	Pizza();
	//���� ���̽� & ���� �� �缳��
	void ResetPizza(int* setting);
	friend bool operator == (Pizza ordered, Pizza made);
	bool GetBase(int index);
	int GetToppings(int index);
};