#include "ui.h"

UI::UI() {
	star = 3;
	day = 1;
	dough = false;
}

bool UI::GetDough() {
	return dough;
}

void UI::IsSame() {
	if ((list.front()->GetPizza() == *deliveryBox.front()) == false) {
		star--;
	}
	deliveryBox.pop();
	list.pop();
}

int UI::GetDay() {
	return day;
}

int UI::GetBoxSize() {
	return deliveryBox.size();
}

queue<Order*> UI::GetList() {
	return list;
}

void UI::InputBox(Pizza* pizza) {
	deliveryBox.push(pizza);
}

void UI::SetDough(bool setting) {
	dough = setting;
}

void UI::GetOrder() {
	Order* order = new Order();

	wchar_t text[160];
	wsprintf(text, L"�ּ�: %s\r\n�޴�: %s\r\n���: %s\r\n��û ����: %s\r\n", order->GetPlace(), order->GetMenu(), order->GetDelivery(), order->GetSpecial());

	int choose = MessageBox(NULL, text, L"�ֹ�", MB_YESNO);
	if (choose == IDYES) {
		list.push(order);
	}
	else {
		delete order;
		this->star--;
	}
}

void UI::PrintList(HDC hdc) {
	int i = 0;
	wchar_t text[100];
	
	SetTextAlign(hdc, TA_LEFT);
	TextOut(hdc, 900, 20, L"�ֹ���", lstrlen(L"�ֹ���"));
	
	for (queue<Order*> temp = list; !temp.empty(); temp.pop()) {
		Order* index = temp.front();
		
		wsprintf(text, L"�ּ�: %s", index->GetPlace());
		TextOut(hdc, 900, 40 + i * 100, text, lstrlen(text));
		wsprintf(text, L"�޴�: %s", index->GetMenu());
		TextOut(hdc, 900, 60 + i * 100, text, lstrlen(text));
		wsprintf(text, L"���: %s", index->GetDelivery());
		TextOut(hdc, 900, 80 + i * 100, text, lstrlen(text));
		wsprintf(text, L"��û ����: %s", index->GetSpecial());
		TextOut(hdc, 900, 100 + i * 100, text, lstrlen(text));

		i++;
	}
}