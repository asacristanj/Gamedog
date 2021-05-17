#pragma once
#include "Escenario.h"
#include "Jugador.h"  
#include "Bonus.h" 
#include "DisparoGel.h" 
#include "Interaccion.h"
#include "Enemigo.h"
#include "ListaEnemigos.h"
#include "ListaDisparosGel.h"
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

public:
	virtual ~Juego();
	void tecla(unsigned char key);
	void inicializa();
	void moverOjo();
	void mueve();
	void dibuja();
	void teclaEspecial(unsigned char key);
};


