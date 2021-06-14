#include "Janssen.h"
Janssen::Janssen() {//constructor
	tipo = JANSSEN;
	lado = 0.5;
	//TAMAÑO Y CENTRO SPRITE:
	sprite.setCenter(lado/2.0f, lado / 2.0f);
	sprite.setSize(lado, lado);
}
Janssen::~Janssen() {//destructor

}
Janssen::Janssen(float l, float x, float y, float vx, float vy)
{
	tipo = JANSSEN;
	lado = l;
	sprite.setCenter(lado / 2.0f, lado / 2.0f);
	sprite.setSize(lado, lado);
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	aceleracion.y = -9.8;
}
void Janssen::dibuja() {
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(0.0f, 0.0f, 250.0f);
	//glutSolidCube(lado);
	sprite.draw();
	glPopMatrix();
}