#pragma once
#include "Enemigo.h"
class MurcielagoBoss: public Enemigo
{
public:
	MurcielagoBoss();
	void volar();
	MurcielagoBoss(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void dibuja();
	void disparoChina(Vector2D posJugador); // recibe la posicion del jugador y dispara una cepa china hacia este
};

