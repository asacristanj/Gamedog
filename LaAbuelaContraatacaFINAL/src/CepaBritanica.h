#pragma once
#include "Enemigo.h"
class CepaBritanica: public Enemigo
{
public:
	CepaBritanica();
	CepaBritanica(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void explotar();
	void dibuja();
};

