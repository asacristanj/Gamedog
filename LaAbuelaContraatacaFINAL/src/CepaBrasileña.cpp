#include "CepaBrasile�a.h"
CepaBrasile�a::CepaBrasile�a()
{
	tipo = CEPABRASILE�A;
	altura = 0.4f;
	color.r = color.g = 100;
	color.b = 0;
	aceleracion.y = -9.8f;
	origenSalto = { 0,0 };
}
CepaBrasile�a::CepaBrasile�a(float alt, float x, float y, float vx, float vy)
{
	tipo = CEPABRASILE�A;
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
void CepaBrasile�a::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(0.0f, 200.0f, 200.0f);
	glutSolidSphere(altura, 15, 15);
	glPopMatrix();
}
void CepaBrasile�a::saltar()
{
	setVel(velocidad.x, 5.0f);
}
