#pragma once
#include <windows.h>
#include <queue>
#include <tchar.h>

#include "order.h"

class UI {
private:
	int star;
	int day;
	bool dough;
	queue<Order*> list;
	queue<Pizza*> deliveryBox;
public:
	UI();
	//���� ���� ���� Ȯ��
	bool GetDough(); 

	//(�ֹ� ����) == (���� ����) Ȯ�� �Լ�
	void IsSame();
	
	//day ���
	int GetDay();
	
	//������ ���� ���� Ȯ�� �Լ�
	int GetBoxSize();
	
	//��� ���ڿ� ���� ����
	void InputBox(Pizza* pizza);
	
	//���� ���� ����
	void SetDough(bool setting);
	
	//�ֹ� �޴� �Լ�
	void GetOrder();
	
	//�ֹ��� ����Ʈ ���
	void PrintList(HDC hdc);
	
	//�ֹ� ����Ʈ �ҷ�����
	queue<Order*> GetList();
};