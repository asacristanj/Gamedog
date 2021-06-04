#pragma once
#include "DisparoGel.h"
#include "Jugador.h"
#include "Bonus.h"
#include "Interaccion.h"
#include "Astrazeneca.h"
#include "Janssen.h"
#include "MascarillaTocha.h"
#include "Pfizer.h"
#include "Quirurgica.h"
#include "Sputnik.h"
class Factoria
{
public:
	Factoria();
	virtual ~Factoria();
	static DisparoGel* CrearDisparo(Jugador j);
	static void CogerQuirurgica(Jugador& j);
	static void CogerMascarillaTocha(Jugador j);
	static void CogerAstrazeneca(Jugador& j);
	//static void accionbonus(Jugador j, Bonus b);
	//void ModificarSalto(Jugador j, Bonus b);
};

