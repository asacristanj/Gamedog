#pragma once
#include "Vector2D.h"

#include "ETSIDI.h"
using ETSIDI::SpriteSequence;
class Plataforma
{
private:
	SpriteSequence sprite{ "imagenes/plataforma.png", 1 };
	Vector2D limite1;
	Vector2D limite2;

public:
	Plataforma();
	Plataforma(float x1, float y1, float x2, float y2);
	virtual ~Plataforma();
	void dibuja(); 
	void setPos(float x1, float y1, float x2, float y2);
	float getPosxizq(){ return limite1.x; }
	float getPosxder() { return limite2.x; }
	float getPosy() { return limite2.y; }
	float distancia(Vector2D punto, Vector2D* direccion = 0);
	friend class ListaEnemigos;
	friend class Interaccion;
};
