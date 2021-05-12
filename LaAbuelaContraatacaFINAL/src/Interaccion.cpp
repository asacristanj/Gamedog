#include "Interaccion.h"
#include "freeglut.h" 
#include <math.h>
#define PI 3.141592
void Interaccion::rebote(Jugador& j, Escenario e)
{
	//Función para que el jugador no se pueda salir del escenario. Coge sus límites y dice que si sobrepasa estos se quede en el borde del escenario
	float xmax = e.suelo.limite2.x;
	float xmin = e.suelo.limite1.x;
	if (j.posicion.x+j.altura > xmax)j.posicion.x = xmax-j.altura;
	if (j.posicion.x-j.altura< xmin)j.posicion.x = xmin+j.altura;

	float ymin = e.suelo.limite1.y;
	if ((j.posicion.y - j.altura) < ymin) j.posicion.y = ymin+j.altura;
}
void Interaccion::rebote(Jugador& j, Plataforma p)
{
	//Función para que el jugador no pueda atravesar las plataformas.Coge sus límites y dice que si choca por encima se quede arriba y se choca por debajo que se queda abajo frenándose debido al choque.
	float xmax = p.limite2.x;
	float xmin = p.limite1.x;
	float y= p.limite1.y;
	if (Interaccion::colisionEncima(j, p))
	{
		// freno al personaje
		j.velocidad.y = 0.0f;
		j.aceleracion.y = 0.0f;
	}
	else
		j.aceleracion.y = -20.0f; // vuelvo

	if (Interaccion::colisionDebajo(j, p))
		j.velocidad.y = -5.0f; // el jugador rebota ligeramente al tocar la plataforma
}
void Interaccion::rebote(Enemigo& enem, Plataforma p)
{
	//Función para que los enemgios no se puedan salir de las plataformas. Coge sus límites y dice que si sobrepasa estos se quede en el borde y además que vayan al sentido contrario.
	float xmax = p.limite2.x;
	float xmin = p.limite1.x;
	if (enem.posicion.x > xmax)
	{
		enem.posicion.x = xmax;
		enem.velocidad.x = -4.0f;
	}
	if (enem.posicion.x < xmin)
	{
		enem.posicion.x = xmin;
		enem.velocidad.x = 4.0f;
	}

	float ymin = p.limite1.y;
	if ((enem.posicion.y - enem.altura) < ymin) enem.posicion.y = ymin + enem.altura;
}
void Interaccion::rebote(Enemigo& enem, Escenario e)
{
	//Función para que los enemgios no se puedan salir de las plataformas. Coge sus límites y dice que si sobrepasa estos se quede en el borde y además que vayan al sentido contrario.
	float xmax = e.pared_dcha.limite2.x;
	float xmin = e.pared_izq.limite2.x;
	if (enem.posicion.x > xmax)
	{
		enem.posicion.x = xmax;
		enem.velocidad.x = -4.0f;
	}
	if (enem.posicion.x < xmin)
	{
		enem.posicion.x = xmin;
		enem.velocidad.x = 4.0f;
	}
}
bool Interaccion::colision(Enemigo enem, Jugador j)
{
	//Función que manda un booleano si ha habido contacto entre un enemigo y el jugador. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D pos = j.getPos(); //la posicion de la base del hombre
	pos.y += j.getAltura() / 2.0f; //posicion del centro
	float distancia = ((enem.getPos()+enem.getAltura()/2.0f) - pos).modulo();
	if (distancia < ((enem.altura/2.0f)+(j.altura/2.0f)))
		return true;
	return false;
}
bool Interaccion::colisionDebajo(Jugador j, Plataforma p)
{
	//Función que manda un booleano si ha habido contacto entre la plataforma y la cabeza del jugador. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D pos = j.getPos(); //la posicion de la base del jugador
	pos.y += (j.getAltura());
	float distancia = p.distancia(pos);
	if (distancia <= 0.2f)//compara la distancia de la plataforma al jugador con un valor pequeño
		return true;
	return false;
}
bool Interaccion::colisionEncima(Jugador j, Plataforma p)
{
	//Función que manda un booleano si ha habido contacto entre la plataforma y los pies del jugador. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D pos = j.getPos(); //la posicion de la base del jugador
	float distancia = p.distancia(pos);
	if (distancia <= j.getAltura())
		return true;
	return false;
}
bool Interaccion::colisionSuelo(Jugador j, Escenario e)
{
	//Función que manda un booleano si ha habido contacto entre el suelo y el jugador. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D pos = j.getPos(); //la posicion de la base del jugador
	float distancia = e.suelo.distancia(pos);
	if (distancia <= j.getAltura())
		return true;
	return false;
}
bool Interaccion::colision(DisparoGel d, Plataforma p)
{
	//Función que manda un booleano si ha habido contacto entre un disparo y una plataforma. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D pos = d.getPos(); //la posicion de la base del disparo
	pos.y += d.getRadio(); //posicion del centro 
	float distancia = p.distancia(pos);
	if (distancia <= d.getRadio()) 
		return true;
	return false;
}
bool Interaccion::colision(DisparoGel d, Escenario e)
{
	//Función que manda un booleano si ha habido contacto entre un disparo y el escenario. 
	if (Interaccion::colision(d, e.pared_dcha) || Interaccion::colision(d, e.techo) || Interaccion::colision(d, e.pared_izq)||Interaccion::colision(d,e.suelo))
		return true;
	return false;
}
bool Interaccion::colision(DisparoGel d, Enemigo enem) 
{
	//Función que manda un booleano si ha habido contacto entre un disparo y un enemigo. Coge ambas posiciones y mide la distancia entre ellas.
	//un vector para la diferencia de posiciones y dos floats para las distancias a comparar
	Vector2D pos=enem.getPos(),diferencia = enem.posicion-pos;
	float distancia = diferencia.modulo(),radios=enem.altura+d.getRadio();
	if (distancia <= radios) 
		return true;
	return false;
	
}
