#include "BloqueSorpresa.h"

BloqueSorpresa::BloqueSorpresa() {
	posicion.x = posicion.y = 0;
	lado = 1.0f;
	sprite.setCenter(lado / 2.0f, lado / 2.0f);
	sprite.setSize(lado, lado);
	usado = false;
}
BloqueSorpresa::BloqueSorpresa(float l, float x, float y, unsigned char r,unsigned char g,unsigned char b){
	posicion.x = x;
	posicion.y = y;
	lado = l;
	sprite.setCenter(lado / 2.0f, lado / 2.0f);
	sprite.setSize(lado, lado);
	usado = false;
}
BloqueSorpresa::~BloqueSorpresa() {

}
void BloqueSorpresa::dibuja() {
	SpriteSequence sprite{ "imagenes/bloque.png", 1 };
	sprite.setCenter(lado / 2.0f, lado / 2.0f);
	sprite.setSize(lado, lado);
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	sprite.draw();
	glPopMatrix();
}
float BloqueSorpresa::getlado() {
	return lado;
}
void BloqueSorpresa::setPos(float x, float y) {
	posicion.x = x;
	posicion.y = y;
}
bool BloqueSorpresa::getuso() {
	return usado;
}
void BloqueSorpresa::setUsotrue() {
	usado = true;
}
Vector2D BloqueSorpresa::getPos() {
	return posicion;
}
void BloqueSorpresa::mueve(float t) {
	sprite.loop();
}