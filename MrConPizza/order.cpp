#include "order.h"

#define PEPPERONI 3
#define TOMATO 4
#define PAPRIKA 5
#define PEPPER 6
#define ONION 7
#define OLIVE 8
#define SHRIMP 9
#define MUSHROOM 10

#define EASY 40
#define NORMAL 75
#define HARD 100

int GetRandom(int num) {
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(1, num);
	int random = dist(mt);

	return random;
}

Order::Order() {
	int orderCase = GetRandom(100);
	int setting[11] = { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
	//easy �ֹ�
	if (orderCase <= EASY) {
		switch (GetRandom(4)) {
		case 1:
			lstrcpy(place, L"�°�����");
			lstrcpy(menu, L"�ӽ��� ����");
			lstrcpy(delivery, L"�˶� ���");
			lstrcpy(special, L"X");
			setting[MUSHROOM] = 1;
			break;
		case 2:
			lstrcpy(place, L"ä������");
			lstrcpy(menu, L"���۷δ� ����");
			lstrcpy(delivery, L"�˶� ���");
			lstrcpy(special, L"X");
			setting[PEPPERONI] = 1;
			break;
		case 3:
			lstrcpy(place, L"��������");
			lstrcpy(menu, L"������ ����");
			lstrcpy(delivery, L"�˶� ���");
			lstrcpy(special, L"X");
			setting[SHRIMP] = 1;
			break;
		case 4:
			lstrcpy(place, L"�������");
			lstrcpy(menu, L"��Ͼ� ����");
			lstrcpy(delivery, L"���� ���");
			lstrcpy(special, L"X");
			setting[ONION] = 1;
			break;
		}
	}
	//normal �ֹ�
	else if (EASY < orderCase && orderCase <= NORMAL) {
		switch (GetRandom(6)) {
		case 1:
			lstrcpy(place, L"��� �п�");
			lstrcpy(menu, L"������ �ӽ��� ����");
			lstrcpy(delivery, L"�˶� ���");
			lstrcpy(special, L"X");
			setting[SHRIMP] = 1;
			setting[MUSHROOM] = 1;
			break;
		case 2:
			lstrcpy(place, L"�����Դ�");
			lstrcpy(menu, L"��Ͼ� ���۷δ� ����");
			lstrcpy(delivery, L"���� ���");
			lstrcpy(special, L"���۷δ� ���� �ּ���~");
			setting[ONION] = 1;
			setting[PEPPERONI] = 2;
			break;
		case 3:
			lstrcpy(place, L"�°�����");
			lstrcpy(menu, L"Ŀ���� ����");
			lstrcpy(delivery, L"�˶� ���");
			lstrcpy(special, L"������ ���� �� �÷��ּ���.");
			setting[TOMATO] = 1;
			setting[PEPPERONI] = 1;
			setting[PAPRIKA] = 1;
			break;
		case 4:
			lstrcpy(place, L"��������");
			lstrcpy(menu, L"�ø��� ����");
			lstrcpy(delivery, L"���� ���");
			lstrcpy(special, L"�ø��� 2�� �߰����ּ���!");
			setting[OLIVE] = 3;
			break;
		case 5:
			lstrcpy(place, L"�������");
			lstrcpy(menu, L"������ī �Ǹ� ����");
			lstrcpy(delivery, L"���� ���");
			lstrcpy(special, L"X");
			setting[PAPRIKA] = 1;
			setting[PEPPER] = 1;
			break;
		case 6:
			lstrcpy(place, L"ä������");
			lstrcpy(menu, L"Ŀ���� ����");
			lstrcpy(delivery, L"���� ���");
			lstrcpy(special, L"�׳� ������ ���� �԰�;��.");
			setting[1] = setting[2] = 0; //���츸
			break;
		}
	}
	//hard �ֹ�
	else if (NORMAL < orderCase && orderCase <= HARD) {
		switch (GetRandom(8)) {
		case 1:
			lstrcpy(place, L"��� ��");
			lstrcpy(menu, L"�õ巹�� ����");
			lstrcpy(delivery, L"�˶� ���");
			lstrcpy(special, L"X");
			for (int index = 3; index < 11; index++) {
				setting[index] = 1;
			}
			break;
		case 2:
			lstrcpy(place, L"��� �����");
			lstrcpy(menu, L"�õ巹�� ����");
			lstrcpy(delivery, L"���� ���");
			lstrcpy(special, L"�ſ� ���� ��� ���ּ���~");
			setting[MUSHROOM] = 1;
			setting[TOMATO] = 1;
			setting[SHRIMP] = 1;
			setting[OLIVE] = 1;
			break;
		case 3:
			lstrcpy(place, L"�°�����");
			lstrcpy(menu, L"��� ����");
			lstrcpy(delivery, L"���� ���");
			lstrcpy(special, L"������ ��� ���ڷ� ��Ź�����.");
			setting[2] = 0;
			setting[MUSHROOM] = 1;
			setting[TOMATO] = 1;
			setting[ONION] = 1;
			setting[PAPRIKA] = 1;
			setting[PEPPER] = 1;
			setting[OLIVE] = 1;
			break;
		case 4:
			lstrcpy(place, L"ä������");
			lstrcpy(menu, L"�ø��� ������ ����");
			lstrcpy(delivery, L"���� ���");
			lstrcpy(special, L"�ø��� �˷����Ⱑ �־��. ���ּ���.");
			setting[SHRIMP] = 1;
			break;
		case 5:
			lstrcpy(place, L"�����Դ�");
			lstrcpy(menu, L"Ŀ���� ����");
			lstrcpy(delivery, L"���� ���");
			lstrcpy(special, L"���� �ʿ� �� ���� ������ī ������ ��� �ͳ׿�.");
			setting[MUSHROOM] = 1;
			setting[PAPRIKA] = 1;
			break;
		case 6:
			lstrcpy(place, L"�������");
			lstrcpy(menu, L"ġ�� ����");
			lstrcpy(delivery, L"���� ���");
			lstrcpy(special, L"���� ġ� �ִ� ���ڷ� ��Ź�����.");
			setting[1] = 0;
			break;
		case 7:
			lstrcpy(place, L"��������");
			lstrcpy(menu, L"Ŀ���� ����");
			lstrcpy(delivery, L"�˶� ���");
			lstrcpy(special, L"����... �ʷ�... ����... ����...");
			setting[PEPPERONI] = 1;
			setting[TOMATO] = 1;
			setting[PEPPER] = 1;
			setting[ONION] = 1;
			setting[OLIVE] = 1;
			break;
		case 8:
			lstrcpy(place, L"��� ����");
			lstrcpy(menu, L"Ŀ���� ����");
			lstrcpy(delivery, L"���� ���");
			lstrcpy(special, L"��⸸ �÷��ּ���!");
			setting[PEPPERONI] = 1;
			setting[SHRIMP] = 1;
			break;
		}
	}
	pizza.ResetPizza(setting);
}

wchar_t* Order::GetPlace() {
	return place;
}

wchar_t* Order::GetMenu() {
	return menu;
}

wchar_t* Order::GetDelivery() {
	return delivery;
}

wchar_t* Order::GetSpecial() {
	return special;
}

Pizza Order::GetPizza() {
	return pizza;
}