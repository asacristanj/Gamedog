#pragma once
#include "Interaccion.h"
#include "freeglut.h"
#include "Vector2D.h"
class BloqueSorpresa
{
private: 
	ColorRVA color;
	float lado;
	Vector2D posicion;
	bool usado; // variable controla si el bloque ya ha sido usado 1, o si aún el jugador no lo ha usado 0
public:
	friend class Interaccion;
	void dibuja();
	BloqueSorpresa();
	BloqueSorpresa(float l, float x, float y, unsigned char r = 255, unsigned char g = 255, unsigned char b = 100);
	virtual ~BloqueSorpresa();
	float getlado();
	void setPos(float x, float y);
	void setColor(unsigned char r, unsigned char g, unsigned char b);
	bool getuso();
};

