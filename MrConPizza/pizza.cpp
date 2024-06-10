#include "pizza.h"

#define NONE 0

//���� Ŭ���� state �ʱ�ȭ
Pizza::Pizza() {
	//�迭�� ����(��ġ ����, ��ư�� �̿�)
	memset(base, false, sizeof(base));
	memset(toppings, 0, sizeof(toppings));
}

//�ֹ��� ���� ���� �޴� ����
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

bool Pizza::GetBase(int index) {
	return base[index];
}

int Pizza::GetToppings(int index) {
	return toppings[index];
}