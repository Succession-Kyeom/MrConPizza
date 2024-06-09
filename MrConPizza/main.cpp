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
#include "playermotorbike.h"
#include "enemymotorbike.h"
#include "building.h"

// ������ ũ�� ����
#define SCREEN_X 1280
#define SCREEN_Y 720
#define IMAGE_WIDTH 512
#define IMAGE_HEIGHT 384

#pragma comment(lib, "Gdiplus.lib")

using namespace std;
using namespace Gdiplus;

//�� ����ü(rect, RGB)
struct Wall {
    RECT rect;
    COLORREF color;
};

GdiplusStartupInput m_GdiplusStartupInput;
ULONG_PTR m_GdiplusToken;

// ���� ���� ����(�ʱⰪ START)
enum GameState { START, EXPLAIN, ORDER, MAKE, DELIVERY };
GameState gameState = START;

// �޽���(�̺�Ʈ) �߻� �� �޽����� ���޹޾� ó���ϴ� ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// �ν��Ͻ� �ڵ�
HINSTANCE g_hInst;
HINSTANCE hInstance;

// ���� ������ �ڵ�
HWND hWndMain;

// Ÿ��Ʋ ���ڿ�
LPCTSTR lpszClass = _T("Mr.Con Pizza");

//���� ��ü, ���� ����
UI ui;
PlayerMotorbike* playerBike;
EnemyMotorbike* enemyBike[4];

const int wallCount = 20;
Wall walls[wallCount] = {
    { {0, 17, 762, 30}, RGB(255, 0, 0) },
    { {0, 192, 30, 180}, RGB(255, 0, 0) },
    { {19, 33, 30, 190}, RGB(255, 0, 0) },
    { {100, 67, 112, 190}, RGB(255, 0, 0) },
    { {100, 67, 296, 77}, RGB(255, 0, 0) },
    { {281, 67, 294, 190}, RGB(255, 0, 0) },
    { {0, 240, 33, 400}, RGB(255, 0, 0) },
    { {0, 407, 162, 421}, RGB(255, 0, 0) },
    { {151, 410, 166, 564}, RGB(255, 0, 0) },
    { {231, 363, 250, 530}, RGB(255, 0, 0) },
    { {280, 236, 296, 389}, RGB(255, 0, 0) },
    { {370, 66, 695, 77}, RGB(255, 0, 0) },
    { {370, 66, 383, 167}, RGB(255, 0, 0) },
    { {684, 66, 697, 170}, RGB(255, 0, 0) },
    { {764, 17, 779, 568}, RGB(255, 0, 0) },
    { {284, 400, 428, 429}, RGB(255, 0, 0) },
    { {404, 409, 428, 511}, RGB(255, 0, 0) },
    { {500, 410, 517, 510}, RGB(255, 0, 0) },
    { {525, 261, 661, 339}, RGB(255, 0, 0) },
    { {500, 410, 662, 421}, RGB(255, 0, 0) }
};

const int buildingCount = 6;
Building* buildings[buildingCount];

bool g_controlLocked = false;
bool g_upPressed = false;
bool g_leftPressed = false;
bool g_downPressed = false;
bool g_rightPressed = false;
bool timerSet = false;

HDC hdcStatic = NULL;
HBITMAP hbmStatic = NULL;
//

// ���� ������ ���� init
void WndClassInit(WNDCLASS* WndClass, HINSTANCE hInstance) {
    WndClass->cbClsExtra = 0;
    WndClass->cbWndExtra = 0;
    WndClass->hbrBackground = (HBRUSH)CreateSolidBrush(RGB(43, 193, 188)); // ������ ��� ���� ����
    WndClass->hCursor = LoadCursor(NULL, IDC_ARROW); // Ŀ�� ����
    WndClass->hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_PIZZATEST)); // ������ ����
    WndClass->hInstance = hInstance; // �ش� ������ Ŭ������ ����ϴ� ���α׷� ��ȣ
    WndClass->lpfnWndProc = WndProc; // �ش� �����쿡�� �߻��ϴ� �޽����� ó���ϴ� �Լ� ����
    WndClass->lpszClassName = lpszClass; // ������ Ŭ���� �̸� ����
    WndClass->lpszMenuName = NULL; // ���α׷��� ����� �޴� ����
    WndClass->style = CS_HREDRAW | CS_VREDRAW; // ������ ���� ����, |(or)�� �̿��� ���� �� ���
}

