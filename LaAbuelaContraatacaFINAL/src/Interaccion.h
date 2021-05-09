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
	static bool colisionEncima(Jugador j, Plataforma p);
	static bool colisionDebajo(Jugador j, Plataforma p);
	static void rebote(Jugador& j, Plataforma p);
	static void rebote(Enemigo& enem, Plataforma p);
	static bool colision(Enemigo enem, Jugador j);
	static bool colision(DisparoGel d, Plataforma p);
	static bool colision(DisparoGel d, Escenario e);
	static bool colision(DisparoGel d, Enemigo e);
};


