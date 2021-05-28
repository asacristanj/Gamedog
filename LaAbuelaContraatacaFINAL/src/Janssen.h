#pragma once
#include "Bonus.h"
class Janssen :    public Bonus
{
public:
	Janssen();
	Janssen(float l, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	virtual ~Janssen();
	void dibuja();
};

