#pragma once
#include "Vector2D.h"
#include "ColorRVA.h"
#include "ETSIDI.h"
class Escalera
{
private:
	Vector2D limder1,limder2, limizq1,limizq2;
	ColorRVA color;
public:
	Escalera();
	Escalera(float limizqx, float limderx, float ybase, float altura, float ancho);
	virtual ~Escalera();
	void dibujar();
	void SetColor(unsigned char r, unsigned char b, unsigned char g);
	void SetPos(float limizqx, float limderx, float ybase, float altura, float ancho);
	Vector2D limenx();
	Vector2D centro();
	float limeny();
};