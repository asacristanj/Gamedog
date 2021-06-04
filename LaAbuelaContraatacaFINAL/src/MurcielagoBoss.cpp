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

void MurcielagoBoss::disparoChina(Vector2D posJugador)
{
	CepaChina* c = new CepaChina();
	Vector2D posInicial = posicion;
	c->setPos(posicion.x, posicion.y);
	Vector2D vel_media = (posJugador - posInicial) * (1 / (c->getTiempo())); // velocidad media de la cepa china
	c->setVel(vel_media.x, vel_media.y);
}
