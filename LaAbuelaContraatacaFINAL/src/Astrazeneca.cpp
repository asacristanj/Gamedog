#include "Astrazeneca.h"
Astrazeneca::Astrazeneca() {//constructor
	tipo = ASTRAZENECA;
	lado = 0.5;
	color.r = color.b = 250;
	color.g = 0;
	sprite.setCenter(lado / 2.0f, lado / 2.0f);
	sprite.setSize(lado, lado);
}
Astrazeneca::~Astrazeneca() {//destructor

}
Astrazeneca::Astrazeneca(float l, float x, float y, float vx, float vy)
{
	tipo = ASTRAZENECA;
	lado = l;
	sprite.setCenter(lado / 2.0f, lado / 2.0f);
	sprite.setSize(lado, lado);
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	color.r = color.b = 250;
	color.g = 0;
	aceleracion.y = -9.8;
}
void Astrazeneca::dibuja() {
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(250.0f, 0.0f, 250.0f);
	//glutSolidCube(lado);
	sprite.draw();
	glPopMatrix();
}