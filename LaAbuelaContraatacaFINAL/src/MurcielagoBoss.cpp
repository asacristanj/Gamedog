#include "MurcielagoBoss.h"
#include <CepaChina.h>
MurcielagoBoss::MurcielagoBoss()
{
	tipo = MURCIELAGOBOSS;
	altura = 0.4f;
	posicion.x = 0.0f;
	posicion.y = 10.0f;
	color.r = color.g = 255;
	color.b = 0;
}
MurcielagoBoss::MurcielagoBoss(float alt, float x, float y, float vx, float vy)
{
	tipo = MURCIELAGOBOSS;
	altura = alt;
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	color.r = color.b = 0;
	color.g = 100;
	aceleracion.y = -9.8f;
}
void MurcielagoBoss::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(0.0f, 200.0f, 200.0f);
	glutSolidSphere(altura, 15, 15);
	glPopMatrix();
}
void MurcielagoBoss::volar()
{
}

void MurcielagoBoss::disparoChina(Vector2D posJugador)
{
	CepaChina* c = new CepaChina();
	Vector2D posInicial = posicion;
	c->setPos(posicion.x, posicion.y);
	Vector2D vel_media = (posJugador - posInicial) * (1 / (c->getTiempo())); // velocidad media de la cepa china
	c->setVel(vel_media.x, vel_media.y);
}