// ��ư ���� �Լ�
void CreateButton(HWND hWnd, HINSTANCE hInstance) {
    CreateWindowW(L"Button", L"���� ����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 950, 475, 200, 50, hWnd, (HMENU)GAMESTART, hInstance, NULL);
    CreateWindowW(L"Button", L"���� ����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 950, 555, 200, 50, hWnd, (HMENU)HOWTOPLAY, hInstance, NULL);
    CreateWindowW(L"Button", L"���ư���", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 950, 555, 200, 50, hWnd, (HMENU)BACK, hInstance, NULL);

    // ���� ���� �� ��� ��ư
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
    CreateWindowW(L"Button", L"������ī", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 30, 300, 100, 25, hWnd, (HMENU)PAPRIKA, hInstance, NULL);
    CreateWindowW(L"Button", L"����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 30, 340, 100, 25, hWnd, (HMENU)DISPOSAL, hInstance, NULL);
    CreateWindowW(L"Button", L"����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 340, 100, 25, hWnd, (HMENU)COOK, hInstance, NULL);
}

// ��ư �ʱ�ȭ(��� ��ư �����)
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
    ShowWindow(GetDlgItem(hWnd, PAPRIKA), SW_HIDE);
    ShowWindow(GetDlgItem(hWnd, DISPOSAL), SW_HIDE);
    ShowWindow(GetDlgItem(hWnd, COOK), SW_HIDE);
}

// �̹��� �ε� �� �׸��� �Լ�
void DrawImageFromFile(HDC hdc, const WCHAR* filename, int x, int y, int width, int height) {
    Graphics graphics(hdc);
    Image image(filename);
    graphics.DrawImage(&image, x - 30, y - 40, width, height);
}

//�� �׸��� �Լ�
void DrawWalls(Graphics& graphics) {
    for (int index = 0; index < wallCount; index++) {
        SolidBrush brush(Color(255, GetRValue(walls[index].color), GetGValue(walls[index].color), GetBValue(walls[index].color)));
        Rect rect(walls[index].rect.left, walls[index].rect.top, walls[index].rect.right - walls[index].rect.left, walls[index].rect.bottom - walls[index].rect.top);
        graphics.FillRectangle(&brush, rect);
    }
}

//�ǹ� �׸��� �Լ�
void DrawBuildings(Graphics& graphics) {
    for (int index = 0; index < buildingCount; index++) {
        buildings[index]->Draw(graphics);
    }
}

//�ǹ� �浹 ���� �Լ�
int CheckCollisionWithBuildings(int x, int y, int radius) {
    for (int index = 0; index < buildingCount; index++) {
        if (buildings[index]->CheckCollision(x, y, radius)) {
            return 1;
        }
    }
    return -1;
}

//������� �浹 ���� �Լ�
bool CheckCollisionWithEnemy(int x, int y, int radius) {
    for (int index = 0; index < 4; index++) {
        int enemyCenterX = enemyBike[index]->x;
        int enemyCenterY = enemyBike[index]->y;

        int distanceSquared = pow((x - enemyCenterX), 2) + pow((y - enemyCenterY), 2);
        int radiusSquared = pow((radius + ENEMY_RADIUS), 2);

        if (distanceSquared <= radiusSquared) {
            return true;
        }
    }
    return false;
}

// ���
void DrawBackFromFile(HDC hdc, const WCHAR* filename, int x, int y, int width, int height) {
    Graphics graphics(hdc);
    Image image(filename);
    graphics.DrawImage(&image, x, y, width, height);
}

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmdParam, _In_ int nCmdShow) {
    HWND hWnd;
    MSG Message;
    WNDCLASS WndClass;
    g_hInst = hInstance;

    WndClassInit(&WndClass, hInstance);

    // GDI+ �ʱ�ȭ
    GdiplusStartup(&m_GdiplusToken, &m_GdiplusStartupInput, NULL);

    // ������ Ŭ������ Ŀ�ο� ���
    RegisterClass(&WndClass);

    // ��ϵ� �����츦 �޸𸮿� ����
    hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, SCREEN_X, SCREEN_Y, NULL, (HMENU)NULL, hInstance, NULL);
    hWndMain = hWnd;
    ShowWindow(hWnd, nCmdShow);

    // ��ư �ʱ�ȭ
    CreateButton(hWnd, hInstance);
    InitButton(hWnd);

    while (GetMessage(&Message, NULL, 0, 0)) {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }

    // GDI+ ����
    GdiplusShutdown(m_GdiplusToken);

    return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
    static int setting[11] = { 0 }; // static���� �����Ͽ� ��� �����ǵ��� ��
    static Pizza* pizza = nullptr; // ���� ��ü�� ���������� ����
    static int prevX, prevY;
    static Image* backgroundImage = nullptr;

    PAINTSTRUCT ps;
    HDC hdc;

    Graphics staticGraphics(hdcStatic);
    SolidBrush backgroundBrush(Color(255, 255, 255, 255));

    HDC hdcMem;
    HBITMAP hbmMem;
    HBITMAP hbmOld;

    switch (iMessage) {
    case WM_CREATE:
        SetTimer(hWnd, ID_TIMER_MOVE, 50, NULL);
        timerSet = true;

        playerBike = new PlayerMotorbike(190, 190, BALL_RADIUS, L"NormalRight.bmp");
        prevX = playerBike->x;
        prevY = playerBike->y;

        enemyBike[0] = new EnemyMotorbike(80, 100, ENEMY_RADIUS, L"enemyRight.bmp", L"enemyLeft.bmp", 50, 450, Direction::VERTICAL);
        enemyBike[1] = new EnemyMotorbike(320, 150, ENEMY_RADIUS, L"enemyRight.bmp", L"enemyLeft.bmp", 50, 300, Direction::VERTICAL);
        enemyBike[2] = new EnemyMotorbike(200, 550, ENEMY_RADIUS, L"enemyRight.bmp", L"enemyLeft.bmp", 150, 450, Direction::HORIZONTAL);
        enemyBike[3] = new EnemyMotorbike(400, 400, ENEMY_RADIUS, L"enemyRight.bmp", L"enemyLeft.bmp", 350, 550, Direction::HORIZONTAL);

        buildings[0] = new Building({ 179, 256, 232, 272 }, L"��������");
        buildings[1] = new Building({ 446, 164, 494, 182 }, L"�°�����");
        buildings[2] = new Building({ 575, 149, 623, 167 }, L"ä������");
        buildings[3] = new Building({ 427, 332, 478, 342 }, L"�����Դ�");
        buildings[4] = new Building({ 305, 503, 355, 512 }, L"�������");
        buildings[5] = new Building({ 572, 497, 621, 508 }, L"��� �п�");

        backgroundImage = new Bitmap(L"stage1.bmp");
        if (backgroundImage->GetLastStatus() != Gdiplus::Ok) {
            MessageBox(hWnd, L"Failed to load image", L"Error", MB_OK);
            delete backgroundImage;
            backgroundImage = nullptr;
        }

        // ������ ��Ҹ� �׸��� ���� DC�� ��Ʈ�� ����
        hdc = GetDC(hWnd);
        hdcStatic = CreateCompatibleDC(hdc);
        hbmStatic = CreateCompatibleBitmap(hdc, 800, 600);
        SelectObject(hdcStatic, hbmStatic);
        ReleaseDC(hWnd, hdc);

        // ������ ��� �׸���
        staticGraphics.FillRectangle(&backgroundBrush, 0, 0, 800, 600);
        DrawWalls(staticGraphics);
        DrawBuildings(staticGraphics);
        if (backgroundImage) {
            staticGraphics.DrawImage(backgroundImage, 0, 0, 800, 600);
        }
        return 0;
    case WM_COMMAND:
        switch (LOWORD(wParam)) { // ��ư ��Ʈ��
        case GAMESTART: // ���� ���� ��ư Ŭ�� ��
            gameState = ORDER; // �ֹ� �ޱ� ȭ�� ���
            ShowWindow(GetDlgItem(hWnd, GAMESTART), SW_HIDE); // ���� ���� ��ư �����
            ShowWindow(GetDlgItem(hWnd, HOWTOPLAY), SW_HIDE); // ���� ���� ��ư �����
            ShowWindow(GetDlgItem(hWnd, BACK), SW_HIDE); // ���ư��� ��ư �����
            if (gameState == ORDER) {
                while (ui.GetList().size() != 1 + ui.GetDay() * 2) {
                    ui.GetOrder();
                }
                gameState = MAKE;
            }
            InvalidateRect(hWnd, NULL, TRUE); // ������ ȭ�� ����
            break;
        case HOWTOPLAY: // ���� ���� ��ư Ŭ�� ��
            gameState = EXPLAIN; // ���� ���� ȭ�� ���
            ShowWindow(GetDlgItem(hWnd, GAMESTART), SW_HIDE); // ���� ���� ��ư �����
            ShowWindow(GetDlgItem(hWnd, HOWTOPLAY), SW_HIDE); // ���� ���� ��ư �����
            InvalidateRect(hWnd, NULL, TRUE); // ������ ȭ�� ����
            break;
        case BACK:
            gameState = START;
            ShowWindow(GetDlgItem(hWnd, BACK), SW_HIDE); // ���ư��� ��ư �����
            InvalidateRect(hWnd, NULL, TRUE); // ������ ȭ�� ����
            break;
        case DOUGH: // ���� ���� & ���� ���� ����
            if (ui.GetDough() == false) {
                ui.SetDough(true);
                if (pizza) {
                    delete pizza;
                }
                pizza = new Pizza();
                setting[DOUGH] = 1;
                pizza->ResetPizza(setting);
            }
            InvalidateRect(hWnd, NULL, TRUE); // ������ ȭ�� ����
            break;
        case SAUCE:
            if (ui.GetDough()) {
                setting[SAUCE] = 1;
                if (pizza) pizza->ResetPizza(setting);
                InvalidateRect(hWnd, NULL, TRUE); // ������ ȭ�� ����
            }
            break;
        case CHEESE:
            if (ui.GetDough()) {
                setting[CHEESE] = 1;
                if (pizza) pizza->ResetPizza(setting);
                InvalidateRect(hWnd, NULL, TRUE); // ������ ȭ�� ����
            }
            break;
        case PEPPERONI:
            if (ui.GetDough()) {
                setting[PEPPERONI]++;
                if (pizza) pizza->ResetPizza(setting);
                InvalidateRect(hWnd, NULL, TRUE); // ������ ȭ�� ����
            }
            break;
        case TOMATO:
            if (ui.GetDough()) {
                setting[TOMATO]++;
                if (pizza) pizza->ResetPizza(setting);
                InvalidateRect(hWnd, NULL, TRUE); // ������ ȭ�� ����
            }
            break;
        case PAPRIKA:
            if (ui.GetDough()) {
                setting[PAPRIKA]++;
                if (pizza) pizza->ResetPizza(setting);
                InvalidateRect(hWnd, NULL, TRUE); // ������ ȭ�� ����
            }
            break;
        case PEPPER:
            if (ui.GetDough()) {
                setting[PEPPER]++;
                if (pizza) pizza->ResetPizza(setting);
                InvalidateRect(hWnd, NULL, TRUE); // ������ ȭ�� ����
            }
            break;
        case ONION:
            if (ui.GetDough()) {
                setting[ONION]++;
                if (pizza) pizza->ResetPizza(setting);
                InvalidateRect(hWnd, NULL, TRUE); // ������ ȭ�� ����
            }
            break;
        case OLIVE:
            if (ui.GetDough()) {
                setting[OLIVE]++;
                if (pizza) pizza->ResetPizza(setting);
                InvalidateRect(hWnd, NULL, TRUE); // ������ ȭ�� ����
            }
            break;
        case SHRIMP:
            if (ui.GetDough()) {
                setting[SHRIMP]++;
                if (pizza) pizza->ResetPizza(setting);
                InvalidateRect(hWnd, NULL, TRUE); // ������ ȭ�� ����
            }
            break;
        case MUSHROOM:
            if (ui.GetDough()) {
                setting[MUSHROOM]++;
                if (pizza) pizza->ResetPizza(setting);
                InvalidateRect(hWnd, NULL, TRUE); // ������ ȭ�� ����
            }
            break;
        case DISPOSAL: // ���̽� & ���� ����
            if (ui.GetDough() == true) {
                ui.SetDough(false);
                delete pizza;
                pizza = nullptr;

                for (int index = 0; index < 11; index++) {
                    setting[index] = 0;
                }
            }
            InvalidateRect(hWnd, NULL, TRUE); // ������ ȭ�� ����
            break;
        case COOK: // ���� ���� Ȯ��
            if (ui.GetDough() == true) {
                ui.SetDough(false);
                ui.InputBox(pizza);

                for (int index = 0; index < 11; index++) {
                    setting[index] = 0;
                }

                // (������ ���� ����) == (�ֹ� ���� ���� ����) ��ġ �� ��޷� �Ѿ��
                if (ui.GetBoxSize() == ui.GetList().size()) {
                    gameState = DELIVERY;
                }
                delete pizza;
                pizza = nullptr;
            }
            InvalidateRect(hWnd, NULL, TRUE); // ������ ȭ�� ����
            break;
        }
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        if (gameState == START) {
            ShowWindow(GetDlgItem(hWnd, GAMESTART), SW_SHOW);
            ShowWindow(GetDlgItem(hWnd, HOWTOPLAY), SW_SHOW);

            // ���� ȭ���� ���� �̹��� �׸���
            RECT rect;
            GetClientRect(hWnd, &rect);
            int width = rect.right - rect.left;
            int height = rect.bottom - rect.top;
            DrawBackFromFile(hdc, L"StartScreen.png", 0, 0, width, height);

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
            ShowWindow(GetDlgItem(hWnd, PAPRIKA), SW_SHOW);
            ShowWindow(GetDlgItem(hWnd, DISPOSAL), SW_SHOW);
            ShowWindow(GetDlgItem(hWnd, COOK), SW_SHOW);
        }
        else if (gameState == DELIVERY) {
            ui.PrintList(hdc);
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
            ShowWindow(GetDlgItem(hWnd, PAPRIKA), SW_HIDE);
            ShowWindow(GetDlgItem(hWnd, DISPOSAL), SW_HIDE);
            ShowWindow(GetDlgItem(hWnd, COOK), SW_HIDE);

            // ���� ���۸��� ���� �޸� DC�� ��Ʈ�� ����
            hdcMem = CreateCompatibleDC(hdc);
            hbmMem = CreateCompatibleBitmap(hdc, 800, 600);
            hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);

            // ������ ��Ҹ� �޸� DC�� ����
            BitBlt(hdcMem, 0, 0, SCREEN_X, SCREEN_Y, hdcStatic, 0, 0, SRCCOPY);

            // �����̴� ��� �׸���
            Graphics graphics(hdcMem);
            playerBike->Draw(graphics);
            for (int i = 0; i < 4; ++i) {
                enemyBike[i]->Draw(graphics);
            }

            // �޸� DC�� ������ ȭ�� DC�� ����
            BitBlt(hdc, 0, 0, SCREEN_X, SCREEN_Y, hdcMem, 0, 0, SRCCOPY);

            // �޸� DC�� ��Ʈ�� ����
            SelectObject(hdcMem, hbmOld);
            DeleteObject(hbmMem);
            DeleteDC(hdcMem);
        }

        // �̹����� �׸��� �ڵ�
        if (ui.GetDough()) {
            DrawImageFromFile(hdc, L"����.png", (SCREEN_X - IMAGE_WIDTH) / 2, (SCREEN_Y - IMAGE_HEIGHT) / 2, IMAGE_WIDTH, IMAGE_HEIGHT);
        }
        if (setting[SAUCE] == 1) {
            DrawImageFromFile(hdc, L"����ҽ�.png", (SCREEN_X - IMAGE_WIDTH) / 2, (SCREEN_Y - IMAGE_HEIGHT) / 2, IMAGE_WIDTH, IMAGE_HEIGHT);
        }
        if (setting[CHEESE] == 1) {
            DrawImageFromFile(hdc, L"ġ��.png", (SCREEN_X - 30 - IMAGE_WIDTH) / 2, (SCREEN_Y - 30 - IMAGE_HEIGHT) / 2, IMAGE_WIDTH + 40, IMAGE_HEIGHT + 30);
        }
        if (setting[PEPPERONI] > 0) {
            DrawImageFromFile(hdc, L"���۷δ�.png", (SCREEN_X + 80 - IMAGE_WIDTH) / 2, (SCREEN_Y + 40 - IMAGE_HEIGHT) / 2, IMAGE_WIDTH - 20, IMAGE_HEIGHT + 30);
        }
        if (setting[TOMATO] > 0) {
            DrawImageFromFile(hdc, L"�丶��.png", (SCREEN_X + 80 - IMAGE_WIDTH) / 2, (SCREEN_Y + 40 - IMAGE_HEIGHT) / 2, IMAGE_WIDTH - 20, IMAGE_HEIGHT + 30);
        }
        if (setting[PAPRIKA] > 0) {
            DrawImageFromFile(hdc, L"������ī.png", (SCREEN_X + 80 - IMAGE_WIDTH) / 2, (SCREEN_Y + 40 - IMAGE_HEIGHT) / 2, IMAGE_WIDTH - 20, IMAGE_HEIGHT + 30);
        }
        if (setting[PEPPER] > 0) {
            DrawImageFromFile(hdc, L"�Ǹ�.png", (SCREEN_X + 80 - IMAGE_WIDTH) / 2, (SCREEN_Y + 40 - IMAGE_HEIGHT) / 2, IMAGE_WIDTH - 20, IMAGE_HEIGHT + 30);
        }
        if (setting[ONION] > 0) {
            DrawImageFromFile(hdc, L"����.png", (SCREEN_X + 80 - IMAGE_WIDTH) / 2, (SCREEN_Y + 40 - IMAGE_HEIGHT) / 2, IMAGE_WIDTH - 20, IMAGE_HEIGHT + 30);
        }
        if (setting[OLIVE] > 0) {
            DrawImageFromFile(hdc, L"�ø���.png", (SCREEN_X + 80 - IMAGE_WIDTH) / 2, (SCREEN_Y + 40 - IMAGE_HEIGHT) / 2, IMAGE_WIDTH - 20, IMAGE_HEIGHT + 30);
        }
        if (setting[SHRIMP] > 0) {
            DrawImageFromFile(hdc, L"����.png", (SCREEN_X + 80 - IMAGE_WIDTH) / 2, (SCREEN_Y + 40 - IMAGE_HEIGHT) / 2, IMAGE_WIDTH - 20, IMAGE_HEIGHT + 30);
        }
        if (setting[MUSHROOM] > 0) {
            DrawImageFromFile(hdc, L"����.png", (SCREEN_X + 80 - IMAGE_WIDTH) / 2, (SCREEN_Y + 40 - IMAGE_HEIGHT) / 2, IMAGE_WIDTH - 20, IMAGE_HEIGHT + 30);
        }

        

        EndPaint(hWnd, &ps);
        return 0;
    case WM_TIMER:
        if (wParam == ID_TIMER_MOVE && gameState == DELIVERY) {
            if (!g_controlLocked) {
                int targetX = playerBike->x;
                int targetY = playerBike->y;

                if (g_leftPressed && !g_rightPressed)
                    targetX -= 5;
                if (g_rightPressed && !g_leftPressed)
                    targetX += 5;
                if (g_upPressed && !g_downPressed)
                    targetY -= 5;
                if (g_downPressed && !g_upPressed)
                    targetY += 5;

                bool collision = false;
                for (int i = 0; i < wallCount; ++i) {
                    RECT rect = walls[i].rect;
                    if (targetX + BALL_RADIUS > rect.left && targetX - BALL_RADIUS < rect.right &&
                        targetY + BALL_RADIUS > rect.top && targetY - BALL_RADIUS < rect.bottom) {
                        collision = true;
                        break;
                    }
                }

                if (!collision) {
                    prevX = playerBike->x;
                    prevY = playerBike->y;
                    playerBike->x = targetX;
                    playerBike->y = targetY;

                    // ������ �浹 �˻� �� ó��
                    int collidedItemIndex = CheckCollisionWithBuildings(playerBike->x, playerBike->y, BALL_RADIUS);
                    if (collidedItemIndex != -1) {
                        buildings[collidedItemIndex]->visible = false; // ������ ����

                        MessageBox(hWnd, buildings[collidedItemIndex]->message.c_str(), L"���", MB_OK | MB_ICONINFORMATION);

                        // ��� �������� �� �Ծ����� Ȯ��
                        bool allItemsCollected = true;
                        for (int i = 0; i < buildingCount; ++i) {
                            if (buildings[i]->visible) {
                                allItemsCollected = false;
                                break;
                            }
                        }

                        if (allItemsCollected) {
                            PostQuitMessage(0); // ���α׷� ����
                        }
                    }

                    // �� ������� �浹 �˻�
                    if (CheckCollisionWithEnemy(playerBike->x, playerBike->y, BALL_RADIUS)) {
                        g_controlLocked = true;
                        g_leftPressed = false;
                        g_rightPressed = false;
                        g_upPressed = false;
                        g_downPressed = false;
                        SetTimer(hWnd, ID_TIMER_CONTROL_LOCK, 2000, NULL);
                    }
                }

                RECT updateRect = { min(prevX, playerBike->x) - BALL_RADIUS, min(prevY, playerBike->y) - BALL_RADIUS, max(prevX, playerBike->x) + BALL_RADIUS, max(prevY, playerBike->y) + BALL_RADIUS };
                InvalidateRect(hWnd, &updateRect, TRUE);
            }

            // �� ������� �̵� ����
            for (int i = 0; i < 4; ++i) {
                enemyBike[i]->Move();
                RECT enemyUpdateRect = { enemyBike[i]->x - ENEMY_RADIUS, enemyBike[i]->y - ENEMY_RADIUS, enemyBike[i]->x + ENEMY_RADIUS, enemyBike[i]->y + ENEMY_RADIUS };
                InvalidateRect(hWnd, &enemyUpdateRect, TRUE);
            }
        }
        else if (wParam == ID_TIMER_CONTROL_LOCK) {
            g_controlLocked = false;
            KillTimer(hWnd, ID_TIMER_CONTROL_LOCK);
        }
        break;

    case WM_KEYDOWN:
        if (!g_controlLocked) {
            switch (wParam) {
            case VK_LEFT:
                g_leftPressed = true;
                break;
            case VK_RIGHT:
                g_rightPressed = true;
                break;
            case VK_UP:
                g_upPressed = true;
                break;
            case VK_DOWN:
                g_downPressed = true;
                break;
            }

            // �̵� Ű�� ���� ��쿡�� Ÿ�̸� ����
            if (!timerSet) {
                SetTimer(hWnd, ID_TIMER_MOVE, 50, NULL);
                timerSet = true;
            }

            RECT updateRect = { playerBike->x - BALL_RADIUS, playerBike->y - BALL_RADIUS, playerBike->x + BALL_RADIUS, playerBike->y + BALL_RADIUS };
            InvalidateRect(hWnd, &updateRect, TRUE);
        }
        break;

    case WM_KEYUP:
        if (!g_controlLocked) {
            switch (wParam) {
            case VK_LEFT:
                g_leftPressed = false;
                break;
            case VK_RIGHT:
                g_rightPressed = false;
                break;
            case VK_UP:
                g_upPressed = false;
                break;
            case VK_DOWN:
                g_downPressed = false;
                break;
            }
        }
        break;
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