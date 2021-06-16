#pragma once
#include "Vector2D.h"
#include "ETSIDI.h"
using ETSIDI::SpriteSequence;
class Escalera
{
private:
	SpriteSequence sprite{ "imagenes/escaleras.png", 1 };
	Vector2D limder1,limder2, limizq1,limizq2;
public:
	Escalera();
	Escalera(float limizqx, float limderx, float ybase, float altura);
	virtual ~Escalera();
	void dibujar();
	void SetPos(float limizqx, float limderx, float ybase, float altura);
	Vector2D limenx();
	Vector2D centro();
	Vector2D centroabajo();
	Vector2D centroarriba();
	float limeny();
};