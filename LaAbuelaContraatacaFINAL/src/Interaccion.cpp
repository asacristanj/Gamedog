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
		j.velocidad.y = 0.0f;
		//j.aceleracion.y = 0.0f;
		j.posicion.y = y + j.getAltura();
		j.tocandosuelo = true;
	}
	else
		j.aceleracion.y = j.acel_inicial; // vuelvo a recuperar la aceleracion inicial// que la hemos cambiado por 30
	if (Interaccion::colisionDebajo(j, p) && j.posicion.x < xmax && j.posicion.x > xmin)
	{
		j.velocidad.y = -5.0f; // el jugador rebota ligeramente al tocar la plataforma
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
	if (j.posicion.x > xmax)j.posicion.x = xmax;
	if (j.posicion.x < xmin)j.posicion.x = xmin;

	//Para que el jugador se mantenga encima del escenario
	float ymin = e.suelo.limite1.y;
	if ((j.getPos().y - j.getAltura()) <= ymin) {
		j.velocidad.y = 0.0f;
		j.aceleracion.y = 0.0f;
		j.posicion.y = ymin + j.getAltura();
		// freno al personaje
	}
}

bool Interaccion::colisionDebajo(Jugador j, BloqueSorpresa b)
{
	//Calculamos la distancia entre el bloque y el jugador para detectar si hay colision;
	Vector2D aux, bloque = b.posicion, jugador = j.getPos();
	float radio = (j.getAltura()), l = b.lado * 0.5f,lim1=bloque.x-l,lim2=bloque.x+l;
	aux = bloque - jugador;
	float distancia = aux.modulo();
	if ((distancia <= radio+l) && (jugador.y <= bloque.y)&&(lim1<=jugador.x)&&(jugador.x<=lim2)) 
	{
		return true;
	}
	else
		return false;
}
bool Interaccion::colisionEncima(Jugador j, BloqueSorpresa b)
{
	Vector2D aux, bloque = b.posicion, jugador = j.getPos();
	float radio = (j.getAltura()), l = b.lado * 0.5f, lim1 = bloque.x - l, lim2 = bloque.x + l;
	aux = bloque - jugador;
	float distancia = aux.modulo();
	if ((distancia <= radio + l) && (jugador.y >= bloque.y) && (lim1 <= jugador.x)&&(jugador.x <= lim2))
		return true;
	return false;
}
void Interaccion::rebote(Jugador& j, BloqueSorpresa b)
{
	//Si el choque se produce desde abajo
	if (Interaccion::colisionDebajo(j, b)) {
		j.velocidad.y = -5.0f;
		
	}
	if (Interaccion::colisionEncima(j, b)) {
		float y = b.posicion.y + b.getlado() * 0.5f;
		j.velocidad.y = 0.0f;
		j.aceleracion.y = 0.0f;
		j.posicion.y = y + j.altura;
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
	if ((distancia <= ((j.altura))))
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
	if (b.posicion.x + b.getlado() > xmax) {
		b.posicion.x = xmax - b.getlado();
		b.velocidad.x = -4.0f;
	}
	if (b.posicion.x - b.getlado() < xmin) {
		b.posicion.x = xmin + b.getlado();
		b.velocidad.x = 4.0f;
	}
	Vector2D pos = b.getPos();
	pos.y -= b.getlado() / 2;//se le resta el lado para que quede apoyado en a superficie de abajo
	float distancia = e.suelo.distancia(pos);
	if (distancia <= 0.1f) {
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
		b.velocidad.y = 0.0f;
		b.aceleracion.y = 0.0f;
	}
	else 
	{
		//b.aceleracion.y = -2.0f;
	}
}

void Interaccion::rebote(Bonus& b, Escenario e) //Función que gestiona el rebote de cualquier bonus con el escenario
{
	if (Interaccion::colision(b, e.suelo)) 
	{
		b.velocidad.y = 0;
		b.aceleracion.y = 0;
	}
	float ymin = e.suelo.limite1.y;
	if ((b.posicion.y - b.getlado()) < ymin) b.posicion.y = ymin + b.getlado() /2;
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
	float xmax = p.limite2.x - (enem.getAltura() / 8.0f);
	float xmin = p.limite1.x + (enem.getAltura() / 8.0f);
	float ymin = p.limite1.y;
	if (((enem.posicion.y - enem.altura / 2.0f) < ymin) && enem.posicion.x >= xmin && enem.posicion.x <= xmax)
		return true;
	return false;
}
bool Interaccion::colision(Enemigo enem, Escenario e)
{
	//Función que manda un bool true si cualquier enemigo ha tocado con el escenario.
	//float xmax = e.pared_dcha.limite2.x - (enem.getAltura() / 8.0f);
	//float xmin = e.pared_izq.limite2.x + (enem.getAltura() / 8.0f);
	float ymin = e.suelo.limite1.y;
	if ((enem.posicion.y - enem.altura / 2.0f) < ymin) //enem.posicion.x <= xmin || enem.posicion.x >= xmax ||
		return true;
	return false;
}
bool Interaccion::colision(Enemigo enem, Jugador j)
{
	//Función que manda un boole true si ha habido contacto entre un enemigo y el jugador de frente. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D pos = j.getPos(); //la posicion de la base del hombre
	float distancia = (enem.getPos() - pos).modulo();
	if ((distancia <= (enem.getAltura()) && (enem.posicion.y >= (j.posicion.y-(j.getAltura()/4.0f)))))
		return true;
	return false;
}
bool Interaccion::colisionEncima(Enemigo enem, Jugador j)
{
	//Función que manda un booleano si ha habido contacto entre un enemigo y el jugador por encima del enemigo. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D pos = j.getPos(); //la posicion de la base del hombre
	float distancia = (enem.getPos() - pos).modulo();
	if (distancia <= (enem.getAltura()) && (enem.posicion.y < (j.posicion.y -(j.getAltura()/4.0f))))//(enem.altura -(j.getAltura()/8.0f))
		return true;
	return false;
}
void Interaccion::rebote(CepaIndia& ind, Plataforma p)
{
	//Función para que las CepasIndias no se puedan salir de las plataformas. Coge sus límites y dice que si sobrepasa estos se quede en el borde y además que vayan al sentido contrario.
	float xmax = p.limite2.x - (ind.getAltura()/8.0f);
	float xmin = p.limite1.x + (ind.getAltura()/8.0f);
	float ymin = p.limite1.y;
	if ((ind.posicion.y > ymin) && ((ind.posicion.y - ind.getAltura()) < ymin))
	{
		if (ind.posicion.x >= xmax)
		{
			ind.posicion.x = xmax;
			ind.velocidad.x = -ind.velocidad.x;
		}
		if (ind.posicion.x <= xmin)
		{
			ind.posicion.x = xmin;
			ind.velocidad.x = -ind.velocidad.x;
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
	float xmax = p.limite2.x - (brit.getAltura()/8.0f);
	float xmin = p.limite1.x + (brit.getAltura() / 8.0f);
	float ymin = p.limite1.y;
	if((brit.posicion.y > ymin) && ((brit.posicion.y - brit.getAltura()) < ymin))
	{
		if (brit.posicion.x > xmax)
		{
			brit.posicion.x = xmax;
			brit.velocidad.x = -2.0f;
		}
		if (brit.posicion.x < xmin)
		{
			brit.posicion.x = xmin;
			brit.velocidad.x = 2.0f;
		}
	}
	//Además como pasaba con el jugador, para que se mantenga encima de la plataforma
	float dist = p.distancia(brit.getPos());
	if ((dist <= (brit.getAltura())) && brit.posicion.x >= xmin && brit.posicion.x <= xmax)
		brit.posicion.y = ymin + brit.getAltura() / 2.0f; //+ brit.getAltura() / 2.0f
}

void Interaccion::rebote(CepaBrasileña& bra, Plataforma p)
{
	//Función para que las CepasBrasileñas no se puedan salir de las plataformas. Coge sus límites y dice que si sobrepasa estos se quede en el borde y además que vayan al sentido contrario.
	float xmax = p.limite2.x - (bra.getAltura() / 8.0f);
	float xmin = p.limite1.x + (bra.getAltura() / 8.0f);
	float ymin = p.limite1.y;
	int SemillaAl = rand();
	srand(time(NULL) * SemillaAl); //Se crea semilla aleatoria para todas las CepasBrasileñas
	int aleatorio, DESDE = 4, HASTA = 10;
	aleatorio = rand() % (HASTA - DESDE + 1) + DESDE; //Se crea el numero aleatorio
	/*if ((bra.posicion.y > ymin) && ((bra.posicion.y - bra.getAltura()) < ymin))
	{
		if (bra.posicion.x >= xmax)
		{
			bra.posicion.x = xmax;
			bra.velocidad.x = -5.0f;
		}
		if (bra.posicion.x <= xmin)
		{
			bra.posicion.x = xmin;
			bra.velocidad.x = 5.0f;
		}
	}*/
	//Además, se le añade a esta Cepa que cuando toque el suelo toque con alturas aleatorias.
	float dist = p.distancia(bra.getPos());
	if ((dist <= bra.getAltura() / 2.0f) && (bra.posicion.y - bra.getAltura()/2.0f) < ymin && bra.posicion.x >= xmin && bra.posicion.x <= xmax)
	{
		bra.posicion.y = ymin + bra.getAltura()/2.0f;
		//if(bra.posicion.x >= (xmin+0.5f) && bra.posicion.x <= (xmax-0.5f))
		bra.saltar((float)aleatorio); //La Cepa salta
	}
}
void Interaccion::rebote(CepaIndia& ind, Escenario e)
{
	//Función para que las CepasIndias no se puedan salir del escenario. Coge sus límites y dice que si sobrepasa estos se quede en el borde y además que vayan al sentido contrario.
	float xmax = e.pared_dcha.limite2.x - (ind.getAltura() / 2.0f);
	float xmin = e.pared_izq.limite2.x + (ind.getAltura() / 2.0f);
	if (ind.posicion.x > xmax)
	{
		ind.posicion.x = xmax;
		ind.velocidad.x = -5.0f;
	}
	if (ind.posicion.x < xmin)
	{
		ind.posicion.x = xmin;
		ind.velocidad.x = 5.0f;
	}
}
void Interaccion::rebote(CepaBritanica& brit, Escenario e)
{
	//Función para que las CepasBritanicas no se puedan salir del escenario. Coge sus límites y dice que si sobrepasa estos se quede en el borde y además que vayan al sentido contrario.
	float xmax = e.pared_dcha.limite2.x - (brit.getAltura() / 2.0f);
	float xmin = e.pared_izq.limite2.x + (brit.getAltura() / 2.0f);;
	if (brit.posicion.x > xmax)
	{
		brit.posicion.x = xmax;
		brit.velocidad.x = -3.0f;
	}
	if (brit.posicion.x < xmin)
	{
		brit.posicion.x = xmin;
		brit.velocidad.x = 3.0f;
	}
}
void Interaccion::rebote(CepaBrasileña& bra, Escenario e)
{
	//Función para que las CepasBritanicas no se puedan salir del escenario. Coge sus límites y dice que si sobrepasa estos se quede en el borde y además que vayan al sentido contrario.
	float xmax = e.pared_dcha.limite2.x - (bra.getAltura() / 2.0f);
	float xmin = e.pared_izq.limite2.x + (bra.getAltura() / 2.0f);;
	if (bra.posicion.x > xmax)
	{
		bra.posicion.x = xmax;
		bra.velocidad.x = -bra.velocidad.x;
	}
	if (bra.posicion.x < xmin)
	{
		bra.posicion.x = xmin;
		bra.velocidad.x = -bra.velocidad.x;
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
	if(murpeq.posicion.y > ymax)
	{
		murpeq.posicion.y = ymax;
		murpeq.velocidad.y = -murpeq.velocidad.y;
	}
	if (murpeq.posicion.y < ymin)
	{
		murpeq.posicion.y = ymin;
		murpeq.velocidad.y = -murpeq.velocidad.y;
	}
	if (murpeq.posicion.x > xmax)
	{
		murpeq.posicion.x = xmax;
		murpeq.velocidad.x = -murpeq.velocidad.x;
	}
	if (murpeq.posicion.x < xmin)
	{
		murpeq.posicion.x = xmin;
		murpeq.velocidad.x = -murpeq.velocidad.x;
	}
}
void Interaccion::rebote(MurcielagoBoss& murboss, Escenario e, Jugador j) // PATRON DE MOVIMIENTO DEL MURCIÉLAGO DIFERETE. SE MUEVE HACIENDO ONDAS
{
	//Función para que el MurcielagoBoss no se puedan salir del escenario. Coge sus límites y dice que si sobrepasa estos se quede en el borde y además que vayan al sentido contrario.
	float xmax_escenario = e.pared_dcha.limite2.x - (murboss.getAltura() / 2.0f);
	float xmin_escenario = e.pared_izq.limite2.x + (murboss.getAltura() / 2.0f);;
	float xmax_jugador = j.getPos().x + 4.0f; // limite relativo al jugador
	float xmin_jugador = j.getPos().x - 4.0f; // lo mismo pero por el otro lado
	static const float posicion_referencia = murboss.getPos().y; // recibe la posicion inicial del enemigo
	static const Vector2D velocidad_referencia = murboss.getVel(); // recibe la velocidad inicial del enemigo
	float ymax = posicion_referencia + 0.5f;
	float ymin = posicion_referencia - 0.5f;
	if (murboss.getDisparoRecibido() == false)
	{
		// limites de movimiento en eje y
		if (murboss.getPos().y > ymax)
		{
			murboss.setPos(murboss.getPos().x, ymax);
			murboss.velocidad.y = -murboss.velocidad.y;
		}
		if (murboss.getPos().y < ymin)
		{
			murboss.setPos(murboss.getPos().x, ymin);
			murboss.velocidad.y = -murboss.velocidad.y;
		}
		// limites relativos a escenario y jugador

		if (murboss.getPos().x > xmax_escenario) // limite max escenario 
		{
			murboss.setPos(xmax_escenario, murboss.getPos().y);
			murboss.velocidad.x = -murboss.velocidad.x;
		}
		if (murboss.getPos().x > xmax_jugador) // limite max jugador
		{
			murboss.setPos(xmax_jugador, murboss.getPos().y);
			murboss.velocidad.x = -murboss.velocidad.x;
		}
		if (murboss.getPos().x < xmin_escenario) // limite min escenario
		{
			murboss.setPos(xmin_escenario, murboss.getPos().y);
			murboss.velocidad.x = -murboss.velocidad.x;
		}
		if (murboss.getPos().x < xmin_jugador) // limite min jugador
		{
			murboss.setPos(xmin_jugador, murboss.getPos().y);
			murboss.velocidad.x = -murboss.velocidad.x;
		}
	}
	// secuencia de movimiento al recibir disparo
	if (murboss.getDisparoRecibido() == true && murboss.getVidas() > 0) // si es disparado
	{
		murboss.setVel(0.0f, murboss.getVelocidadBajada()); // baja
		if (murboss.getPos().y < murboss.getPosicionBajada()) // si llego a la posicion de bajada
		{
			// se queda quieto esperando que le den
			murboss.setPos(murboss.getPos().x, murboss.getPosicionBajada());
			murboss.setVel(0.0f, 0.0f);
		}
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
	Vector2D p1 = d.posicion;
	Vector2D p2 = d.origen;
	aux.setPos(p1.x, p1.y, p2.x, p2.y); //Que coincida con el disparo.
	float dist = aux.distancia(enem.posicion); //para calcular su distancia 
	if (dist < (enem.altura/2.0f))
		return true;
	return false;
}
//Funciones llave
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
bool Interaccion::colision(Llave& b, Escenario e) //Funcion que manda true si hay colision entre bonus y escenario. Mide distancia entre ellas y compara. 
{
	float xmax = e.suelo.limite2.x;
	float xmin = e.suelo.limite1.x;
	if (b.posicion.x + b.getLado() > xmax) {
		b.posicion.x = xmax - b.getLado();
		b.velocidad.x = -4.0f;
	}
	if (b.posicion.x - b.getLado() < xmin) {
		b.posicion.x = xmin + b.getLado();
		b.velocidad.x = 4.0f;
	}
	Vector2D pos = b.getPos();
	pos.y -= b.getLado() / 2;//se le resta el lado para que quede apoyado en a superficie de abajo
	float distancia = e.suelo.distancia(pos);
	if (distancia <= 0.1f) {
		return true;
	}
	return false;
}
void Interaccion::rebote(Llave& b, Escenario e) //Función que gestiona el rebote de cualquier bonus con el escenario
{
	if (Interaccion::colision(b, e.suelo))
	{
		b.velocidad.y = 0;
		b.aceleracion.y = 0;
	}
	float ymin = e.suelo.limite1.y;
	if ((b.posicion.y - b.getLado()) < ymin) b.posicion.y = ymin + b.getLado() / 2;
}
bool Interaccion::colision(Llave b, Jugador j) {
	Vector2D pos = j.getPos(), llave = b.getPos();
	Vector2D aux = pos - llave;
	float distancia = aux.modulo(),altura=j.getAltura(),lado=b.getLado();
	if (distancia <= (lado + altura)/2.0f)
		return true;
	return false;
}
