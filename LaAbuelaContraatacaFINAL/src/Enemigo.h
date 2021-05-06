#pragma once
#include "Vector2d.h"
#include "ColorRVA.h"
class Enemigo
{
private:
	float altura;
	ColorRVA color;
	Vector2D posicion;
	Vector2D velocidad;
	Vector2D aceleracion;

public:
	Enemigo();
	Enemigo(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	virtual ~Enemigo();
	void dibuja();
	void mueve(float t);
	void setColor(Byte r, Byte v, Byte a);
	void setAltura(float alt);
	void setPos(float ix, float iy);
	void setVel(float vx, float vy);
	Vector2D getPos() { return posicion; }
	float getAltura() { return altura; }

	friend class Interaccion;
};

