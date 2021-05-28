#pragma once
#include "Jugador.h"
#include "Enemigo.h"
#include "DisparoGel.h"
#include "Escenario.h"
#include "Plataforma.h"
#include "CepaBritanica.h"
#include "CepaIndia.h"
#include "CepaChina.h"
#include "CepaBrasileņa.h"
#include "Bonus.h"
#include "ListaDisparosGel.h"
#include "ListaEnemigos.h"
class Interaccion
{
public:
	static void rebote(Jugador& j, Escenario e);
	static bool colisionEncima(Jugador j, Plataforma p); //Capta la colision del jugador y la plataforma por debajo de la plataforma
	static bool colisionDebajo(Jugador j, Plataforma p); //Capta la colision del jugador y la plataforma por encima de la plataforma
	static bool colisionLadoIzq(Jugador j, Plataforma p);
	static bool colisionLadoDer(Jugador j, Plataforma p);
	static bool colisionSuelo(Jugador j, Escenario e);
	static void rebote(Jugador& j, Plataforma p);
	static void rebote(Bonus& b, Plataforma p);
	static void rebote(Bonus& b, Escenario e);
	static void rebote(CepaBritanica& brit, Plataforma p);
	static void rebote(CepaIndia& ind, Plataforma p);
	static void rebote(CepaBrasileņa& bra, Plataforma p);
	static bool rebote(Enemigo enem, Plataforma p);
	static void rebote(CepaBritanica& brit, Escenario e);
	static void rebote(CepaIndia& ind, Escenario e);
	static bool rebote(Enemigo enem, Escenario e);
	static bool colision(Enemigo enem, Jugador j);
	static bool colisionEncima(Enemigo enem, Jugador j);
	static bool colision(DisparoGel d, Plataforma p);
	static bool colision(DisparoGel d, Escenario e);
	static bool colision(DisparoGel d, Enemigo enem);
	static bool colision(Bonus b, Plataforma p);
	static bool colision(Bonus b, Escenario e);
	static bool colision(Bonus b, Jugador j);
	static bool ratio(CepaBritanica brit, Jugador j);
	static bool ratioExplosion(CepaBritanica brit, Jugador j);
};


