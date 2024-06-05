#include <iostream>
#include <Windows.h>
#include <tchar.h>

#define GAME_START 0
#define HOW_TO_PLAY 1
#define GAME_END -1
/*
//메시지(이벤트) 발생 시 메시지를 전달받아 처리하는 역할
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//인스턴스 핸들
HINSTANCE g_hInst;

//메인 윈도우 핸들
HWND hWndMain;

//타이틀 문자열
LPCTSTR lpszClass = _T("Mr.Con Pizza");

//메인 윈도우 설정 init
void WndClassInit(WNDCLASS* WndClass, HINSTANCE hInstance) {
	WndClass->cbClsExtra = 0;
	WndClass->cbWndExtra = 0;
	WndClass->hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //윈도우 배경 색상 지정
	WndClass->hCursor = LoadCursor(NULL, IDC_ARROW); //커서 지정
	WndClass->hIcon = LoadIcon(NULL, IDI_APPLICATION); //아이콘 지정
	WndClass->hInstance = hInstance; //해당 윈도우 클래스를 등록하는 프로그램 번호
	WndClass->lpfnWndProc = WndProc; //해당 윈도우에서 발생하는 메시지를 처리하는 함수 지정
	WndClass->lpszClassName = lpszClass; //윈도우 클래스 이름 정의
	WndClass->lpszMenuName = NULL; //프로그램이 사용할 메뉴 지정
	WndClass->style = CS_HREDRAW | CS_VREDRAW; //윈도우 형태 지정, |(or)을 이용해 여러 개 사용
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
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	hWndMain = hWnd;

	HWND gameStart = CreateWindowW(L"button", L"게임 시작", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 400, 100, 20, hWnd, (HMENU)0, g_hInst, NULL);
	hWndMain = gameStart;

	HWND howTOPlay = CreateWindowW(L"button", L"게임 설명", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 440, 100, 20, hWnd, (HMENU)1, g_hInst, NULL);
	hWndMain = howTOPlay;
	
	HWND gameEnd = CreateWindowW(L"button", L"게임 종료", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 480, 100, 20, hWnd, (HMENU)-1, g_hInst, NULL);
	hWndMain = gameEnd;

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_CREATE:
		
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 0:
			MessageBox(hWnd, L"게임 시작 클릭", L"Button", MB_OK);
			break;
		case 1:
			MessageBox(hWnd, L"게임 설명 클릭", L"Button", MB_OK);
			break;
		}
		return 0;
	//case WM_LBUTTONDOWN:
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
*/
// https://chanos.tistory.com/category/%EA%B0%9C%EB%B0%9C/Win32%20API%20Programming?page=1
// https://www.youtube.com/playlist?list=PL4SIC1d_ab-ZLg4TvAO5R4nqlJTyJXsPK