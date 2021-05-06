#pragma once
#include "Vector2D.h"
class Jugador
{
private:
	float altura;
	Vector2D posicion;
	Vector2D velocidad;
	Vector2D aceleracion;

public:
	Jugador();
	virtual ~Jugador();
	void dibuja();
	void mueve(float t);
	void setVel(float vx, float vy);

	friend class Interaccion;
};

