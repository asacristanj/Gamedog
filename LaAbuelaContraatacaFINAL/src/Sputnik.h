#pragma once
#include "Bonus.h"
class Sputnik :    public Bonus
{
public:
	Sputnik();
	Sputnik(float l, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	virtual ~Sputnik();
	void dibuja();
};

