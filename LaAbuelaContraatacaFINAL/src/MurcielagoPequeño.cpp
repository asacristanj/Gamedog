#include "MurcielagoPequeño.h"
#include <CepaChina.h>
MurcielagoPequeño::MurcielagoPequeño()
{
	tipo = MURCIELAGOPEQUEÑO;
	altura = 0.4f;
	sprite.setCenter(altura / 2.0f, altura / 2.0f);
	sprite.setSize(altura, altura);
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
	sprite.setCenter(altura / 2.0f, altura / 2.0f);
	sprite.setSize(altura, altura);
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
	glColor3f(0.0f, 200.0f, 200.0f);

	if (velocidad.x > 0.01)sprite.flip(false, false);
	if (velocidad.x < -0.01)sprite.flip(true, false);
	if ((velocidad.x < 0.01) && (velocidad.x > -0.01))
		sprite.setState(0);
	else if (sprite.getState() == 0)
		sprite.setState(1, false);
	sprite.draw();
	glPopMatrix();
}
void MurcielagoPequeño::mueve(float t)
{
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
	sprite.loop();
}
