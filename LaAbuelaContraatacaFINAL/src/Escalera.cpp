#include "Escalera.h"
Escalera::Escalera() {
}
Escalera::Escalera(float limizqx, float limderx,float ybase, float altura, float ancho) {
	limder1.x = limderx;
	limder1.y = ybase;
	limder2.x = limderx;
	limder2.y = ybase+altura;
	limizq1.x = limizqx;
	limizq1.y = ybase;
	limizq2.x = limizqx;
	limizq2.y = ybase+altura;
	sprite.setCenter((limder1.x - limizq1.x) / 2.0f, altura / 2.0f);
	sprite.setSize(limderx - limizqx, altura);
}
Escalera::~Escalera() {

}
void Escalera::dibujar() {

	glPushMatrix();
	glTranslatef(((limder1.x - limizq1.x) / 2.0f)+limizq1.x, ((limizq2.y - limizq1.y) / 2.0f) + limizq1.y, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	sprite.draw();
	glPopMatrix();
}
void Escalera::SetPos(float limizqx, float limderx, float ybase, float altura, float ancho) {
	limder1.x = limderx;
	limder1.y = ybase;
	limder2.x = limderx;
	limder2.y = ybase + altura;
	limizq1.x = limizqx;
	limizq1.y = ybase;
	limizq2.x = limizqx;
	limizq2.y = ybase + altura;
}
Vector2D Escalera::limenx() {
	Vector2D aux;
	aux.x = limder1.x;
	aux.y = limizq1.x;
	return aux;
}float Escalera::limeny() {
	return limizq2.y;
}
Vector2D Escalera::centro() {
	Vector2D aux;
	float ancho = limder1.x - limizq1.x, altura = limizq2.y - limizq1.y;
	aux.x = limder1.x - ancho * 0.5f;
	aux.y = limder1.y + altura * 0.5f;
	return aux;
}
Vector2D Escalera::centroabajo() {
	Vector2D aux;
	float ancho = limder1.x - limizq1.x;
	aux.x = limder1.x - (ancho / 2.0f);
	aux.y = limder1.y;
	return aux;
}
Vector2D Escalera::centroarriba() {
	Vector2D aux;
	float ancho = limder1.x-limizq1.x;
	aux.x= limder2.x - (ancho / 2.0f);
	aux.y = limder2.y;
	return aux;
}