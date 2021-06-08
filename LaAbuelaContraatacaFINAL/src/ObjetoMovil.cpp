#include "ObjetoMovil.h"
ObjetoMovil::ObjetoMovil()
{
	posicion = velocidad = aceleracion = { 0,0 };
	puntuacion = 0;
}
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

void ObjetoMovil::setVel(float vx, float vy)
{
	velocidad.x = vx;
	velocidad.y = vy;
}

void ObjetoMovil::setVelx(float vx)
{
	velocidad.x = vx;
}
void ObjetoMovil::setVely(float vy) {
	velocidad.y = vy;
}
void ObjetoMovil::setPunt(int punt) {
	puntuacion= punt;
}