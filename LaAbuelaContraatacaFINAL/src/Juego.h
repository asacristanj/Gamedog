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

#include "Escalera.h"
#include "Llave.h"
#include "ListaLlaves.h"
#include <iostream>
#include <fstream> // ficheros
#include <string>
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
	int llaveJug = jugador.getNumLlaves();//llaves que tiene el jugador, a las 3 pasa el nivel
	int vidas=1; // veces que se puede reintentar el nivel tras morir
	int nivel;//variable que encaja el nivel
	int record_puntuacion; // record de puntuacion general
	int puntuacion_jugador = jugador.getPuntuacion();
	bool record_superado;
public:
	virtual ~Juego();
	void tecla(unsigned char key);
	void inicializa();
	void moverOjo();
	void mueve();
	void dibuja();
	bool cargarNivel();
	void teclaEspecial(unsigned char key);
	void teclaEspecialUp(unsigned char key);
	// sets
	void setChances(int chance) { chances = chance; }
	void setVidas(int vida) { vidas += vida; }
	void setllaveJug(int llave) { llaveJug = llave; }
	void setRecord(int r) { record_puntuacion = r; }
	void setRecordFile(int r);
	void setPuntuacionJugador(int p) { puntuacion_jugador = p; }
	void setRecordSuperado(bool r) { record_superado = r; }
	// gets
	int getLlaves() { return llaveJug; }
	int getChances() { return chances; }
	int getVidas() { return vidas; }
	bool getImpacto() {	return impacto;}//funcion que lee el impacto
	int getRecord() { return record_puntuacion; }
	int getRecordFile();
	int getPuntuacionJugador() { return puntuacion_jugador; }
	bool getRecordSuperado() { return record_superado; }
};