#include "MurcielagoBoss.h"
#include <CepaChina.h>

MurcielagoBoss::MurcielagoBoss()
{
	tipo = MURCIELAGOBOSS;
	altura = 1.0f;
	sprite.setCenter(altura / 2.0f, altura / 2.0f);
	sprite.setSize(altura, altura);
	posicion.x = 0.0f;
	posicion.y = 10.0f;
	velocidad = (2.0f, 2.0f);
	aceleracion.y = 0.0f;
	vidas = 3;
	posicion_bajada = 1.0f;
	velocidad_bajada = -5.0f;
	velocidad_china = -5.0f;
	horaIniciocaida = time(NULL);
}
MurcielagoBoss::MurcielagoBoss(float alt, float x, float y, float vx, float vy)
{
	tipo = MURCIELAGOBOSS;
	altura = alt;
	sprite.setCenter(altura / 2.0f, altura / 2.0f);
	sprite.setSize(altura, altura);
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	aceleracion.y = 0.0f;
	velocidad_china = -5.0f;
	posicion_bajada = 1.0f;
	velocidad_bajada = -5.0f;
	velocidad_china = -5.0f;
	horaIniciocaida = time(NULL);
	vidas = 3;
}
void MurcielagoBoss::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(0.0f, 200.0f, 200.0f);
	//glutSolidSphere(altura, 15, 15);

	if (velocidad.x > 0.01)sprite.flip(false, false);
	if (velocidad.x < -0.01)sprite.flip(true, false);
	if ((velocidad.x < 0.01) && (velocidad.x > -0.01))
		sprite.setState(0);
	else if (sprite.getState() == 0)
		sprite.setState(1, false);
	sprite.draw();
	glPopMatrix();
}
void MurcielagoBoss::mueve(float t)
{
	sprite.loop();
	time_t horaActual = time(NULL);
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
	if ((horaActual - horaIniciocaida) > 3)
	{
		velocidad.y = -5.0f;
		horaIniciocaida = time(NULL);
	}
}
