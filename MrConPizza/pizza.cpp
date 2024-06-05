#include <iostream>

#include "pizza.h"

#define NONE 0

//���� Ŭ���� state �ʱ�ȭ
Pizza::Pizza()
	:dough(false), sauce(false), cheese(false),
	pepperoni(NONE), tomato(NONE), paprika(NONE), pepper(NONE), onion(NONE), olive(NONE), shrimp(NONE), mushroom(NONE) {
	//�迭�� ����(��ġ ����, ��ư�� �̿�)
	base[0] = &dough;
	base[1] = &sauce;
	base[2] = &cheese;

	toppings[0] = &pepperoni;
	toppings[1] = &tomato;
	toppings[2] = &paprika;
	toppings[3] = &pepper;
	toppings[4] = &onion;
	toppings[5] = &olive;
	toppings[6] = &shrimp;
	toppings[7] = &mushroom;
}

Pizza::Pizza(int* setting) {
	Pizza();
	
	int index = 0;
	for (; index < 3; index++) {
		if (setting[index] == 1) {
			*base[index] = true;
		}
	}
	for (int index2 = 0; index2 < 8; index2++) {
		*toppings[index2] = setting[index + index2];
	}
}

//�ֹ� ���ڿ� ���� ���ڰ� ��ġ�ϸ� true, �ٸ��� false
bool operator == (Pizza ordered, Pizza made) {
	int index = 0;
	for (; index < 3; index++) {
		if (ordered.base[index] != made.base[index] || ordered.toppings[index] != made.toppings[index]) {
			return false;
		}
	}
	for (; index < 8; index++) {
		if (ordered.toppings[index] != made.toppings[index]) {
			return false;
		}
	}

	return true;
}