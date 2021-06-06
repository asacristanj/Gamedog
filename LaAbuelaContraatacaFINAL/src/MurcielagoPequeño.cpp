#include "MurcielagoPeque�o.h"
#include <CepaChina.h>
MurcielagoPeque�o::MurcielagoPeque�o()
{
	tipo = MURCIELAGOPEQUE�O;
	altura = 0.4f;
	posicion.x = 0.0f;
	posicion.y = 10.0f;
	aceleracion.y = 0;
}
MurcielagoPeque�o::MurcielagoPeque�o(float alt, float x, float y, float vx, float vy)
{
	tipo = MURCIELAGOPEQUE�O;
	altura = alt;
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	aceleracion.y = 0;
}
void MurcielagoPeque�o::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(altura, 15, 15);
	glPopMatrix();
}
void MurcielagoPeque�o::disparoChina(Vector2D posJugador)
{
	CepaChina* c = new CepaChina();
	Vector2D posInicial = posicion;
	c->setPos(posicion.x, posicion.y);
	Vector2D vel_media = (posJugador - posInicial) * (1 / (c->getTiempo())); // velocidad media de la cepa china
	c->setVel(vel_media.x, vel_media.y);
}