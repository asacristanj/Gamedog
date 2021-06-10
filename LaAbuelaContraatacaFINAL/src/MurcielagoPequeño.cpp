#include "MurcielagoPequeño.h"
#include <CepaChina.h>
MurcielagoPequeño::MurcielagoPequeño()
{
	tipo = MURCIELAGOPEQUEÑO;
	altura = 0.4f;
	posicion.x = 0.0f;
	posicion.y = 10.0f;
	velocidad = (4.0f, 4.0f);
	aceleracion.y = 0.0f;
	velocidad_china = -5.0f;
	vidas = 1;
}
MurcielagoPequeño::MurcielagoPequeño(float alt, float x, float y, float vx, float vy)
{
	tipo = MURCIELAGOPEQUEÑO;
	altura = alt;
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	aceleracion.y = 0.0f;
	velocidad_china = -5.0f;
}
void MurcielagoPequeño::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(altura, 15, 15);
	glPopMatrix();
}
