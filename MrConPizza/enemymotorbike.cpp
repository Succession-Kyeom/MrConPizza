#include "enemymotorbike.h"

EnemyMotorbike::EnemyMotorbike(int startX, int startY, int radius, const wstring& rightImage, const wstring& leftImage, int minRange, int maxRange, Direction dir)
	:Motorbike(startX, startY, radius, rightImage), rightImagePath(rightImage), leftImagePath(leftImage), direction(1),
	minPos(minRange), maxPos(maxRange), moveDirection(dir) {
	ChangeImage(rightImagePath);
}

void EnemyMotorbike::ChangeImage(const wstring& imagePath) {
	if (image) {
		delete image;
	}
	image = new Bitmap(imagePath.c_str());
	if (image->GetLastStatus() != Ok) {
		MessageBox(NULL, L"Failed to load image", L"Error", MB_OK);
		delete image;
		image = nullptr;
	}
}

void EnemyMotorbike::Move() {
	if (moveDirection == Direction::VERTICAL) {
		y += direction * 2;
		if (y - radius < minPos || y + radius > maxPos) {
			direction *= -1;
			ChangeImage(direction == 1 ? rightImagePath : leftImagePath);
		}
	}
	else if (moveDirection == Direction::HORIZONTAL) {
		x += direction * 2;
		if (x - radius < minPos || x + radius > maxPos) {
			direction *= -1;
			ChangeImage((direction == 1) ? rightImagePath : leftImagePath);
		}
	}
}