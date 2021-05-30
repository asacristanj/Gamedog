#pragma once
#define MAX_BONUS 10
#include "Bonus.h"
#include "Interaccion.h"
class ListaBonus
{
private:
	Bonus* lista[MAX_BONUS];
	int numero;
public:
	ListaBonus();
	virtual ~ListaBonus();
	void dibuja();
	void mueve(float t);
	bool agregar(Bonus* b);
	void rebote(Plataforma p);
	void rebote(Escenario e);
	void rebote(Jugador& j);
	Bonus* colision(Jugador& j);
	Bonus* operator [](int i);
	int getNumero() { return numero; }
	void destruirContenido();
	void eliminar(int index);
	void eliminar(Bonus* b);
};
