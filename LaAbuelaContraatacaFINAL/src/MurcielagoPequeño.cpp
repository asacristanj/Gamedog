#include "MurcielagoPeque�o.h"
#include <CepaChina.h>
MurcielagoPeque�o::MurcielagoPeque�o()
{
	tipo = MURCIELAGOPEQUE�O;
	altura = 0.4f;
	posicion.x = 0.0f;
	posicion.y = 10.0f;
	velocidad = (5.0f, 5.0f);
	aceleracion.y = 0;
	velocidad_china = -5.0f;
	posiciony_inicial = 0.0f;
}
MurcielagoPeque�o::MurcielagoPeque�o(float alt, float x, float y, float vx, float vy)
{
	tipo = MURCIELAGOPEQUE�O;
	altura = alt;
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	aceleracion.y = 0;
	velocidad_china = -5.0f;
	posiciony_inicial = y;
}
void MurcielagoPeque�o::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(altura, 15, 15);
	glPopMatrix();
}
