#include "Bonus.h"
#include "freeglut.h" 
Bonus::Bonus()
{
	tipo = NINGUNO;
	posicion.x = 0.0f;
	posicion.y = 1.0f;
	lado = 1.0f;
	aceleracion.y = -9.8f;

	//TAMAÑO Y CENTRO SPRITE:
	sprite0.setCenter(1, 1);
	sprite0.setSize(2, 2);
	sprite1.setCenter(1, 1);
	sprite1.setSize(2, 2);
	sprite2.setCenter(1, 1);
	sprite2.setSize(2, 2);
	sprite3.setCenter(1, 1);
	sprite3.setSize(2, 2);
	sprite4.setCenter(1, 1);
	sprite4.setSize(2, 2);
	sprite5.setCenter(1, 1);
	sprite5.setSize(2, 2);
}
void Bonus::dibuja()
{
	glPushMatrix();
	/*
	glTranslatef(posicion.x, posicion.y, 0);
	glRotatef(30, 1, 1, 1);
	glColor3f(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX,
		rand() / (float)RAND_MAX);//color aleatorio 
	glutSolidCube(lado);
	*/
	glPopMatrix();
}
void Bonus::mueve(float t)
{
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
}
Bonus :: ~Bonus()
{

}