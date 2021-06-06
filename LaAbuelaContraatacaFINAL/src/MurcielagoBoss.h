#pragma once
#include "Enemigo.h"
class MurcielagoBoss: public Enemigo
{
public:
	MurcielagoBoss();
	void volar();
	void disparoChina(Vector2D posJugador); // recibe la posicion del jugador y dispara una cepa china hacia este
};

