#include "CepaBrasileña.h"
CepaBrasileña::CepaBrasileña()
{
	tipo = CEPABRASILEÑA;
	altura = 0.4f;
	color.r = color.g = 100;
	color.b = 0;
	aceleracion.y = -9.8f;
	origenSalto = { 0,0 };
}
CepaBrasileña::CepaBrasileña(float alt, float x, float y, float vx, float vy)
{
	tipo = CEPABRASILEÑA;
	altura = alt;
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	color.r = color.b = 0;
	color.g = 100;
	aceleracion.y = -9.8f;
	origenSalto = { 0,0 };
}
void CepaBrasileña::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(0.0f, 200.0f, 200.0f);
	glutSolidSphere(altura, 15, 15);
	glPopMatrix();
}
void CepaBrasileña::saltar()
{
	setVel(velocidad.x, 5.0f);
}
