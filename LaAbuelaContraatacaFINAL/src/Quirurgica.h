#pragma once
#include "Bonus.h"
class Quirurgica :    public Bonus
{
public:
	Quirurgica();
	Quirurgica(float l, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	virtual ~Quirurgica();
	void dibuja();
	friend class Interaccion;
};

