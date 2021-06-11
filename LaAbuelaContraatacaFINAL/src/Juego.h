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
#include"ListaEscaleras.h"
#include "ListaPlataformas.h"
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
#include "Llave.h"
#include "ListaLlaves.h"
class Juego
{
private:
	float x_ojo;
	float y_ojo;
	float z_ojo;
	DisparoGel disparogel;
	Jugador jugador;
	Escenario escenario;
	ListaEnemigos enemigos;
	ListaDisparosGel disparos;
	ListaBonus bonuses;
	CepaBritanica brit;
	ListaBloques bloques;
	ListaPlataformas plataformas;
	ListaEscaleras escaleras;
	ListaLlaves llaves;
	bool impacto;//variable que es true si enemigo choca con jugador
	bool bajarescaleras,subirescaleras,primeravez;
	int chances=jugador.getNumBonus(); // veces que se puede recibir daño sin llegar a morir
	int vidas=1; // veces que se puede reintentar el nivel tras morir
	int nivel;//variable que encaja el nivel
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
	bool cargarNivel();
	bool getImpacto() {	return impacto;}//funcion que lee el impacto
};