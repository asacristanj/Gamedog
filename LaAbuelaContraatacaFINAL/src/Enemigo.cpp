#include "Enemigo.h"
#include "freeglut.h" 
Enemigo::Enemigo()
{
	tipo = NINGUNO;
	altura = 2.0f;
	aceleracion.y = -9.8f;
	disparo_recibido = false;
	pisoton = false;
	vidas = 1;
}
Enemigo::Enemigo(float alt, float x, float y, float vx, float vy)
{
	tipo = NINGUNO;
	altura = alt;
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	aceleracion.y = -9.8f;
	vidas = 1;
	pisoton = false;
	disparo_recibido = false;
}
void Enemigo::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	//glutSolidSphere(altura, 15, 15);
	glPopMatrix();
}
void Enemigo::mueve(float t)
{
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
}
void Enemigo::setAltura(float alt)
{
	if (alt < 0.1f)alt = 0.1f;
	altura = alt;
}
Enemigo :: ~Enemigo()
{

}
