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
	suelo.dibuja(0);
	techo.dibuja(0);
	pared_izq.dibuja(0);
	pared_dcha.dibuja(0);
}

Escenario :: ~Escenario()
{

}