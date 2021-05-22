#pragma once
#define MAX_ENEMIGOS 100
#include "Enemigo.h"
#include "Interaccion.h"
#include "ListaDisparosGel.h"
class ListaEnemigos
{
private:
	Enemigo* lista[MAX_ENEMIGOS];
	int numero;

public:
	ListaEnemigos();
	virtual ~ListaEnemigos();
	void dibuja();
	void mueve(float t);
	bool agregar(Enemigo* enem);
	void rebote(Plataforma p);
	void rebote(Escenario e);
	void rebote(Jugador& j);
	Enemigo* colision(Jugador& j);
	Enemigo* colisionEncima(Jugador& j);
	//Enemigo* colision(DisparoGel& d);
	Enemigo* operator [](int i);
	int getNumero() { return numero; }
	void destruirContenido();
	void eliminar(int index);
	void eliminar(Enemigo* enem);
};


