#ifndef BUILDING_H
#define BUILDING_H

#include <windows.h>
#include <gdiplus.h>
#include <string>

using namespace Gdiplus;
using namespace std;

class Building {
public:
    RECT rect;
    wstring message;
    bool visible;
    bool collisionDisabled;
    UINT_PTR timerID;

    Building(RECT rect, const wstring& message);
    void Draw(Graphics& graphics);
    bool CheckCollision(int x, int y, int radius);
    void DisableCollisionForDuration(HWND hWnd, int duration);
    void EnableCollision();
};

#endif // BUILDING_H