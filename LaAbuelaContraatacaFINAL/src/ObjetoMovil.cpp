#include "ObjetoMovil.h"
void ObjetoMovil::mueve(float t)
{
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
}
void ObjetoMovil::setPos(float ix, float iy)
{
	posicion.x = ix;
	posicion.y = iy;
}
void ObjetoMovil::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(0.0f, 200.0f, 200.0f);
	glutSolidSphere(5, 15, 15);
	glPopMatrix();
}
void ObjetoMovil::setVel(float vx, float vy)
{
	velocidad.x = vx;
	velocidad.y = vy;
}

void ObjetoMovil::setAcel(float ax, float ay)
{
	aceleracion.x = ax;
	aceleracion.y = ay;
}

void ObjetoMovil::setVelx(float vx)
{
	velocidad.x = vx;
}
void ObjetoMovil::setVely(float vy) {
	velocidad.y = vy;
}