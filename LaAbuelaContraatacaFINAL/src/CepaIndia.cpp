#include "CepaIndia.h"
CepaIndia::CepaIndia()
{
	tipo = CEPAINDIA;
	altura = 0.4f;
	color.r = color.b = 200;
	color.g = 0;
}
CepaIndia::CepaIndia(float alt, float x, float y, float vx, float vy)
{
	tipo = CEPAINDIA;
	altura = alt;
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	color.r = color.b = 0;
	color.g = 100;
	aceleracion.y = -9.8f;
}
void CepaIndia::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(0.0f, 255.0f, 0.0f);
	glutSolidSphere(altura, 15, 15);
	glPopMatrix();
}