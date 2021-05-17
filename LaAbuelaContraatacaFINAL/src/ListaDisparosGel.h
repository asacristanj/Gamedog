#pragma once
#define MAX_DISPAROS 10
#include "DisparoGel.h"
#include "Interaccion.h"
class ListaDisparosGel
{
private:
	DisparoGel* lista[MAX_DISPAROS];
	int numero;
public:
	ListaDisparosGel();
	virtual ~ListaDisparosGel();
	bool agregar(DisparoGel* d);
	void destruirContenido();
	void mueve(float t);
	void dibuja();
	void colision(Plataforma p);
	void colision(Escenario e);
	void colision(Enemigo e);
};



