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
	static bool colisionEncima(Jugador j, Plataforma p); //Capta la colision del jugador y la plataforma por debajo de la plataforma
	static bool colisionDebajo(Jugador j, Plataforma p); //Capta la colision del jugador y la plataforma por encima de la plataforma
	static bool colisionSuelo(Jugador j, Escenario e);
	static void rebote(Jugador& j, Plataforma p);
	static void rebote(Enemigo& enem, Plataforma p);
	static void rebote(Enemigo& enem, Escenario e);
	static bool colision(Enemigo enem, Jugador j);
	static bool colision(DisparoGel d, Plataforma p);
	static bool colision(DisparoGel d, Escenario e);
	static bool colision(DisparoGel d, Enemigo enem);
};


