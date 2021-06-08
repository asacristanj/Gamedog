#pragma once
#include "Vector2D.h"
#include "ColorRVA.h"
#include "ETSIDI.h"
class Plataforma
{
private:
	ColorRVA color;
	Vector2D limite1;
	Vector2D limite2;

public:
	Plataforma();
	Plataforma(float x1, float y1, float x2, float y2);
	virtual ~Plataforma();
	void dibuja(); 
	//si n==0 dibujar escenario
	//si n==1 plataformas
	void setColor(Byte r, Byte v, Byte a);
	void setPos(float x1, float y1, float x2, float y2);
	float distancia(Vector2D punto, Vector2D* direccion = 0);
	friend class ListaEnemigos;
	friend class Interaccion;
};
