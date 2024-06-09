#pragma once
#include <iostream>
#include <windows.h>
#include <gdiplus.h>

#pragma comment(lib, "Gdiplus.lib")

using namespace std;
using namespace Gdiplus;

class Motorbike {
public:
	int x, y;
	int radius;
	Image* image;

	Motorbike(int startX, int startY, int radius, const wstring& imagePath);
	virtual ~Motorbike();
	virtual void Draw(Graphics& graphics);
	virtual void Move() = 0;
};