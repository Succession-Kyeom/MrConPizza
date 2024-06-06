#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <SDKDDKVer.h>
#include <tchar.h>
#include <string>
#include <gdiplus.h>

#include "Resource.h"
#include "pizza.h"
#include "order.h"
#include "ui.h"

//������ ũ�� ����
#define SCREEN_X 1280
#define SCREEN_Y 720

#pragma comment(lib, "Gdiplus.lib")

using namespace std;
using namespace Gdiplus;

UI ui;

GdiplusStartupInput m_GdiplusStartupInput;
ULONG_PTR m_GdiplusToken;
//GdiplusStartup(&m_GdiplusToken, &m_GdiplusStartupInput, NULL);

//���� ���� ����(�ʱⰪ START)
enum GameState { START, EXPLAIN, ORDER, MAKE, DELIVERY };
GameState gameState = START;

//�޽���(�̺�Ʈ) �߻� �� �޽����� ���޹޾� ó���ϴ� ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//�ν��Ͻ� �ڵ�
HINSTANCE g_hInst;
HINSTANCE hInstance;

//���� ������ �ڵ�
HWND hWndMain;

//Ÿ��Ʋ ���ڿ�
LPCTSTR lpszClass = _T("Mr.Con Pizza");

//���� ������ ���� init
void WndClassInit(WNDCLASS* WndClass, HINSTANCE hInstance) {
	WndClass->cbClsExtra = 0;
	WndClass->cbWndExtra = 0;
	WndClass->hbrBackground = (HBRUSH)CreateSolidBrush(RGB(43, 193, 188)); //������ ��� ���� ����
	WndClass->hCursor = LoadCursor(NULL, IDC_ARROW); //Ŀ�� ����
	WndClass->hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_PIZZATEST)); //������ ����
	WndClass->hInstance = hInstance; //�ش� ������ Ŭ������ ����ϴ� ���α׷� ��ȣ
	WndClass->lpfnWndProc = WndProc; //�ش� �����쿡�� �߻��ϴ� �޽����� ó���ϴ� �Լ� ����
	WndClass->lpszClassName = lpszClass; //������ Ŭ���� �̸� ����
	WndClass->lpszMenuName = NULL; //���α׷��� ����� �޴� ����
	WndClass->style = CS_HREDRAW | CS_VREDRAW; //������ ���� ����, |(or)�� �̿��� ���� �� ���
}

