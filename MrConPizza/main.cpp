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

//메시지(이벤트) 발생 시 메시지를 전달받아 처리하는 역할
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//인스턴스 핸들
HINSTANCE g_hInst;
HINSTANCE hInstance;

//메인 윈도우 핸들
HWND hWndMain;

//타이틀 문자열
LPCTSTR lpszClass = _T("Mr.Con Pizza");

//메인 윈도우 설정 init
void WndClassInit(WNDCLASS* WndClass, HINSTANCE hInstance) {
	WndClass->cbClsExtra = 0;
	WndClass->cbWndExtra = 0;
	WndClass->hbrBackground = (HBRUSH)CreateSolidBrush(RGB(43, 193, 188)); //윈도우 배경 색상 지정
	WndClass->hCursor = LoadCursor(NULL, IDC_ARROW); //커서 지정
	WndClass->hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_PIZZATEST)); //아이콘 지정
	WndClass->hInstance = hInstance; //해당 윈도우 클래스를 등록하는 프로그램 번호
	WndClass->lpfnWndProc = WndProc; //해당 윈도우에서 발생하는 메시지를 처리하는 함수 지정
	WndClass->lpszClassName = lpszClass; //윈도우 클래스 이름 정의
	WndClass->lpszMenuName = NULL; //프로그램이 사용할 메뉴 지정
	WndClass->style = CS_HREDRAW | CS_VREDRAW; //윈도우 형태 지정, |(or)을 이용해 여러 개 사용
}

//버튼 생성 함수
void CreateButton(HWND hWnd, HINSTANCE hInstance) {
	CreateWindowW(L"Button", L"게임 시작", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 950, 475, 200, 50, hWnd, (HMENU)GAMESTART, hInstance, NULL);
	CreateWindowW(L"Button", L"게임 설명", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 950, 555, 200, 50, hWnd, (HMENU)HOWTOPLAY, hInstance, NULL);
	CreateWindowW(L"Button", L"돌아가기", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 950, 555, 200, 50, hWnd, (HMENU)BACK, hInstance, NULL);
}

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmdParam, _In_ int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClassInit(&WndClass, hInstance);

	//정의한 클래스를 커널에 등록
	RegisterClass(&WndClass);

	//등록된 윈도우를 메모리에 생성
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
		switch (LOWORD(wParam)) { //버튼 컨트롤
		case GAMESTART: //게임 시작 버튼 클릭 시
			gameState = ORDER; //주문 받기 화면 출력
			ShowWindow(GetDlgItem(hWnd, GAMESTART), SW_HIDE); //게임 시작 버튼 숨기기
			ShowWindow(GetDlgItem(hWnd, HOWTOPLAY), SW_HIDE); //게임 설명 버튼 숨기기
			break;
		case HOWTOPLAY: //게임 설명 버튼 클릭 시
			gameState = EXPLAIN; //게임 설명 화면 출력
			ShowWindow(GetDlgItem(hWnd, GAMESTART), SW_HIDE); //게임 시작 버튼 숨기기
			ShowWindow(GetDlgItem(hWnd, HOWTOPLAY), SW_HIDE); //게임 설명 버튼 숨기기
			break;
		case BACK:
			gameState = START;
			ShowWindow(GetDlgItem(hWnd, BACK), SW_HIDE); //돌아가기 버튼 숨기기
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