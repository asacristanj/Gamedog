#pragma once
#include "Vector2D.h"

class ObjetoMovil
{
protected:
	Vector2D posicion, velocidad, aceleracion;
public:
    void mueve(float t);
	void setPos(float ix, float iy);
	void setVel(float vx, float vy);
	void setVelx(float vx);
	void setVely(float vy);
	Vector2D getPos() { return posicion; }
	Vector2D getVel() { return velocidad; }
	float getVelx() { return velocidad.x; }
	float getVely() { return velocidad.y; }
};

