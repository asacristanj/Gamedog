#pragma once
#include "Escalera.h"
#include "Jugador.h"
#include "Interaccion.h"
#define MAX_NUM 300
class ListaEscaleras
{
private:
	Escalera* lista[MAX_NUM];
	int numero;
public:
	friend class Interaccion;
	ListaEscaleras();
	virtual ~ListaEscaleras();
	void dibuja();
	bool agregar(Escalera* e);
	int getNumero() { return numero; }
	void destruirContenido();
	void eliminar(int index);
	void eliminar(Escalera* e);
	bool subirEscalera(Jugador j);
	bool bajarEscalera(Jugador j);
	Escalera* operator [](int i);
};

