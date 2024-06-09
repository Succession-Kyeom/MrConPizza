#pragma once
#include "motorbike.h"

class PlayerMotorbike : public Motorbike {
public:
	PlayerMotorbike(int startX, int startY, int radius, const wstring& imagePath);
	void Move() override;
};