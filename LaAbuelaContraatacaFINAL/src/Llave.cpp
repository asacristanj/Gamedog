#include "Llave.h"
Llave::Llave() {

	lado = 1.0f;
	sprite.setCenter(lado / 2.0f, lado / 2.0f);
	sprite.setSize(lado, lado);
	aceleracion.x = 0.0f;
	aceleracion.y = 0.0f;
	velocidad.x = 0.0f;
	velocidad.y = 0.0f;
}
Llave::Llave(float l, float x, float y, float vx, float vy) {
	lado = l;
	sprite.setCenter(lado / 2.0f, lado / 2.0f);
	sprite.setSize(lado, lado);
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	aceleracion.x = 0.0f;
	aceleracion.y = 0.0f;

}
Llave::~Llave() {

}
void Llave::dibuja() {
	SpriteSequence sprite{ "imagenes/llave.png", 1 };
	sprite.setCenter(lado / 2.0f, lado / 2.0f);
	sprite.setSize(lado, lado);
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	sprite.draw();
	glPopMatrix();
}
float Llave::getLado() {
	return lado;
}
void Llave::mueve(float t) {
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
	sprite.loop();
}
