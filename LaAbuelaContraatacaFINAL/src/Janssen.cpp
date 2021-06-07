#include "Janssen.h"
Janssen::Janssen() {//constructor
	tipo = JANSSEN;
	color.b = 250;
	color.g = color.r = 0;
	lado = 0.5;
}
Janssen::~Janssen() {//destructor

}
Janssen::Janssen(float l, float x, float y, float vx, float vy)
{
	tipo = JANSSEN;
	lado = l;
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	color.b=250;
	color.g =color.r=0;
	aceleracion.y = -9.8;
}
void Janssen::dibuja() {
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(0.0f, 0.0f, 250.0f);
	//glutSolidCube(lado);
	sprite2.draw();
	glPopMatrix();
}