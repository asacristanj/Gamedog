#include "Juego.h"
#include "freeglut.h"
#include <math.h>

void Juego::inicializa()
{
	x_ojo = 0;
	y_ojo = 7.5;
	z_ojo = 30;

	bonus.setPos(5.0f, 5.0f);
	disparogel.setPos(-5.0f, 0.0f);

	plataforma.setPos(-5.0f, 9.0f, 5.0f, 9.0f);
}

void Juego::rotarOjo()
{
	float dist = (float)sqrt(x_ojo * x_ojo + z_ojo * z_ojo);
	float ang = (float)atan2(z_ojo, x_ojo);
	ang += 0.05f;
	x_ojo = (float)dist * (float)cos(ang);
	z_ojo = (float)dist * (float)sin(ang);
}

void Juego::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
		0.0, y_ojo, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	escenario.dibuja();
	jugador.dibuja();
	disparogel.dibuja();
	plataforma.dibuja();
	bonus.dibuja();
}

void Juego::mueve()
{
	jugador.mueve(0.025f);
	bonus.mueve(0.025f);
	disparogel.mueve(0.025f);
	Interaccion::rebote(jugador, escenario);
}

void Juego::teclaEspecial(unsigned char key)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		jugador.setVel(-5.0f, 0.0f);
		break;
	case GLUT_KEY_RIGHT:
		jugador.setVel(5.0f, 0.0f);
		break;
	}
}

void Juego::tecla(unsigned char key)
{

}