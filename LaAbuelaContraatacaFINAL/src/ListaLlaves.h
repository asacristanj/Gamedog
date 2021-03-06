#pragma once
#include "Llave.h"
#include "Interaccion.h"
#define MAX_ELEM 3
#include "ETSIDI.h"
using ETSIDI::play;
class ListaLlaves
{
private:
	Llave* lista[MAX_ELEM];
	int numero;
public:
	ListaLlaves();
	virtual ~ListaLlaves();
	void dibuja();
	void mueve(float t);
	bool agregar(Llave* l);
	void destruirContenido();
	Llave* operator[](int i);
	void eliminar(int index);
	void eliminar(Llave* l);
	void colision(Jugador& j);
};

