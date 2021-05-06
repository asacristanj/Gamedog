#pragma once
#include "Jugador.h"
#include "Enemigo.h"
#include "DisparoGel.h"
#include "Escenario.h"
#include "Plataforma.h"
class Interaccion
{
public:
	static void rebote(Jugador& j, Escenario e);
	static void rebote(Enemigo& enem, Escenario e);
	static bool colision(Enemigo enem, Jugador j);
	static bool colision(DisparoGel d, Plataforma p);
	static bool colision(DisparoGel d, Escenario e);
};


