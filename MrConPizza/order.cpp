#include <windows.h>

#include "order.h"

Order::Order(int orderCase) {
	int setting[11] = { 0 };
	if (0 <= orderCase && orderCase <= 10) {
		lstrcpy(place, L"�°�����");
		lstrcpy(menu, L"�ӽ��� ����");
		lstrcpy(delivery, L"�˶� ���");
		lstrcpy(special, L"X");
		
	}
	switch (orderCase) {
	case 0:
		
		break;
	case 1:
		lstrcpy(place, L"ä������");
		lstrcpy(delivery, L"�˶� ���");
		lstrcpy(special, L"X");
		break;
	case 2:
	}
}

wchar_t* Order::GetPlace() {
	return place;
}

wchar_t* Order::GetPizza() {
	return pizza.GetPizza();
}

wchar_t* Order::GetDelivery() {
	return delivery;
}

wchar_t* Order::GetSpecial() {
	return special;
}

UI::UI() {
	star = 3;
	day = 1;
}

void UI::GetOrder() {
	Order* order = new Order(rand() % 8);
	LPWSTR text = lstrcat(lstrcat(lstrcat(lstrcat(order->GetPlace(), L"\r\n"), lstrcat(order->GetPizza(), L"\r\n")),
				  lstrcat(order->GetDelivery(), L"\r\n")), lstrcat(order->GetSpecial(), L"\r\n"));

	bool choose = MessageBox(NULL, text, L"�ֹ�", MB_YESNO);
	if (choose == IDYES) {
		list.push(order);
	}
	else {
		delete order;
		this->star--;
	}
}

void UI::PrintList(HDC hdc) {
	SetTextAlign(hdc, TA_CENTER);
	TextOut(hdc, 800, 20, L"�ֹ���", lstrlen(L"�ֹ���"));
	int i = 0;

	for (queue<Order*> temp = list; !temp.empty(); temp.pop()) {
		Order* index = temp.front();
		TCHAR* place = index->GetPlace();
		TCHAR* pizza = index->GetPizza();
		TCHAR* delivery = index->GetDelivery();
		TCHAR* special = index->GetSpecial();

		TextOut(hdc, 800, 40 + i * 20, place, lstrlen(place));
		TextOut(hdc, 800, 40 + i * 40, pizza, lstrlen(pizza));
		TextOut(hdc, 800, 40 + i * 60, delivery, lstrlen(delivery));
		TextOut(hdc, 800, 40 + i * 80, special, lstrlen(special));

		i++;
	}
}