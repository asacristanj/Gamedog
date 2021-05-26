#pragma once
#include "DisparoGel.h"
#include "Jugador.h"
class Factoria
{
public:
	Factoria();
	virtual ~Factoria();

	static DisparoGel* CrearDisparo(Jugador j);
};

