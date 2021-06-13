#pragma once
#include "DisparoGel.h"
#include "Jugador.h"
#include "Bonus.h"
#include "ListaEnemigos.h"
#include "Interaccion.h"
#include "Astrazeneca.h"
#include "Janssen.h"
#include "MascarillaTocha.h"
#include "Pfizer.h"
#include "Quirurgica.h"

class Factoria
{
public:
	Factoria();
	virtual ~Factoria();
	static void CogerQuirurgica(Jugador& j);
	static void CogerMascarillaTocha(Jugador& j);
	static void CogerAstrazeneca(Jugador& j);
	static void CogerPfizer(Jugador& j);
	static void CogerJanssen(Jugador& j);
};

