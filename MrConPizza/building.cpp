#include "building.h"

Building::Building(RECT rect, const wstring& message)
    : rect(rect), visible(true), message(message), collisionDisabled(false), timerID(0) {}

void Building::Draw(Graphics& graphics) {
    if (visible) {
        SolidBrush brush(Color(255, 255, 255, 0));
        Rect drawRect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
        graphics.FillEllipse(&brush, drawRect);
    }
}

bool Building::CheckCollision(int x, int y, int radius) {
    if (visible && !collisionDisabled) {
        int buildingCenterX = (rect.left + rect.right) / 2;
        int buildingCenterY = (rect.top + rect.bottom) / 2;
        int distanceSqaured = pow((x - buildingCenterX), 2) + pow((y - buildingCenterY), 2);
        int radiusSqaured = pow(radius, 2);

        return distanceSqaured <= radiusSqaured;
    }
    return false;
}

void Building::DisableCollisionForDuration(HWND hWnd, int duration) {
    collisionDisabled = true;
    visible = false;
    timerID = SetTimer(hWnd, reinterpret_cast<UINT_PTR>(this), duration, NULL);
}

void Building::EnableCollision() {
    if (timerID >= 10000) {
        collisionDisabled = false;
        visible = true;
        KillTimer(NULL, timerID);
    }
}
