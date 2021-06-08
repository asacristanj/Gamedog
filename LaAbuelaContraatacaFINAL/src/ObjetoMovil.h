#pragma once
#include "Vector2D.h"

class ObjetoMovil
{
protected:
	Vector2D posicion, velocidad, aceleracion;
	static int puntuacion;
public:
    void mueve(float t);
	void setPos(float ix, float iy);
	void setVel(float vx, float vy);
	void setVelx(float vx);
	void setVely(float vy);
	void setPunt(int punt);
	Vector2D getPos() { return posicion; }
	Vector2D getVel() { return velocidad; }
	float getVelx() { return velocidad.x; }
	float getVely() { return velocidad.y; }
	int getPunt() { return puntuacion; }
};

