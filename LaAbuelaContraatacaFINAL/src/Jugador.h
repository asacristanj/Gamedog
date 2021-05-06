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
	void setVel(float vx, float vy);
	void salto();
	void movLateral(float ix);

	friend class Interaccion;
	friend class Juego;
};

