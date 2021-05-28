#pragma once
#include "Bonus.h"
class Pfizer :    public Bonus
{
public:
	Pfizer();
	Pfizer(float l, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	virtual ~Pfizer();
	void dibuja();
};

