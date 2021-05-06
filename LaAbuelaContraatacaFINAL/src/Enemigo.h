#pragma once
#include "Vector2d.h"
class Enemigo
{
private:
	float altura;
	Vector2D posicion;
	Vector2D velocidad;
	Vector2D aceleracion;

public:
	Enemigo();
	virtual ~Enemigo();
	void dibuja();
	void mueve(float t);
	void setVel(float vx, float vy);

	friend class Interaccion;
};

