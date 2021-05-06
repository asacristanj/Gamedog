#pragma once
#include "Vector2D.h"
class Bonus
{
private:
	float lado;
	Vector2D posicion;
	Vector2D velocidad;
	Vector2D aceleracion;

public:
	Bonus();
	virtual ~Bonus();
	void dibuja();
	void mueve(float t);
	void setPos(float ix, float iy);
};
