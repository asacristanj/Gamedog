#pragma once
#define MAX_ENEMIGOS 100
#include "Enemigo.h"
#include "Interaccion.h"
class ListaEnemigos
{
private:
	Enemigo* lista[MAX_ENEMIGOS];
	int numero;
	bool inicializar_hora_inicio = false; //Variable que guarda si se ha usado el temporizador de la CepaBritanica
public:
	ListaEnemigos();
	virtual ~ListaEnemigos();
	void dibuja();
	void mueve(float t);
	bool agregar(Enemigo* enem);
	void rebote(Plataforma p);
	void rebote(Escenario e);
	void rebote(Jugador& j);
	void reboteBoss(Escenario e, Jugador& j);
	Enemigo* operator [](int i);
	int getNumero() { return numero; }
	void destruirContenido();
	void eliminar(int index);
	void eliminar(Enemigo* enem);
};


