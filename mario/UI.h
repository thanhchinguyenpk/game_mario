#pragma once
#include "TextAndNumber.h"
class UI
{

	float posX=100, posY=100;
	
	TextAndNumber text;
public:

	UI() {};
	~UI() {};

	void Update();
	void Render(int remainingTim);
};

