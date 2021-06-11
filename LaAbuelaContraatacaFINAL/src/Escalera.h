#pragma once
#include "Vector2D.h"
#include "ColorRVA.h"
#include "ETSIDI.h"
using ETSIDI::SpriteSequence;
class Escalera
{
private:
	SpriteSequence sprite{ "imagenes/escaleras.png", 1 };
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
	Vector2D centroabajo();
	Vector2D centroarriba();
	float limeny();
};