#pragma once
#include "Vector2D.h"
#include "ObjetoMovil.h"
class Jugador: public ObjetoMovil
{
private:
	float altura;
	float acel_inicial = -30.0f;
	float impulso = 10.0f; //impulso vertical inicial del salto

public:
	Jugador();
	virtual ~Jugador();
	void dibuja();
	void salto(float imp);
	void movLateral(float ix);
	void morir();
	float getAltura() { return altura; }

	friend class Interaccion;
};

