#include <windows.h>

#include "order.h"

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

Order::Order() {

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
	Order* order = new Order();
	LPWSTR text = lstrcat(lstrcat(lstrcat(lstrcat(order->GetPlace(), L"\r\n"), lstrcat(order->GetPizza(), L"\r\n")),
				  lstrcat(order->GetDelivery(), L"\r\n")), lstrcat(order->GetSpecial(), L"\r\n"));

	bool choose = MessageBox(NULL, text, L"주문", MB_YESNO);
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
	TextOut(hdc, 800, 20, L"주문서", lstrlen(L"주문서"));
	int i = 0;
	for (queue<Order*> temp = list; !temp.empty(); temp.pop(), i++) {
		Order* index = temp.front();
		TCHAR* place = index->GetPlace();
		TCHAR* pizza = index->GetPizza();
		TCHAR* delivery = index->GetDelivery();
		TCHAR* special = index->GetSpecial();

		TextOut(hdc, 800, 40 + i * 20, place, lstrlen(place));
		TextOut(hdc, 800, 40 + i * 40, pizza, lstrlen(pizza));
		TextOut(hdc, 800, 40 + i * 60, delivery, lstrlen(delivery));
		TextOut(hdc, 800, 40 + i * 80, special, lstrlen(special));
	}
}