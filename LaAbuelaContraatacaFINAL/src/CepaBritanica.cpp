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
CepaBritanica::CepaBritanica(float alt, float x, float y, float vx, float vy)
{
	tipo = CEPABRITANICA;
	altura = alt;
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	color.r = color.b = 0;
	color.g = 100;
	aceleracion.y = -9.8f;
}
void CepaBritanica::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(0.0f, 0.0f, 255.0f);
	glutSolidSphere(altura, 15, 15);
	glPopMatrix();
}
void CepaBritanica::explotar()
{
	altura = 0.0f;
}
