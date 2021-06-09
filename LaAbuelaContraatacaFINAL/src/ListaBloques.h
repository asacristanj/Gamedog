#pragma once
#define MAXNUMBER 3
#include "BloqueSorpresa.h"
#include "ListaBonus.h"
class ListaBloques
{
private:
	BloqueSorpresa* lista[MAXNUMBER];
	int numero;
public:
	friend class Interaccion;
	ListaBloques();
	virtual ~ListaBloques();
	void dibuja();
	bool agregar(BloqueSorpresa* b);
	int getNumero() { return numero; }
	void destruirContenido();
	void rebote(Jugador& j);
	void CrearBonus(ListaBonus& b, Jugador j);
	BloqueSorpresa* operator [](int i);
};

