#include <iostream>
#include <Windows.h>
#include <tchar.h>

#define GAME_START 0
#define HOW_TO_PLAY 1
#define GAME_END -1
/*
//�޽���(�̺�Ʈ) �߻� �� �޽����� ���޹޾� ó���ϴ� ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//�ν��Ͻ� �ڵ�
HINSTANCE g_hInst;

//���� ������ �ڵ�
HWND hWndMain;

//Ÿ��Ʋ ���ڿ�
LPCTSTR lpszClass = _T("Mr.Con Pizza");

//���� ������ ���� init
void WndClassInit(WNDCLASS* WndClass, HINSTANCE hInstance) {
	WndClass->cbClsExtra = 0;
	WndClass->cbWndExtra = 0;
	WndClass->hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //������ ��� ���� ����
	WndClass->hCursor = LoadCursor(NULL, IDC_ARROW); //Ŀ�� ����
	WndClass->hIcon = LoadIcon(NULL, IDI_APPLICATION); //������ ����
	WndClass->hInstance = hInstance; //�ش� ������ Ŭ������ ����ϴ� ���α׷� ��ȣ
	WndClass->lpfnWndProc = WndProc; //�ش� �����쿡�� �߻��ϴ� �޽����� ó���ϴ� �Լ� ����
	WndClass->lpszClassName = lpszClass; //������ Ŭ���� �̸� ����
	WndClass->lpszMenuName = NULL; //���α׷��� ����� �޴� ����
	WndClass->style = CS_HREDRAW | CS_VREDRAW; //������ ���� ����, |(or)�� �̿��� ���� �� ���
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
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	hWndMain = hWnd;

	HWND gameStart = CreateWindowW(L"button", L"���� ����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 400, 100, 20, hWnd, (HMENU)0, g_hInst, NULL);
	hWndMain = gameStart;

	HWND howTOPlay = CreateWindowW(L"button", L"���� ����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 440, 100, 20, hWnd, (HMENU)1, g_hInst, NULL);
	hWndMain = howTOPlay;
	
	HWND gameEnd = CreateWindowW(L"button", L"���� ����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 480, 100, 20, hWnd, (HMENU)-1, g_hInst, NULL);
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
			MessageBox(hWnd, L"���� ���� Ŭ��", L"Button", MB_OK);
			break;
		case 1:
			MessageBox(hWnd, L"���� ���� Ŭ��", L"Button", MB_OK);
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