#pragma once
#include "Vector2D.h"
#include "ColorRVA.h"
class Plataforma
{
private:
	ColorRVA color;
	Vector2D limite1;
	Vector2D limite2;

public:
	Plataforma();
	virtual ~Plataforma();
	void dibuja();
	void setColor(Byte r, Byte v, Byte a);
	void setPos(float x1, float y1, float x2, float y2);
	float distancia(Vector2D punto, Vector2D* direccion = 0);

	friend class Interaccion;
};
