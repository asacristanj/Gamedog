#include "Juego.h"
#include "freeglut.h"
#include <math.h>
void Juego::inicializa()
{
	x_ojo = 0;
	y_ojo = 7.5;
	z_ojo = 30;

	bonus.setPos(5.0f, 5.0f);
	plataforma.setPos(-3.0f, 4.0f, 3.0f, 4.0f);
	enemigos.agregar(new Enemigo(1.5f, 0.0f, 10.0f, -1.0f, 0.0f));
}

void Juego::moverOjo()
{
	//Se coge la posicion actual del jugador para centrarla en él y se suma una cantidad para ajustarlo al escenario
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
	//enemigos.rebote(escenario);
	enemigos.rebote(plataforma);
	//Se crea un enemigo auxiliar que revisa si todos los enemigos se choca con un jugador
	Enemigo* aux = enemigos.colision(jugador);
	Enemigo* aux1 = enemigos.colisionEncima(jugador);
	//funcion que regula que el disparo elimina al enemigo
	if (aux != 0)//si algún enemigo ha chocado
		jugador.morir();
	else if (aux1 != 0)//si algún enemigo ha chocado
		enemigos.eliminar(aux1);
	disparos.colision(escenario);
	disparos.colision(plataforma);
	Interaccion::rebote(jugador, escenario);
	Interaccion::rebote(jugador, plataforma);
	Interaccion::rebote(bonus, plataforma);
	Interaccion::rebote(bonus, escenario);
	enemigos.colision(disparos);
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
	   case GLUT_KEY_UP:
		   //Para que no pueda saltar en el aire
		   if (Interaccion::colisionEncima(jugador, plataforma) || Interaccion::colisionSuelo(jugador, escenario))
			   jugador.salto(19.0f);
		   break;
	}
}
void Juego::teclaEspecialUp(unsigned char key) //al dejar de pulsar la tecla
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		jugador.setVel(0.0f, 0.0f);
		break;
	case GLUT_KEY_RIGHT:
		jugador.setVel(0.0f, 0.0f);
		break;
	case GLUT_KEY_UP:
		//Para que no pueda saltar en el aire
		if (Interaccion::colisionEncima(jugador, plataforma) || Interaccion::colisionSuelo(jugador, escenario))
			jugador.salto(19.0f);
		break;
	}
}

void Juego::tecla(unsigned char key)
{
	switch (key)
	{
	case 'w':
	{
		DisparoGel* d = new DisparoGel();
		Vector2D pos = jugador.getPos();
		d->setPos(pos.x, pos.y);
		d->setVel(0, 6.0f);
		disparos.agregar(d);
		break;
	}
	case 'a':
	{
		//Se crea un nuevo disparo y se dispara en la posición actual del jugador, para hacer la animación que la dispara él
		DisparoGel* d = new DisparoGel();
		Vector2D pos = jugador.getPos();
		d->setPos(pos.x, pos.y);
		d->setVel(-6.0f, 0);
		disparos.agregar(d);
		break;
	}
	case 'd':
	{
		DisparoGel* d = new DisparoGel();
		Vector2D pos = jugador.getPos();
		d->setPos(pos.x, pos.y);
		d->setVel(6.0f, 0);
		disparos.agregar(d);
		break;
	}
	case '1':
		enemigos.agregar(new Enemigo(2.0f, 0.0f, 10.0f, -1.0f,0.0f));
		break;
	}
}
Juego::~Juego()
{
	enemigos.destruirContenido();
	disparos.destruirContenido();
}