#include "Sputnik.h"
Sputnik::Sputnik() {//constructor
	tipo = SPUTNIK;
	color.g = 100;
	color.r = color.r = 0;
	lado = 0.5;
}
Sputnik::~Sputnik() {//destructor

}
Sputnik::Sputnik(float l, float x, float y, float vx, float vy)
{
	tipo = SPUTNIK;
	lado = l;
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	color.g = 100;
	color.b = color.r = 0;
	aceleracion.y = -9.8f;
}
void Sputnik::dibuja() {
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(0.0f, 100.0f, 0.0f);
	//glutSolidCube(lado);
	sprite5.draw();
	glPopMatrix();
}
