#pragma once
#include "Vector2D.h"
class Jugador
{
private:
	float altura;
	float impulso = 10.0f; //impulso vertical inicial del salto
	Vector2D posicion;
	Vector2D velocidad;
	Vector2D aceleracion;

public:
	Jugador();
	virtual ~Jugador();
	void dibuja();
	void mueve(float t);
	void setPos(float ix, float iy);
	void setVel(float vx, float vy);
	void setAcel(float ax);
	void salto(float imp);
	Vector2D getPos() { return posicion; }
	float getAltura() { return altura; }

	friend class Interaccion;
};

