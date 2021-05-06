#pragma once
#define MAX_ESFERAS 100
#include "Enemigo.h"
#include "Interaccion.h"
class ListaEnemigos
{
private:
	Enemigo* lista[MAX_ESFERAS];
	int numero;

public:
	ListaEnemigos();
	virtual ~ListaEnemigos();
	void dibuja();
	void mueve(float t);
	bool agregar(Enemigo* enem);
	void rebote(Escenario e);
	Enemigo* colision(Jugador& j);
	Enemigo* operator [](int i);
	int getNumero() { return numero; }
	void destruirContenido();
	void eliminar(int index);
	void eliminar(Enemigo* enem);
};


