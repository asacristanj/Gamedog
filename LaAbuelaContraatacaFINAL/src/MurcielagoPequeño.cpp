#include "MurcielagoPeque�o.h"
MurcielagoPeque�o::MurcielagoPeque�o()
{
	tipo = MURCIELAGOPEQUE�O;
	altura = 0.4f;
	posicion.x = 0.0f;
	posicion.y = 10.0f;
	color.r = color.g = 200;
	color.b = 0;
}
void MurcielagoPeque�o::volar()
{
	setVel(-3.0f, 0.0f);
	setVel(3.0f, 0.0f);
}