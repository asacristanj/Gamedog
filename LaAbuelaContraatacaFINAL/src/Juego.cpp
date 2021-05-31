#include "Juego.h"
#include "freeglut.h"
#include <math.h>
#include "ETSIDI.h"

void Juego::inicializa()
{
	x_ojo = 0;
	y_ojo = 7.5;
	z_ojo = 30;

	//bonus.setPos(5.0f, 5.0f);
	plataforma.setPos(-5.0f, 4.0f, 5.0f, 4.0f);
	//enemigos.agregar(new Enemigo(1.5f, 0.0f, 10.0f, -1.0f, 0.0f));
	//Agregamos un bonus inicial
	//bonuses.agregar(new Astrazeneca(0.5f,-5.0f,8));
	//bonuses.agregar(new Janssen(0.5f,-4.0f,5));
	//bonuses.agregar(new MascarillaTocha(3.0f,-0.5f,9));
	//bonuses.agregar(new Pfizer(0.5f,1.0f,3));
	//bonuses.agregar(new Quirurgica(3.0f,5.0f,10));
	//bonuses.agregar(new Sputnik(0.5f,8.5f,6));
	enemigos.agregar(new CepaBrasileña(1.0f, -2.0f, 5.0f, 2.0f, 0.0f));
	enemigos.agregar(new CepaBrasileña(1.0f, 2.0f, 5.0f, -2.0f, 0.0f));
	//enemigos.agregar(new CepaBritanica(1.0f, -2.0f, 5.0f, 2.0f, 0.0f));
	//enemigos.agregar(new CepaBritanica(1.0f, 2.0f, 5.0f, -2.0f, 0.0f));
	//enemigos.agregar(new CepaChina(1.5f, 0.0f, 15.0f, -1.0f, 0.0f));
	//enemigos.agregar(new CepaIndia(1.5f, -4.0f, 10.0f, -1.0f, 0.0f));
	//bloques.agregar(new BloqueSorpresa(1.0f, 7.0f, 4.0f));
}

void Juego::moverOjo()
{
	//Se coge la posicion actual del jugador para centrarla en él y se suma una cantidad para ajustarlo al escenario
	Vector2D pos = jugador.getPos();
	y_ojo = pos.y+5.0f;
}

void Juego::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
		0.0, y_ojo, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	escenario.dibuja();
	jugador.dibuja();
	plataforma.dibuja();
	bonuses.dibuja();
	enemigos.dibuja();
	disparos.dibuja();
	bloques.dibuja();
}

void Juego::mueve()
{
	jugador.mueve(0.025f);
	bonuses.mueve(0.025f);
	enemigos.mueve(0.025f);
	disparos.mueve(0.025f);
	//enemigos.rebote(escenario);
	enemigos.rebote(plataforma);
	enemigos.rebote(jugador);
	//Se crea un enemigo auxiliar que revisa si todos los enemigos se choca con un jugador
	/*Enemigo* aux = enemigos.colision(jugador);
	Enemigo* aux1 = enemigos.colisionEncima(jugador);
	//funcion que regula que el disparo elimina al enemigo
	if (aux != 0)//si algún enemigo ha chocado
		jugador.morir();
	else if (aux1 != 0)//si algún enemigo ha chocado
		enemigos.eliminar(aux1);*/
	disparos.colision(escenario);
	disparos.colision(plataforma);
	bonuses.rebote(escenario);
	bonuses.rebote(plataforma);
	bonuses.rebote(jugador);
	Interaccion::rebote(jugador, escenario);
	Interaccion::rebote(jugador, plataforma);
	//Interaccion::rebote(bonus, plataforma);
	//Interaccion::rebote(bonus, escenario);
	for (int i = 0; i < enemigos.getNumero(); i++)
	{
		for (int j = 0; j < disparos.getNumero(); j++)
		{
			if (Interaccion::colision(*disparos[i], *enemigos[i]))
			{
				disparos.eliminar(disparos[i]);
				enemigos.eliminar(enemigos[i]);
			}
		}
	}
	/*for (int i = 0; i < enemigos.getNumero(); i++)
	{
		if (Interaccion::ratio(brit, jugador))
		{
			brit.setVel(0, 0);
			const int SEGUNDOS = 2; //Tiempo que tarda en explotar
			int horaActual;
			int horaInicio = (int)time(NULL);
			horaActual = (int)time(NULL);
			if ((horaActual - horaInicio) > SEGUNDOS)
			{
				brit.explotar();
				if (Interaccion::ratio(brit, jugador))
					jugador.morir();
			}
		}
	}*/ 
	bloques.rebote(jugador);
}

void Juego::teclaEspecial(unsigned char key)
{
	switch (key)
	{
	   case GLUT_KEY_LEFT:
		   jugador.setVelx(-5.0f); // solo modifico la velocidad en el eje x
		   break;
	   case GLUT_KEY_RIGHT:
		   jugador.setVelx(5.0f);
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
		jugador.setVelx(0.0f);
		break;
	case GLUT_KEY_RIGHT:
		jugador.setVelx(0.0f);
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
	{/*
		//incorporo disparos dependiendo del bonus hacia arriba
		if (disparos.getNumero() < MAX_DISPAROS && (jugador.GetNumBonus() == 2)){
			DisparoGel* d = Factoria::CrearDisparo(jugador);
			//Vector2D pos = jugador.getPos();
			//d->setPos(pos.x, pos.y);
			d->setVel(0.0f, 6.0f);
			disparos.agregar(d);
		}
		
		break;
		*/
		DisparoGel* d = new DisparoGel();
		Vector2D pos = jugador.getPos();
		d->setPos(pos.x, pos.y);
		d->setVel(0, 6.0f);
		disparos.agregar(d);
		break;
	}
	case 'a':
	{/*
		//incorporo disparos dependiendo del bonus hacia izquierda
		if (disparos.getNumero() < MAX_DISPAROS && (jugador.GetNumBonus() == 2)) {
			DisparoGel* d = Factoria::CrearDisparo(jugador);
			//Vector2D pos = jugador.getPos();
			//d->setPos(pos.x, pos.y);
			d->setVel(-6.0f, 0);
			disparos.agregar(d);
		}
		break;
		*/
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
		//incorporo disparos dependiendo del bonus hacia derecha
		/*if (disparos.getNumero() < MAX_DISPAROS && (jugador.GetNumBonus()==2)) {
			DisparoGel* d = Factoria::CrearDisparo(jugador);
			//Vector2D pos = jugador.getPos();
			//d->setPos(pos.x, pos.y);
			d->setVel(6.0f, 0);
			disparos.agregar(d);
		}
		break;
		*/
		
		DisparoGel* d = new DisparoGel();
		Vector2D pos = jugador.getPos();
		d->setPos(pos.x, pos.y);
		d->setVel(6.0f, 0);
		disparos.agregar(d);
		break;
	}
	case '1':
		enemigos.agregar(new CepaBritanica(1.5f, -2.0f, 10.0f, -0.5f, 0.0f));
		break;
	}
}
Juego::~Juego()
{
	enemigos.destruirContenido();
	disparos.destruirContenido();
	bonuses.destruirContenido();
}