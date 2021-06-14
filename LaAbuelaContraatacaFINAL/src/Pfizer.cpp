#include "Pfizer.h"
Pfizer::Pfizer() {//constructor
	tipo = PFIZER;
	lado = 0.5;
	sprite.setCenter(lado / 2.0f, lado / 2.0f);
	sprite.setSize(lado, lado);
}
Pfizer::~Pfizer() {//destructor

}
Pfizer::Pfizer(float l, float x, float y, float vx, float vy)
{
	tipo = PFIZER;
	lado = l;
	sprite.setCenter(lado / 2.0f, lado / 2.0f);
	sprite.setSize(lado, lado);
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	aceleracion.y = -9.8;
}
void Pfizer::dibuja() {
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(250.0f, 0.0f, 0.0f);
	//glutSolidCube(lado);
	sprite.draw();
	glPopMatrix();
}