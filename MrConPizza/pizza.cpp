#include "pizza.h"

#define NONE 0

//피자 클래스 state 초기화
Pizza::Pizza() {
	//배열에 매핑(일치 여부, 버튼에 이용)
	memset(base, false, sizeof(base));
	memset(toppings, 0, sizeof(toppings));
}

//주문에 맞춰 피자 메뉴 세팅
void Pizza::ResetPizza(int* setting) {
	int index = 0;
	for (; index < 3; index++) {
		if (setting[index] == 1) {
			base[index] = true;
		}
	}
	for (int index2 = 0; index2 < 8; index2++) {
		toppings[index2] = setting[index + index2];
	}
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

bool Pizza::GetBase(int index) {
	return base[index];
}

int Pizza::GetToppings(int index) {
	return toppings[index];
}