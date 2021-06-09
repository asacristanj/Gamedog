#pragma once
#include "Vector2D.h"

class ObjetoMovil
{
protected:
	Vector2D posicion, velocidad, aceleracion;
	int puntuacion=0;
public:
    void mueve(float t);
	void setPos(float ix, float iy);
	void setVel(float vx, float vy); // Si llamas setVel().x / setVel().y
	void setVelx(float vx); // ESTO NO HACE FALTA POR LO DE ARRIBA
	void setVely(float vy); // NI ESTO
	void setPunt(int punt);
	Vector2D getPos() { return posicion; }
	Vector2D getVel() { return velocidad; }
	float getVelx() { return velocidad.x; } // ESTO TAMPOCO HACE FALTA
	float getVely() { return velocidad.y; } // NI ESTO
	int getPunt() { return puntuacion; }
};

