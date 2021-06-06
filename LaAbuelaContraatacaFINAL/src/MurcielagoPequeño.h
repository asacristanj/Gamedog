#pragma once
#include "Enemigo.h"
class MurcielagoPequeño: public Enemigo
{
public:
	MurcielagoPequeño();
	MurcielagoPequeño(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void dibuja();
	void disparoChina(Vector2D posJugador);
};

