#include "Interaccion.h"
#include "freeglut.h" 
#include <math.h>
#include <time.h>
#include <ctime>
#include <stdlib.h>

///////////////////////////////////////////Funciones de interacción del jugador con el resto de elementos///////////////////////////////////////////////////////////

bool Interaccion::colisionDebajo(Jugador j, Plataforma p)
{
	//Función que manda un booleano si ha habido contacto entre la plataforma y la cabeza del jugador (por debajo de la plataforma). Coge ambas posiciones y mide la distancia entre ellas.
	float distancia = p.distancia(j.getPos());
	if ((distancia <= j.getAltura() + 0.5f && j.getPos().y <= p.limite1.y))
		return true;
	return false;
}
bool Interaccion::colisionLateralDerecha(Jugador j, Plataforma p)
{
	Vector2D posj = j.getPos();
	Vector2D limite1 = p.limite1;
	Vector2D aux = posj - limite1;
	float distancia = aux.modulo();
	if (distancia < j.getAltura() && posj.y < j.getAltura() + limite1.y && j.getVel().x > 0.01f && Interaccion::colisionEncima(j, p) == false)
		return true;
	return false;
}
bool Interaccion::colisionLateralIzquierda(Jugador j, Plataforma p)
{
	Vector2D posj = j.getPos();
	Vector2D limite2 = p.limite2;
	Vector2D aux = posj - limite2;
	float distancia = aux.modulo();
	if (distancia < j.getAltura() && posj.y < j.getAltura() + limite2.y && j.getVel().x < 0.01f && Interaccion::colisionEncima(j, p) == false)
		return true;
	return false;
}
bool Interaccion::colisionEncima(Jugador j, Plataforma p)
{
	//Función que manda un booleano si ha habido contacto entre la plataforma y los pies del jugador (por encima de la plataforma). Coge ambas posiciones y mide la distancia entre ellas.
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
void Interaccion::rebote(Jugador& j, Plataforma p)
{
	//Función para que el jugador no pueda atravesar las plataformas.Coge sus límites y dice que si choca por encima se quede arriba y se choca por debajo que se queda abajo frenándose debido al choque.
	float xmax = p.limite2.x + (j.getAltura()/2.0f);
	float xmin = p.limite1.x - (j.getAltura()/2.0f);;
	float y = p.limite1.y;
	if (Interaccion::colisionEncima(j, p) && j.posicion.x < xmax && j.posicion.x > xmin && Interaccion::colisionLateralIzquierda(j, p) == false && Interaccion::colisionLateralDerecha(j, p) == false)
	{
		// freno al personaje
		j.setVel(j.getVel().x, 0.0f);
		j.setPos(j.getPos().x, y + j.getAltura());
		j.tocandosuelo = true;
	}
	else
		j.setAcel(j.getAcel().x, j.getAcelInicial()); // vuelvo a recuperar la aceleracion inicial// que la hemos cambiado por 30

	if (Interaccion::colisionDebajo(j, p) && j.getPos().x < xmax && j.getPos().x > xmin)
	{
		j.setVel(j.getVel().x, -5.0f); // el jugador rebota ligeramente al tocar la plataforma
	}

	if (Interaccion::colisionLateralDerecha(j, p) == true)
	{
		float xmin_derecha = p.limite1.x - j.getAltura()/3.5f;
		j.setPos(xmin_derecha, j.getPos().y);
	}

	if (Interaccion::colisionLateralIzquierda(j, p) == true)
	{
		float xmax_izquierda = p.limite2.x + j.getAltura()/3.5f;
		j.setPos(xmax_izquierda, j.getPos().y);
	}
}

void Interaccion::rebote(Jugador& j, Escenario e)
{
	//Función para que el jugador no se pueda salir del escenario. Coge sus límites y dice que si sobrepasa estos se quede en el borde del escenario
	float xmax = e.suelo.limite2.x - j.getAltura()/2.0f;
	float xmin = e.suelo.limite1.x + j.getAltura()/2.0f;
	if (j.getPos().x > xmax) j.setPos(xmax, j.getPos().y);
	if (j.getPos().x < xmin) j.setPos(xmin, j.getPos().y);

	//Para que el jugador se mantenga encima del escenario
	float ymin = e.suelo.limite1.y;
	if ((j.getPos().y - j.getAltura()) <= ymin) 
	{
		// freno al personaje
		j.setVel(j.getVel().x, 0.0f);
		j.setAcel(j.getAcel().x, 0.0f);
		j.setPos(j.getPos().x, ymin + j.getAltura());
	}
}

bool Interaccion::colisionDebajo(Jugador j, BloqueSorpresa b) //Funcion que detecta la colision del Jugador con el BloqueSorpresa
{
	//Calculamos la distancia entre el bloque y el jugador para detectar si hay colision;
	Vector2D aux, bloque = b.getPos(), jugador = j.getPos();
	float radio = (j.getAltura()), l = b.getlado() * 0.5f,lim1=bloque.x-l,lim2=bloque.x+l;
	aux = bloque - jugador;
	float distancia = aux.modulo();
	if ((distancia <= radio+l) && (jugador.y <= bloque.y)&&(lim1<=jugador.x)&&(jugador.x<=lim2)) 
	{
		return true;
	}
	else
		return false;
}
//Funcion que detecta la colision del jugador con el Bloque Sorpresa cuando el jugador esta por encima
bool Interaccion::colisionEncima(Jugador j, BloqueSorpresa b)
{
	Vector2D aux, bloque = b.getPos(), jugador = j.getPos();
	float radio = (j.getAltura()), l = b.getlado() * 0.5f, lim1 = bloque.x - l, lim2 = bloque.x + l;
	aux = bloque - jugador;
	float distancia = aux.modulo();
	if ((distancia <= radio + l) && (jugador.y >= bloque.y) && (lim1 <= jugador.x)&&(jugador.x <= lim2))
		return true;
	return false;
}
void Interaccion::rebote(Jugador& j, BloqueSorpresa b) //Funcion que gestiona el rebote del jugador cuando choca con el bloque sorpresa
{
	//Si el choque se produce desde abajo
	if (Interaccion::colisionDebajo(j, b)) {
		j.setVel(j.getVel().x, -5.0f);
	}

	if (Interaccion::colisionEncima(j, b)) {
		float y = b.getPos().y + b.getlado() * 0.5f;
		j.setVel(j.getVel().x, 0.0f);
		j.setAcel(j.getAcel().x, 0.0f);
		j.setPos(j.getPos().x, y + j.getAltura());
		j.tocandosuelo = true;
	}
}
bool Interaccion::colisionEscalerasubir(Escalera e, Jugador j)
{
	//Comprobamos que la posicion del jugador esta entre los limites de la escalera
	Vector2D limites = e.limenx();
	Vector2D pos = j.getPos(),esca=e.centroabajo();
	Vector2D aux = pos -esca ;
	float distancia = aux.modulo();
	if (((distancia<=j.getAltura())&&(limites.y < pos.x)&&(pos.x < limites.x)&&(pos.y<=e.limeny()+j.getAltura()/2.0f))||Interaccion::colisionEscalera(e,j))
		return true;
	return false;
}
bool Interaccion::colisionEscalera(Escalera e, Jugador j) {
	//medimos la distancia del jugador con el centro de la escalera
	Vector2D limites = e.limenx();
	Vector2D pos = j.getPos(), esca = e.centro();
	Vector2D aux = pos - esca;
	float distancia = aux.modulo();
	if (distancia <= j.getAltura() && (limites.y < pos.x) && pos.x<limites.x && pos.y <= e.limeny()&& pos.y>=e.centroabajo().y)
		return true;
	return false;

}
bool Interaccion::colisionEscalerabajar(Escalera e, Jugador j)
{
	//Comprobamos que la posicion del jugador esta entre los limites de la escalera
	Vector2D limites = e.limenx();
	Vector2D pos = j.getPos();
	Vector2D aux = pos - e.centro();
	float distancia = aux.modulo();
	if (((distancia <= j.getAltura()+2.5f)&&(limites.y < pos.x) && (pos.x < limites.x) && (pos.y <= (e.limeny() + j.getAltura()))) ||Interaccion::colisionEscalera(e, j))
		return true;
	return false;
}
///////////////////////////////////////////Funciones de interacción de los bonus con el resto de elementos///////////////////////////////////////////////////////////

bool Interaccion::colision(Bonus b, Jugador j) //Función que manda true si el jugador entra en contacto con un bonus general
{
	Vector2D pos = j.getPos();
	float distancia = (b.getPos() - pos).modulo();
	if (distancia <= j.getAltura())
	{
		return true;
	}
	return false;
}

bool Interaccion::colision(Bonus b, Plataforma p) //Funcion que manda true si hay colision entre el bonus y una plataforma. Mide distancia entre ellas y compara
{
	float distancia = p.distancia(b.getPos()); // distancia entre plataforma y centro del bonus
	if (distancia <= b.getlado() / 2.0f)
		return true;
	return false;
}

bool Interaccion::colision(Bonus& b, Escenario e) //Funcion que manda true si hay colision entre bonus y escenario. Mide distancia entre ellas y compara. 
{
	float xmax = e.suelo.limite2.x;
	float xmin = e.suelo.limite1.x;
	Vector2D pos = b.getPos();
	pos.y -= b.getlado() / 2;//se le resta el lado para que quede apoyado en a superficie de abajo
	float distancia = e.suelo.distancia(pos);

	if (distancia <= 0.1f) 
	{
		if (b.getPos().x + b.getlado() > xmax) 
		{
			b.setPos(xmax - b.getlado(), b.getPos().y);
			b.setVel(-4.0f, b.getVel().y);
		}

		if (b.getPos().x - b.getlado() < xmin) {
			b.setPos(xmin + b.getlado(), b.getPos().y);
			b.setVel(4.0f, b.getVel().y);
		}
		return true;
	}
	return false;
}

void Interaccion::rebote(Bonus& b, Plataforma p) //Función que gestiona el rebote de cualquier bonus con als plataformas
{
	//Se meto el esceneario para que haya aceleracion de plataforma a escenario y no haya en el escenario
	float xmax = p.limite2.x;
	float xmin = p.limite1.x;
	float y = p.limite1.y + b.getlado() / 2.0f; 
	if (Interaccion::colision(b, p)) 
	{
		b.setPos(b.getPos().x, y);
		b.setVel(b.getVel().x, 0.0f);
		b.setAcel(b.getAcel().x, 0.0f);
	}
}

void Interaccion::rebote(Bonus& b, Escenario e) //Función que gestiona el rebote de cualquier bonus con el escenario
{
	if (Interaccion::colision(b, e.suelo)) 
	{
		b.setVel(b.getVel().x, 0.0f);
		b.setAcel(b.getAcel().x, 0.0f);;
	}
	float ymin = e.suelo.limite1.y;

	if ((b.getPos().y - b.getlado()) < ymin)
		b.setPos(b.getPos().x, ymin + b.getlado() / 2.0f);
}

void Interaccion::rebote(Quirurgica& qui, Escenario e) //Funcion que hace el bonus de quirurgica circule por el escenario y si choca con una pared rebote
{
	float xmax = e.pared_dcha.limite2.x;
	float xmin = e.pared_izq.limite2.x;
	float smax = e.suelo.limite2.x;
	float smin = e.suelo.limite1.x;
	float ymin = e.suelo.limite1.y;
	if ((qui.posicion.y - qui.getlado() / 2) < ymin) {
		qui.posicion.y = ymin + qui.getlado() / 2;
	}
	if (qui.posicion.x > xmax)
	{
		qui.posicion.x = xmax;
		qui.velocidad.x = -3.0f;
	}
	if (qui.posicion.x < xmin)
	{
		qui.posicion.x = xmin;
		qui.velocidad.x = 3.0f;
	}
}

///////////////////////////////////////////Funciones de interacción de los enemigos con el resto de elementos///////////////////////////////////////////////////////////

bool Interaccion::colision(Enemigo enem, Plataforma p)
{
	//Función que manda un bool true si cualquier enemigo ha tocado una plataforma.
	float xmax = p.getPosxder() - (enem.getAltura() / 8.0f);
	float xmin = p.getPosxizq() + (enem.getAltura() / 8.0f);
	float ymin = p.getPosy();
	if (((enem.getPos().y - enem.getAltura() / 2.0f) < ymin) && enem.getPos().x >= xmin && enem.getPos().x <= xmax)
		return true;
	return false;
}
bool Interaccion::colision(Enemigo enem, Escenario e)
{
	//Función que manda un bool true si cualquier enemigo ha tocado con el escenario.
	float ymin = e.suelo.limite1.y;
	if ((enem.getPos().y - enem.getAltura() / 2.0f) < ymin)
		return true;
	return false;
}
bool Interaccion::colision(Enemigo enem, Jugador j)
{
	//Función que manda un boole true si ha habido contacto entre un enemigo y el jugador de frente. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D pos = j.getPos(); //la posicion de la base del hombre
	float distancia = (enem.getPos() - pos).modulo()+1.0f;
	if ((distancia <= (enem.getAltura()) && (enem.getPos().y >= (j.getPos().y - j.getAltura()))))
		return true;
	return false;
}
bool Interaccion::colisionEncima(Enemigo enem, Jugador j)
{
	//Función que manda un booleano si ha habido contacto entre un enemigo y el jugador por encima del enemigo. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D pos = j.getPos(); //la posicion de la base del hombre
	float distancia = (enem.getPos() - pos).modulo();
	if ((distancia <= enem.getAltura()) && (enem.getPos().y < (j.getPos().y - j.getAltura())))
		return true;
	return false;
}
void Interaccion::rebote(CepaIndia& ind, Plataforma p)
{
	//Función para que las CepasIndias no se puedan salir de las plataformas. Coge sus límites y dice que si sobrepasa estos se quede en el borde y además que vayan al sentido contrario.
	float xmax = p.getPosxder() - (ind.getAltura()/8.0f);
	float xmin = p.getPosxizq() + (ind.getAltura()/8.0f);
	float ymin = p.getPosy();
	if ((ind.getPos().y > ymin) && ((ind.getPos().y - ind.getAltura()) < ymin))
	{
		if (ind.getPos().x >= xmax)
		{
			ind.setPos(xmax, ind.getPos().y);
			ind.setVel(-5.0f, ind.getVel().y);
		}
		if (ind.getPos().x <= xmin)
		{
			ind.setPos(xmin, ind.getPos().y);
			ind.setVel(5.0f, ind.getVel().y);
		}
	}
	 //Además como pasaba con el jugador, para que se mantenga encima de la plataforma
	float dist=p.distancia(ind.getPos());
	if ((dist <= (ind.getAltura())) && ind.posicion.x >= xmin && ind.posicion.x <= xmax)//&&((ind.posicion.y - ind.altura / 2.0f) < ymin)
	{
		ind.posicion.y = ymin + ind.getAltura() / 2.0f;
	}
}

void Interaccion::rebote(CepaBritanica& brit, Plataforma p)
{
	//Función para que las CepasBritanicas no se puedan salir de las plataformas. Coge sus límites y dice que si sobrepasa estos se quede en el borde y además que vayan al sentido contrario.
	float xmax = p.getPosxder() - (brit.getAltura()/8.0f);
	float xmin = p.getPosxizq() + (brit.getAltura() / 8.0f);
	float ymin = p.getPosy();
	if((brit.getPos().y > ymin) && ((brit.getPos().y - brit.getAltura()) < ymin))
	{
		if (brit.getPos().x > xmax)
		{
			brit.setPos(xmax, brit.getPos().y);
			brit.setVel(-3.0f, brit.getVel().y);
		}
		if (brit.getPos().x < xmin)
		{
			brit.setPos(xmin, brit.getPos().y);
			brit.setVel(3.0f, brit.getVel().y);
		}
	}
	//Además como pasaba con el jugador, para que se mantenga encima de la plataforma
	float dist = p.distancia(brit.getPos());
	if ((dist <= (brit.getAltura())) && brit.getPos().x >= xmin && brit.getPos().x <= xmax)
		brit.setPos(brit.getPos().x, ymin + brit.getAltura() / 2.0f);
}

void Interaccion::rebote(CepaBrasileña& bra, Plataforma p)
{
	//Función para que las CepasBrasileñas no se puedan salir de las plataformas. Coge sus límites y dice que si sobrepasa estos se quede en el borde y además que vayan al sentido contrario.
	float xmax = p.getPosxder() - (bra.getAltura() / 8.0f);
	float xmin = p.getPosxizq() + (bra.getAltura() / 8.0f);
	float ymin = p.getPosy();
	int SemillaAl = rand();
	srand( (int)time(NULL) * SemillaAl); //Se crea semilla aleatoria para todas las CepasBrasileñas
	int aleatorio, DESDE = 4, HASTA = 10;
	aleatorio = rand() % (HASTA - DESDE + 1) + DESDE; //Se crea el numero aleatorio

	//Además, se le añade a esta Cepa que cuando toque el suelo toque con alturas aleatorias.
	float dist = p.distancia(bra.getPos());
	if ((dist <= bra.getAltura() / 2.0f) && (bra.getPos().y - bra.getAltura()/2.0f) < ymin && bra.getPos().x >= xmin && bra.getPos().x <= xmax)
	{
		bra.setPos(bra.getPos().x, ymin + bra.getAltura() / 2.0f);
		bra.saltar((float)aleatorio); //La Cepa salta
	}
}
void Interaccion::rebote(CepaIndia& ind, Escenario e)
{
	//Función para que las CepasIndias no se puedan salir del escenario. Coge sus límites y dice que si sobrepasa estos se quede en el borde y además que vayan al sentido contrario.
	float xmax = e.pared_dcha.limite2.x - (ind.getAltura() / 2.0f);
	float xmin = e.pared_izq.limite2.x + (ind.getAltura() / 2.0f);
	if (ind.getPos().x > xmax)
	{
		ind.setPos(xmax, ind.getPos().y);
		ind.setVel(-5.0f, ind.getVel().y);
	}
	if (ind.getPos().x < xmin)
	{
		ind.setPos(xmin, ind.getPos().y);
		ind.setVel(5.0f, ind.getVel().y);
	}
}
void Interaccion::rebote(CepaBritanica& brit, Escenario e)
{
	//Función para que las CepasBritanicas no se puedan salir del escenario. Coge sus límites y dice que si sobrepasa estos se quede en el borde y además que vayan al sentido contrario.
	float xmax = e.pared_dcha.limite2.x - (brit.getAltura() / 2.0f);
	float xmin = e.pared_izq.limite2.x + (brit.getAltura() / 2.0f);;
	if (brit.getPos().x > xmax)
	{
		brit.setPos(xmax, brit.getPos().y);
		brit.setVel(-3.0f, brit.getVel().y);
	}
	if (brit.getPos().x < xmin)
	{
		brit.setPos(xmin, brit.getPos().y);
		brit.setVel(3.0f, brit.getVel().y);
	}
}
void Interaccion::rebote(CepaBrasileña& bra, Escenario e)
{
	//Función para que las CepasBritanicas no se puedan salir del escenario. Coge sus límites y dice que si sobrepasa estos se quede en el borde y además que vayan al sentido contrario.
	float xmax = e.pared_dcha.limite2.x - (bra.getAltura() / 2.0f);
	float xmin = e.pared_izq.limite2.x + (bra.getAltura() / 2.0f);;
	if (bra.getPos().x > xmax)
	{
		bra.setPos(xmax,bra.getPos().y);
		bra.setVel(-bra.getVel().x, bra.getVel().y);
	}
	if (bra.posicion.x < xmin)
	{
		bra.setPos(xmin, bra.getPos().y);
		bra.setVel(-bra.getVel().x, bra.getVel().y);
	}
}
void Interaccion::rebote(MurcielagoPequeño& murpeq, Escenario e) // PATRON DE MOVIMIENTO DEL MURCIÉLAGO DIFERENTE. SE MUEVE HACIENDO ONDAS
{
	//Función para que los Murcielagospequeños no se puedan salir del escenario. Coge sus límites y dice que si sobrepasa estos se quede en el borde y además que vayan al sentido contrario.
	float xmax = e.pared_dcha.limite2.x - (murpeq.getAltura() / 2.0f);
	float xmin = e.pared_izq.limite2.x + (murpeq.getAltura() / 2.0f);;
	static const float posicion_referencia = murpeq.getPos().y; // referencia del movimiento
	float ymax = posicion_referencia + 1.0f;
	float ymin = posicion_referencia - 1.0f;
	if(murpeq.getPos().y > ymax)
	{
		murpeq.setPos(murpeq.getPos().x, ymax);
		murpeq.setVel(murpeq.getVel().x, -murpeq.getVel().y);
	}
	if (murpeq.getPos().y < ymin)
	{
		murpeq.setPos(murpeq.getPos().x, ymin);
		murpeq.setVel(murpeq.getVel().x, -murpeq.getVel().y);
	}
	if (murpeq.getPos().x > xmax)
	{
		murpeq.setPos(xmax, murpeq.getPos().y);
		murpeq.setVel(-murpeq.getVel().x, murpeq.getVel().y);
	}
	if (murpeq.getPos().x < xmin)
	{
		murpeq.setPos(xmin, murpeq.getPos().y);
		murpeq.setVel(-murpeq.getVel().x, murpeq.getVel().y);
	}
}
void Interaccion::rebote(MurcielagoBoss& murboss, Escenario e, Jugador j) // PATRON DE MOVIMIENTO DEL MURCIÉLAGO BOSS. SE MUEVE HACIENDO ONDAS
{
	//Función para que el MurcielagoBoss no se puedan salir del escenario. Coge sus límites y dice que si sobrepasa estos se quede en el borde y además que vayan al sentido contrario.
	float xmax = 4.0f;
	float xmin = -4.0f;
	static const float posicion_referencia = murboss.getPos().y; // posicion inicial del enemigo
	static const Vector2D velocidad_referencia = murboss.getVel(); // velocidad inicial del enemigo
	float ymax = posicion_referencia + 0.5f;
	float ymin = posicion_referencia - 0.5f;
	if (murboss.getReset())
	{
		murboss.setPos(murboss.getPos().x, posicion_referencia);
		murboss.setVel(velocidad_referencia.x, velocidad_referencia.y);
		murboss.setReset(false);
	}
	if (murboss.getDisparoRecibido() == false)
	{
		// limites de movimiento en eje y
		if (murboss.getPos().y > ymax)
		{
			murboss.setPos(murboss.getPos().x, ymax);
			murboss.setVel(murboss.getVel().x, -murboss.getVel().y);
		}
		if (murboss.getPos().y < ymin)
		{
			murboss.setPos(murboss.getPos().x, ymin);
			murboss.setVel(murboss.getVel().x, -murboss.getVel().y);
		}
		// limites relativos a escenario
		if (murboss.getPos().x > xmax) // limite max escenario 
		{
			murboss.setPos(xmax, murboss.getPos().y);
			murboss.setVel(-murboss.getVel().x, murboss.getVel().y);
		}
		if (murboss.getPos().x < xmin) // limite min escenario
		{
			murboss.setPos(xmin, murboss.getPos().y);
			murboss.setVel(-murboss.getVel().x, murboss.getVel().y);
		}
	}
	// secuencia de movimiento al recibir disparo
	if (murboss.getDisparoRecibido() == true) // si es disparado
	{
		murboss.setVel(0.0f, murboss.getVelocidadBajada()); // baja
		if (murboss.getPos().y < murboss.getPosicionBajada()) // llega a la posicion de bajada
		{
			// se queda quieto esperando que le pisen
			murboss.setPos(murboss.getPos().x, murboss.getPosicionBajada());
			murboss.setVel(0.0f, 0.0f);
			if (murboss.getPisoton() == true && murboss.getVidas() > 0) // si es pisado y aun le quedan vidas
			{
				murboss.setPos(murboss.getPos().x, posicion_referencia);
				murboss.setVel(velocidad_referencia.x, velocidad_referencia.y); // recupera el movimiento normal
				//sentencias de salida
				murboss.setDisparoRecibido(false);
				murboss.setPisoton(false);
			}
		}
	}
}

bool Interaccion::ratio(CepaBritanica brit, Jugador j)
{
	//Función que manda un booleano si el jugador se encuentra en el ratio de explosion de la CepaBritanica
	Vector2D posjugador = j.getPos(); //la posicion de la base del hombre
	posjugador.y -= j.getAltura();
	Vector2D posenemigo = brit.getPos();
	posenemigo.y -= brit.getAltura();
	float distancia = (brit.getPos() - j.getPos()).modulo();
	if ((posjugador.y + 0.1f >= posenemigo.y) && distancia <= ((brit.getAltura() / 2.0f) + (j.getAltura() / 2.0f) + 1.0f))
		return true;
	return false;
}
bool Interaccion::ratioExplosion(CepaBritanica brit, Jugador j)
{
	//Función que manda un booleano si el jugador se encuentra en el ratio de explosion para morir de la CepaBritanica
	Vector2D posjugador = j.getPos(); //la posicion de la base del hombre
	posjugador.y -= j.getAltura();
	Vector2D posenemigo = brit.getPos();
	posenemigo.y -= brit.getAltura();
	//((posjugador.y+0.1f>=posenemigo.y) || (posenemigo.y + 0.1f >= posjugador.y))
	float distancia = (brit.getPos() - j.getPos()).modulo();
	if ((posjugador.y + 0.1f >= posenemigo.y) && distancia <= ((brit.getAltura() / 2.0f) + (j.getAltura() / 2.0f) + 4.0f))
		return true;
	return false;
}
///////////////////////////////////////////Funciones de interacción de los disparos con el resto de elementos///////////////////////////////////////////////////////////


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
	//Un vector para la diferencia de posiciones y dos floats para las distancias a comparar
	Plataforma aux; //Creamos una pared auxiliar
	Vector2D p1 = d.getPos();
	Vector2D p2 = d.getOrigen();
	aux.setPos(p1.x, p1.y, p2.x, p2.y); //Que coincida con el disparo.
	float dist = aux.distancia(enem.getPos()); //para calcular su distancia 
	if (dist <= (enem.getAltura()/2.0f))
		return true;
	return false;
}
///////////////////////////////////////////Funciones de interacción de las llaves con el resto de elementos///////////////////////////////////////////////////////////

bool Interaccion::colision(Llave b, Plataforma p) //Funcion que manda true si hay colision entre el bonus y una plataforma. Mide distancia entre ellas y compara
{
	Vector2D pos = b.getPos();
	pos.y += b.getLado() / 2;//Se le suma el lado para que se apoye en la superficie de abajo
	float distancia = p.distancia(pos);
	if (distancia <= 0.1f + b.getLado()) {
		return true;
	}
	return false;
}
bool Interaccion::colision(Llave b, Jugador j) {
	Vector2D pos = j.getPos(), llave = b.getPos();
	Vector2D aux = pos - llave;
	float distancia = aux.modulo(),altura=j.getAltura(),lado=b.getLado();
	if (distancia <= (lado + altura)/2.0f)
		return true;
	return false;
}
