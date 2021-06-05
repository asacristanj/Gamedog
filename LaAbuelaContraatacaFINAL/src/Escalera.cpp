#include "Escalera.h"
Escalera::Escalera() {
	color.r = color.g = color.b = 255;
}
Escalera::~Escalera() {

}
void Escalera::dibujar() {
	glDisable(GL_LIGHTING);
	glColor3ub(color.r, color.g, color.b);
	glBegin(GL_POLYGON);
	glVertex3d(limder1.x, limder1.y, -5);
	glVertex3d(limizq1.x, limizq1.y, -5);
	glVertex3d(limizq2.x, limizq2.y, -5);
	glVertex3d(limder2.x, limder2.y, -5);
	glEnd();
	glEnable(GL_LIGHTING);
}
void Escalera::SetColor(unsigned char r, unsigned char b, unsigned char g) {
	color.r = r;
	color.g = g;
	color.b = b;
}
void Escalera::SetPos(float limizq1x, float limizq2x, float limder1x, float limder2x, float limizq1y, float limizq2y, float limder1y, float limder2y) {
	limder1.x = limder1x;
	limder1.y = limder1y;
	limder2.x = limder2x;
	limder2.y = limder2y;
	limizq1.x = limizq1x;
	limizq1.y = limizq1y;
	limizq2.x = limizq2x;
	limizq2.y = limizq2y;
}
Vector2D Escalera::limenx() {
	Vector2D aux;
	aux.x = limder1.x;
	aux.y = limizq1.x;
	return aux;
}