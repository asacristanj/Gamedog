#include "CepaBritanica.h"
CepaBritanica::CepaBritanica()
{
	tipo = CEPABRITANICA;
	altura = 1.9f;
	color.b = 200;
	color.r = color.g = 0;
	posicion.x = 1.0f;
	posicion.y = 6.0f;
	velocidad.x = 3.0f;
	aceleracion.y = -9.8f;
}
void CepaBritanica::explotar()
{
	altura = 0.0f;
}