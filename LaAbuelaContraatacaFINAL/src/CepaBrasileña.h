#pragma once
#include "Enemigo.h"
class CepaBrasile�a: public Enemigo
{
public:
	CepaBrasile�a();
	CepaBrasile�a(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void dibuja();
};

