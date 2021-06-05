#pragma once
#include "Vector2D.h"
#include "ColorRVA.h"
class Escalera
{
private:
	Vector2D limder1,limder2, limizq1,limizq2;
	ColorRVA color;
public:
	Escalera();
	virtual ~Escalera();
	void dibujar();
	void SetColor(unsigned char r, unsigned char b, unsigned char g);
	void SetPos(float limizq1x, float limizq2x, float limder1x, float limder2x, float limizq1y, float limizq2y, float limder1y, float limder2y);
	Vector2D limenx();
};