//��ư ���� �Լ�
void CreateButton(HWND hWnd, HINSTANCE hInstance) {
	CreateWindowW(L"Button", L"���� ����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 950, 475, 200, 50, hWnd, (HMENU)GAMESTART, hInstance, NULL);
	CreateWindowW(L"Button", L"���� ����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 950, 555, 200, 50, hWnd, (HMENU)HOWTOPLAY, hInstance, NULL);
	CreateWindowW(L"Button", L"���ư���", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 950, 555, 200, 50, hWnd, (HMENU)BACK, hInstance, NULL);
	
	//���� ���� �� ��� ��ư
	CreateWindowW(L"Button", L"����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 30, 100, 100, 25, hWnd, (HMENU)DOUGH, hInstance, NULL);
	CreateWindowW(L"Button", L"�ҽ�", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 100, 100, 25, hWnd, (HMENU)SAUCE, hInstance, NULL);
	CreateWindowW(L"Button", L"ġ��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 30, 140, 100, 25, hWnd, (HMENU)CHEESE, hInstance, NULL);
	CreateWindowW(L"Button", L"���۷δ�", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 140, 100, 25, hWnd, (HMENU)PEPPERONI, hInstance, NULL);
	CreateWindowW(L"Button", L"�丶��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 30, 180, 100, 25, hWnd, (HMENU)TOMATO, hInstance, NULL);
	CreateWindowW(L"Button", L"�Ǹ�", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 180, 100, 25, hWnd, (HMENU)PEPPER, hInstance, NULL);
	CreateWindowW(L"Button", L"����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 30, 220, 100, 25, hWnd, (HMENU)ONION, hInstance, NULL);
	CreateWindowW(L"Button", L"�ø���", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 220, 100, 25, hWnd, (HMENU)OLIVE, hInstance, NULL);
	CreateWindowW(L"Button", L"����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 30, 260, 100, 25, hWnd, (HMENU)SHRIMP, hInstance, NULL);
	CreateWindowW(L"Button", L"����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 260, 100, 25, hWnd, (HMENU)MUSHROOM, hInstance, NULL);
	CreateWindowW(L"Button", L"����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 30, 340, 100, 25, hWnd, (HMENU)DISPOSAL, hInstance, NULL);
	CreateWindowW(L"Button", L"����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 340, 100, 25, hWnd, (HMENU)COOK, hInstance, NULL);
}

//��ư �ʱ�ȭ(��� ��ư �����)
void InitButton(HWND hWnd) {
	ShowWindow(GetDlgItem(hWnd, GAMESTART), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, HOWTOPLAY), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, BACK), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, DOUGH), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, SAUCE), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, CHEESE), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, PEPPERONI), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, TOMATO), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, PEPPER), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, ONION), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, OLIVE), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, SHRIMP), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, MUSHROOM), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, DISPOSAL), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, COOK), SW_HIDE);
}

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmdParam, _In_ int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClassInit(&WndClass, hInstance);

	//������ Ŭ������ Ŀ�ο� ���
	RegisterClass(&WndClass);

	//��ϵ� �����츦 �޸𸮿� ����
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, SCREEN_X, SCREEN_Y, NULL, (HMENU)NULL, hInstance, NULL);
	hWndMain = hWnd;
	ShowWindow(hWnd, nCmdShow);

	//��ư �ʱ�ȭ
	CreateButton(hWnd, hInstance);
	InitButton(hWnd);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	int setting[11] = { 0 };
	Pizza* pizza = new Pizza();

	switch (iMessage) {
	case WM_CREATE:
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) { //��ư ��Ʈ��
		case GAMESTART: //���� ���� ��ư Ŭ�� ��
			gameState = ORDER; //�ֹ� �ޱ� ȭ�� ���
			ShowWindow(GetDlgItem(hWnd, GAMESTART), SW_HIDE); //���� ���� ��ư �����
			ShowWindow(GetDlgItem(hWnd, HOWTOPLAY), SW_HIDE); //���� ���� ��ư �����
			ShowWindow(GetDlgItem(hWnd, BACK), SW_HIDE); //���ư��� ��ư �����
			if (gameState == ORDER) {
				while (ui.GetList().size() != 1 + ui.GetDay() * 2) {
					ui.GetOrder();
				}
				gameState = MAKE;
			}
			break;
		case HOWTOPLAY: //���� ���� ��ư Ŭ�� ��
			gameState = EXPLAIN; //���� ���� ȭ�� ���
			ShowWindow(GetDlgItem(hWnd, GAMESTART), SW_HIDE); //���� ���� ��ư �����
			ShowWindow(GetDlgItem(hWnd, HOWTOPLAY), SW_HIDE); //���� ���� ��ư �����
			break;
		case BACK:
			gameState = START;
			ShowWindow(GetDlgItem(hWnd, BACK), SW_HIDE); //���ư��� ��ư �����
			break;
		case DOUGH: //���� ���� & ���� ���� ����
			if (ui.GetDough() == false) {
				ui.SetDough(true);
				pizza = new Pizza();
				setting[DOUGH] = 1;
				pizza->ResetPizza(setting);
			}
			break;
		case SAUCE:
			setting[SAUCE] = 1;
			pizza->ResetPizza(setting);
			break;
		case CHEESE:
			setting[CHEESE] = 1;
			pizza->ResetPizza(setting);
			break;
		case PEPPERONI:
			setting[PEPPERONI]++;
			pizza->ResetPizza(setting);
			break;
		case TOMATO:
			setting[TOMATO]++;
			pizza->ResetPizza(setting);
			break;
		case PAPRIKA:
			setting[PAPRIKA]++;
			pizza->ResetPizza(setting);
			break;
		case PEPPER:
			setting[PEPPER]++;
			pizza->ResetPizza(setting);
			break;
		case ONION:
			setting[ONION]++;
			pizza->ResetPizza(setting);
			break;
		case OLIVE:
			setting[OLIVE]++;
			pizza->ResetPizza(setting);
			break;
		case SHRIMP:
			setting[SHRIMP]++;
			pizza->ResetPizza(setting);
			break;
		case MUSHROOM:
			setting[MUSHROOM]++;
			pizza->ResetPizza(setting);
			break;
		case DISPOSAL: //���̽� & ���� ����
			if (ui.GetDough() == true) {
				ui.SetDough(false);
				delete pizza;

				for (int index = 0; index < 11; index++) {
					setting[index] = 0;
				}
			}
			break;
		case COOK: //���� ���� Ȯ��
			if (ui.GetDough() == true) {
				ui.SetDough(false);
				ui.InputBox(pizza);

				for (int index = 0; index < 11; index++) {
					setting[index] = 0;
				}

				//(������ ���� ����) == (�ֹ� ���� ���� ����) ��ġ �� ��޷� �Ѿ��
				if (ui.GetBoxSize() == ui.GetList().size()) {
					gameState = DELIVERY;
				}
			}

			break;
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (gameState == START) {
			ShowWindow(GetDlgItem(hWnd, GAMESTART), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, HOWTOPLAY), SW_SHOW);
		}
		else if (gameState == EXPLAIN) {
			ShowWindow(GetDlgItem(hWnd, BACK), SW_SHOW);
		}
		else if (gameState == ORDER) {
			ui.PrintList(hdc);
		}
		else if (gameState == MAKE) {
			ui.PrintList(hdc);
			ShowWindow(GetDlgItem(hWnd, DOUGH), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, SAUCE), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, CHEESE), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, PEPPERONI), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, TOMATO), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, PEPPER), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, ONION), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, OLIVE), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, SHRIMP), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, MUSHROOM), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, DISPOSAL), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, COOK), SW_SHOW);
		}
		else if (gameState == DELIVERY) {
			ShowWindow(GetDlgItem(hWnd, DOUGH), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, SAUCE), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, CHEESE), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, PEPPERONI), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, TOMATO), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, PEPPER), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, ONION), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, OLIVE), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, SHRIMP), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, MUSHROOM), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, DISPOSAL), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, COOK), SW_HIDE);
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

// https://chanos.tistory.com/category/%EA%B0%9C%EB%B0%9C/Win32%20API%20Programming?page=1
// https://www.youtube.com/playlist?list=PL4SIC1d_ab-ZLg4TvAO5R4nqlJTyJXsPK
// https://skql.tistory.com/536
// https://nx006.tistory.com/19