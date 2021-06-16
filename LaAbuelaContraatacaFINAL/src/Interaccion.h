#pragma once
#include "Jugador.h"
#include "BloqueSorpresa.h"
#include "Enemigo.h"
#include "DisparoGel.h"
#include "Escenario.h"
#include "Plataforma.h"
#include "CepaBritanica.h"
#include "CepaIndia.h"
#include "CepaChina.h"
#include "CepaBrasileña.h"
#include "MurcielagoBoss.h"
#include "MurcielagoPequeño.h"
#include "Bonus.h"
#include "Quirurgica.h"
#include "Astrazeneca.h"
#include "Janssen.h"
#include "Pfizer.h"
#include "MascarillaTocha.h"
#include "Escalera.h"
#include "Llave.h"
class Interaccion
{
public:
	//Jugador
	static bool colisionEncima(Jugador j, Plataforma p); //Capta la colision del jugador y la plataforma por debajo de la plataforma
	static bool colisionDebajo(Jugador j, Plataforma p); //Capta la colision del jugador y la plataforma por encima de la plataforma
	static bool colisionLateralDerecha(Jugador j, Plataforma p);
	static bool colisionLateralIzquierda(Jugador j, Plataforma p);
	static bool colisionSuelo(Jugador j, Escenario e);
	static void rebote(Jugador& j, Plataforma p);
	static void rebote(Jugador& j, Escenario e);
	static void rebote(Jugador& j, BloqueSorpresa b);
	static bool colisionDebajo(Jugador j, BloqueSorpresa b);
	static bool colisionEncima(Jugador j, BloqueSorpresa b);
	static bool colisionEscalerasubir(Escalera e, Jugador j);
	static bool colisionEscalerabajar(Escalera e, Jugador j);
	static bool colisionEscalera(Escalera e, Jugador j);
	//Bonus
	static bool colision(Bonus b, Plataforma p);
	static bool colision(Bonus& b, Escenario e);
	static bool colision(Bonus b, Jugador j);
	static void rebote(Bonus& b, Plataforma p);
	static void rebote(Bonus& b, Escenario e);
	//Enemigos
	static bool colision(Enemigo enem, Plataforma p);
	static bool colision(Enemigo enem, Escenario e);
	static bool colision(Enemigo enem, Jugador j);
	static bool colisionEncima(Enemigo enem, Jugador j);
	static bool ratio(CepaBritanica brit, Jugador j);
	static bool ratioExplosion(CepaBritanica brit, Jugador j);
	static void rebote(CepaBritanica& brit, Plataforma p);
	static void rebote(CepaIndia& ind, Plataforma p);
	static void rebote(CepaBrasileña& bra, Plataforma p);
	static void rebote(CepaBritanica& brit, Escenario e);
	static void rebote(CepaIndia& ind, Escenario e);
	static void rebote(CepaBrasileña& bra, Escenario e);
	static void rebote(MurcielagoPequeño& murpeq, Escenario e);
	static void rebote(MurcielagoBoss& murboss, Escenario e, Jugador j);
	static void rebote(Quirurgica& qui, Escenario e);
	//Disparos
	static bool colision(DisparoGel d, Plataforma p);
	static bool colision(DisparoGel d, Escenario e);
	static bool colision(DisparoGel d, Enemigo enem);
	//Llave
	static bool colision(Llave b, Plataforma p);
	static bool colision(Llave b, Jugador j);
};