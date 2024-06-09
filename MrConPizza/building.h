#pragma once
#include <iostream>
#include <windows.h>
#include <gdiplus.h>
#include <cmath>

#pragma comment(lib, "Gdiplus.lib")

using namespace std;
using namespace Gdiplus;

class Building {
public:
	RECT rect;
	bool visible;
	wstring message;

	Building(RECT rect, const wstring& message);
	void Draw(Graphics& graphics);
	bool CheckCollision(int x, int y, int radius);
};