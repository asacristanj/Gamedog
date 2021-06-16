#pragma once
#include "Vector2D.h"
#include "freeglut.h"

class ObjetoMovil
{
protected:
	Vector2D posicion, velocidad, aceleracion;
public:
	virtual void dibuja()=0;
    virtual void mueve(float t);
	// sets
	void setPos(float ix, float iy);
	void setVel(float vx, float vy); // Si llamas setVel().x / setVel().y
	void setAcel(float ax, float ay);
	void setVelx(float vx); // ESTO NO HACE FALTA POR LO DE ARRIBA
	void setVely(float vy); // NI ESTO
	// gets
	Vector2D getPos() { return posicion; }
	Vector2D getVel() { return velocidad; }
	Vector2D getAcel() { return aceleracion; }
	float getVelx() { return velocidad.x; } // ESTO TAMPOCO HACE FALTA
	float getVely() { return velocidad.y; } // NI ESTO
};

