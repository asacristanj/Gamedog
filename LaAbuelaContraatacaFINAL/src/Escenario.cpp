#include "Escenario.h"
#include "freeglut.h" 
#include "Escenario.h"

Escenario::Escenario()
{
	suelo.setColor(0, 0, 100);
	suelo.setPos(-10.0f, 0, 10.0f, 0);

	techo.setColor(0, 0, 100);
	techo.setPos(-10.0f, 100.0f, 10.0f, 100.0f);

	pared_dcha.setColor(0, 0, 100);
	pared_dcha.setPos(10.0f, 0, 10.0f, 100.0f);

	pared_izq.setColor(0, 0,100);
	pared_izq.setPos(-10.0f, 0, -10.0f, 100.0f);

}
void Escenario::dibuja()
{
	suelo.dibuja();
	techo.dibuja();
	pared_izq.dibuja();
	pared_dcha.dibuja();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fondo.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex2f(-10, 0);
	glTexCoord2d(1, 1); glVertex2f(10, 0);
	glTexCoord2d(1, 0); glVertex2f(10, 15);
	glTexCoord2d(0, 0); glVertex2f(-10, 15);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

Escenario :: ~Escenario()
{

}