#include <iostream>

#include "pizza.h"

#define NONE 0

//피자 클래스 state 초기화
Pizza::Pizza()
	:name(NULL),
	dough(false), sauce(false), cheese(false),
	pepperoni(NONE), tomato(NONE), paprika(NONE), pepper(NONE), onion(NONE), olive(NONE), shrimp(NONE), mushroom(NONE) {
	//배열에 매핑(일치 여부, 버튼에 이용)
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

wchar_t* Pizza::GetPizza() {
	return name;
}

//주문 피자와 제작 피자가 일치하면 true, 다르면 false
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