#pragma once
#include "motorbike.h"

enum class Direction { HORIZONTAL, VERTICAL };

class EnemyMotorbike : public Motorbike {
public:
	int direction;
	int minPos, maxPos;
	Direction moveDirection;
	wstring rightImagePath;
	wstring leftImagePath;

	EnemyMotorbike(int startX, int startY, int radius, const wstring& rightImage, const wstring& leftImage, int minRange, int maxRange, Direction dir);
	void ChangeImage(const wstring& imagePath);
	void Move() override;
};