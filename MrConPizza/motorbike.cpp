#include "motorbike.h"

Motorbike::Motorbike(int startX, int startY, int radius, const wstring& imagePath)
	: x(startX), y(startY), radius(radius) {
	image = new Bitmap(imagePath.c_str());
	if (image->GetLastStatus() != Ok) {
		MessageBox(NULL, L"Failed to load image", L"Error", MB_OK);
		delete image;
		image = nullptr;
	}
}

Motorbike::~Motorbike() {
	if (image) {
		delete image;
	}
}

void Motorbike::Draw(Graphics& graphics) {
	if (image) {
		graphics.DrawImage(image, x - radius, y - radius, 2 * radius, 2 * radius);
	}
}