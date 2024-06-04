#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <SDKDDKVer.h>
#include <tchar.h>
#include <string>
#include <gdiplus.h>

#include "Resource.h"
#include "order.h"

#define SCREEN_X 1280
#define SCREEN_Y 720

#pragma comment(lib, "Gdiplus.lib")

using namespace std;
using namespace Gdiplus;

UI ui;

GdiplusStartupInput m_GdiplusStartupInput;
ULONG_PTR m_GdiplusToken;
//GdiplusStartup(&m_GdiplusToken, &m_GdiplusStartupInput, NULL);

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

	CreateButton(hWnd, hInstance);



	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage) {
	case WM_CREATE:
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) { //��ư ��Ʈ��
		case GAMESTART: //���� ���� ��ư Ŭ�� ��
			gameState = ORDER; //�ֹ� �ޱ� ȭ�� ���
			ShowWindow(GetDlgItem(hWnd, GAMESTART), SW_HIDE); //���� ���� ��ư �����
			ShowWindow(GetDlgItem(hWnd, HOWTOPLAY), SW_HIDE); //���� ���� ��ư �����
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
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (gameState == START) {
			ShowWindow(GetDlgItem(hWnd, GAMESTART), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, HOWTOPLAY), SW_SHOW);
		}
		else if (gameState == EXPLAIN) {
			
		}
		else if (gameState == ORDER) {
			for (int index = 0; index < 3; index++) {
				ui.GetOrder();
			}
			ui.PrintList(hdc);
		}
		else if (gameState == MAKE) {
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hBrush);
			DeleteObject(hBrush);
		}
		else if (gameState == DELIVERY) {

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