#pragma once
#include "Enemigo.h"
class MurcielagoPeque�o: public Enemigo
{
public:
	MurcielagoPeque�o();
	MurcielagoPeque�o(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void dibuja();
	void disparoChina(Vector2D posJugador);
};

