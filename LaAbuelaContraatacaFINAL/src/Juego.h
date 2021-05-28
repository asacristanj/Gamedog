#pragma once
#include "Escenario.h"
#include "Jugador.h"  
#include "Bonus.h" 
#include "DisparoGel.h" 
#include "Interaccion.h"
#include "Enemigo.h"
#include "ListaEnemigos.h"
#include "ListaDisparosGel.h"
#include "ListaBonus.h"
#include "ListaBloques.h"
#include "BloqueSorpresa.h"
#include "CepaBritanica.h"
#include "CepaIndia.h"
#include "Astrazeneca.h"
#include "Janssen.h"
#include "MascarillaTocha.h"
#include "Pfizer.h"
#include "Quirurgica.h"
#include "Sputnik.h"
class Juego
{
private:
	float x_ojo;
	float y_ojo;
	float z_ojo;
	DisparoGel disparogel;
	Jugador jugador;
	Escenario escenario;
	Bonus bonus;
	Plataforma plataforma;
	ListaEnemigos enemigos;
	ListaDisparosGel disparos;
	ListaBonus bonuses;
	CepaBritanica brit;
	ListaBloques bloques;
public:
	virtual ~Juego();
	void tecla(unsigned char key);
	void inicializa();
	void moverOjo();
	void mueve();
	void dibuja();
	void teclaEspecial(unsigned char key);
	void teclaEspecialUp(unsigned char key);
};


