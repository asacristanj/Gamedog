#pragma once
#include "Juego.h"
#include "ETSIDI.h"
#include <iostream>
using namespace ETSIDI;

class Coordinador
{
public:
	Coordinador();
	virtual ~Coordinador();

	void teclaEspecial(unsigned char key);
	void tecla(unsigned char key);
	void teclaEspecialUp(unsigned char key);
	void mueve();
	void dibuja();
protected:
	Juego juego;
	enum Estado {INICIO, JUEGO, PAUSA, GAMEOVER,FIN, INSTRUCCIONES, HISTORIA};
	Estado estado;
	int contHist;
};

