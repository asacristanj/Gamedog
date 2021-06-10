#include "Escalera.h"
Escalera::Escalera() {
	color.r = color.g = color.b = 255;
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
}
Escalera::~Escalera() {

}
void Escalera::dibujar() {

	/*glDisable(GL_LIGHTING);
	glColor3ub(color.r, color.g, color.b);
	glBegin(GL_POLYGON);
	glVertex3d(limder1.x, limder1.y, -5);
	glVertex3d(limizq1.x, limizq1.y, -5);
	glVertex3d(limizq2.x, limizq2.y, -5);
	glVertex3d(limder2.x, limder2.y, -5);
	glEnd();
	glEnable(GL_LIGHTING);*/

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/escaleras.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	/*
	glTexCoord2d(0, 1); glVertex2f(limder1.x, limder1.y);
	glTexCoord2d(1, 1); glVertex2f(limizq1.x, limizq1.y);
	glTexCoord2d(1, 0); glVertex2f(limizq2.x, limizq2.y);
	glTexCoord2d(0, 0); glVertex2f(limder2.x, limder2.y);
	*/
	
	glTexCoord2d(0, 1);glVertex3d(limizq1.x, limizq1.y, 0);
	glTexCoord2d(1, 1);glVertex3d(limder2.x, limizq1.y,0);
	glTexCoord2d(1, 0);glVertex3d(limder2.x, limizq2.y, 0);
	glTexCoord2d(0, 0);glVertex3d(limizq1.x, limizq2.y, 0);

	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}
void Escalera::SetColor(unsigned char r, unsigned char b, unsigned char g) {
	color.r = r;
	color.g = g;
	color.b = b;
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