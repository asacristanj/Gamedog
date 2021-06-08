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
#include "Factoria.h"
#include "BloqueSorpresa.h"
#include "CepaBritanica.h"
#include "CepaIndia.h"
#include "Astrazeneca.h"
#include "Janssen.h"
#include "MascarillaTocha.h"
#include "Pfizer.h"
#include "Quirurgica.h"
#include "Sputnik.h"
#include "Escalera.h"
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
	Escalera escalera;
	bool impacto;//variable que es true si enemigo choca con jugador
	int chances=jugador.GetNumBonus(); // veces que se puede recibir daño sin llegar a morir
	int vidas=1; // veces que se puede reintentar el nivel tras morir
public:
	virtual ~Juego();
	void tecla(unsigned char key);
	void inicializa();
	void moverOjo();
	void mueve();
	void dibuja();
	void teclaEspecial(unsigned char key);
	void teclaEspecialUp(unsigned char key);
	void setChances(int chance) { chances = chance; }
	void setVidas(int vida) { vidas += vida; }
	int getChances() { return chances; }
	int getVidas() { return vidas; }
	bool getImpacto() {	return impacto;}//funcion que lee el impacto
};