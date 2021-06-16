#pragma once
#include "freeglut.h"
#include "Vector2D.h"
#include "ETSIDI.h"
using ETSIDI::SpriteSequence;
class BloqueSorpresa
{
private: 
	SpriteSequence sprite{ "imagenes/bloque.png", 1 };
	float lado;
	Vector2D posicion;
	bool usado; // variable controla si el bloque ya ha sido usado 1, o si aún el jugador no lo ha usado 0
public:
	friend class Interaccion;
	void dibuja();
	BloqueSorpresa();
	BloqueSorpresa(float l, float x, float y, unsigned char r = 255, unsigned char g = 223, unsigned char b = 0);
	virtual ~BloqueSorpresa();
	float getlado() { return lado; }
	bool getuso() { return usado; }
	Vector2D getPos() { return posicion; }
	void setPos(float x, float y);
	void setUsotrue() { usado = true; }
	void mueve(float t);
};

