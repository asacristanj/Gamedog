#pragma once
#include "Plataforma.h"
#include "Interaccion.h"
#include "ListaEscaleras.h"
#define MAXNUM 50
class ListaPlataformas
{
private:
	Plataforma* lista[MAXNUM];
	int numero;
public:
	ListaPlataformas();
	virtual ~ListaPlataformas();
	void dibuja();
	bool agregar(Plataforma* p);
	int getNumero() { return numero; }
	void destruirContenido();
	void eliminar(int index);
	void eliminar(Plataforma* p);
	void rebote(Jugador& j);
	bool colisionEncima(Jugador j);
	Plataforma* operator [](int i);
};

