#pragma once
#include "Bonus.h"
class Astrazeneca : public Bonus
{
public:
	Astrazeneca();
	Astrazeneca(float l, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	virtual ~Astrazeneca();
	void dibuja();
};

