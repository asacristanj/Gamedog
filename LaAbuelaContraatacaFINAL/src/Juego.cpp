#include "Juego.h"
#include "freeglut.h"
#include <math.h>

void Juego::inicializa()
{
	x_ojo = 0;
	y_ojo = 7.5;
	z_ojo = 30;

	bonus.setPos(5.0f, 5.0f);
	plataforma.setPos(-3.0f, 5.0f, 3.0f, 5.0f);
	enemigos.agregar(new Enemigo(1.0f, 0.0f, 10.0f, -1.0f, 0.0f));
}

void Juego::moverOjo()
{
	Vector2D pos = jugador.getPos();
	y_ojo = pos.y+6.4f;
}

void Juego::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
		0.0, y_ojo, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	escenario.dibuja();
	jugador.dibuja();
	plataforma.dibuja();
	bonus.dibuja();
	enemigos.dibuja();
	disparos.dibuja();
}

void Juego::mueve()
{
	jugador.mueve(0.025f);
	bonus.mueve(0.025f);
	enemigos.mueve(0.025f);
	disparos.mueve(0.025f);
	enemigos.rebote(escenario);
	enemigos.rebote(plataforma);
	Enemigo* aux = enemigos.colision(jugador);
	if (aux != 0)//si alg�n enemigo ha chocado
		enemigos.eliminar(aux);

	disparos.colision(escenario);
	disparos.colision(plataforma);
	Interaccion::rebote(jugador, escenario);
	Interaccion::rebote(jugador, plataforma);
}

void Juego::teclaEspecial(unsigned char key)
{
	switch (key)
	{
	   case GLUT_KEY_LEFT:
	   {
		  DisparoGel* d = new DisparoGel();
		  Vector2D pos = jugador.getPos();
		  d->setPos(pos.x, pos.y);
		  d->setVel(-4.0f, 0);
		  disparos.agregar(d);
		  break;
	   }
	   case GLUT_KEY_RIGHT:
	   {
		  DisparoGel* d = new DisparoGel();
		  Vector2D pos = jugador.getPos();
		  d->setPos(pos.x, pos.y);
		  d->setVel(4.0f, 0);
		  disparos.agregar(d);
		  break;
	   }
	   case GLUT_KEY_UP:
	   {
		  DisparoGel* d = new DisparoGel();
		  Vector2D pos = jugador.getPos();
		  d->setPos(pos.x, pos.y);
		  d->setVel(0, 4.0f);
		  disparos.agregar(d);
		  break;
	   }
	}
}

void Juego::tecla(unsigned char key)
{
	switch (key)
	{
	case 'w':
		jugador.salto(10.0f);
		break;
	case 'a':
		jugador.setPos(-0.25f, 0.0f);
		break;
	case 'd':
		jugador.setPos(0.25f, 0.0f);
		break;
	case '1':
		enemigos.agregar(new Enemigo(1.0f, 0.0f, 10.0f, -1.0f,0.0f));
		break;
	}
}
Juego::~Juego()
{
	enemigos.destruirContenido();
	disparos.destruirContenido();
}