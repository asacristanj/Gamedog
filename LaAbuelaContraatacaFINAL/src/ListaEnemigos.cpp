#include "ListaEnemigos.h"
#include <time.h>
using ETSIDI::play;

ListaEnemigos::ListaEnemigos() //Constructor de ListaEnemigos
{
	numero = 0;
	for (int i = 0; i < MAX_ENEMIGOS; i++)
		lista[i] = 0;
}
bool ListaEnemigos::agregar(Enemigo* enem) //M�todo para agregar enemigos de manera correcta y ordenada
{
	for (int i = 0; i < numero; i++)
	{
		if (enem == lista[i]) //Si se introduce un enemigo ya hecho no se mete
			return false;
	}
	if (numero < MAX_ENEMIGOS)
		lista[numero++] = enem; // �ltimo puesto sin rellenar
	else
		return false; // Capacidad m�xima alcanzada
	return true;
}
void ListaEnemigos::dibuja() //M�todo para dibujar todos los enemigos
{
	for (int i = 0; i < numero; i++)
		lista[i]->dibuja();
}
void ListaEnemigos::mueve(float t) // M�todo para mover todos los enemigos
{
	for (int i = 0; i < numero; i++)
		lista[i]->mueve(t);
}
void ListaEnemigos::rebote(Plataforma p) // M�todo para gestionar la interacci�n de todos los enemigos con las plataformas
{
	for (int i = numero - 1; i >= 0; i--)
	{
		int tipo = lista[i]->getTipo();
		if (tipo == CEPAINDIA)
		{
			CepaIndia* ind = (CepaIndia*)lista[i];
			Interaccion::rebote(*ind, p); //Se llama al m�todo que gestiona la interacci�n de la cepa con la plataforma
		}
		if (tipo == CEPABRITANICA)
		{
			CepaBritanica* brit = (CepaBritanica*)lista[i];
			Interaccion::rebote(*brit, p);
		}
		if (tipo == CEPABRASILE�A)
		{
			CepaBrasile�a* bra = (CepaBrasile�a*)lista[i];
			Interaccion::rebote(*bra, p);
		}
		if (tipo == CEPACHINA)
		{
			CepaChina* chin = (CepaChina*)lista[i];
			if (Interaccion::colision(*chin, p)) {
				eliminar(i); //En este caso se quiere que si esta cepa toca la plataforma se elimine
			}
			
		}
		//No est�n los murcielagos ya que nunca va a haber colisi�n entre ellos
	}
}
void ListaEnemigos::rebote(Escenario e) // M�todo para gestionar la interacci�n de todos los enemigos con el escenario
{
	for (int i = numero - 1; i >= 0; i--)
	{
		int tipo = lista[i]->getTipo();
		if (tipo == CEPAINDIA)
		{
			CepaIndia* ind = (CepaIndia*)lista[i];
			Interaccion::rebote(*ind, e); //Se llama al m�todo que gestiona la interacci�n de la cepa con el escenario
		}
		if (tipo == CEPABRITANICA)
		{
			CepaBritanica* brit = (CepaBritanica*)lista[i];
			Interaccion::rebote(*brit, e);
		}
		if (tipo == CEPABRASILE�A)
		{
			CepaBrasile�a* bra = (CepaBrasile�a*)lista[i];
			Interaccion::rebote(*bra, e);
			if(Interaccion::colision(*bra, e))
				eliminar(i);
		}
		if (tipo == CEPACHINA)
		{
			CepaChina* chin = (CepaChina*)lista[i];
			if (Interaccion::colision(*chin, e)) {
				play("sonidos/muerte_enemigo.mp3");
				eliminar(i);
			}
					
		}
		if (tipo ==  MURCIELAGOPEQUE�O)
		{
			MurcielagoPeque�o* murpeq = (MurcielagoPeque�o*)lista[i];
			Interaccion::rebote(*murpeq, e);
		}
		/*
		if (tipo == MURCIELAGOBOSS)
		{
			MurcielagoBoss* murboss = (MurcielagoBoss*)lista[i];
			Interaccion::rebote(*murboss, e);
		}
		*/
	}
}
void ListaEnemigos::rebote(Jugador& j) // M�todo para gestionar la interacci�n de todos los enemigos con el jugador
{
	for (int i = numero - 1; i >= 0; i--)
	{
		int tipo = lista[i]->getTipo();
		if (tipo == CEPAINDIA) //En la CepaIndia se quiere que si el jugador salta por encima del enemigo se elimine este y si choca de frente que muera el jugador
		{
			CepaIndia* ind = (CepaIndia*)lista[i];
			if (Interaccion::colisionEncima(*ind, j))
			{
				play("sonidos/muerte_enemigo.mp3");
				j.setPuntuacion(20); // +20 puntos
				eliminar(i);
			}
			else if (Interaccion::colision(*ind, j))
			{
				play("sonidos/caida.mp3");
				j.setNumBonus(j.getNumBonus() - 1); //si tiene alg�n bonus se lo quitamos
				if (j.getNumBonus() < 0) {
					j.morir(); //cuando no tenga bonus muere
				}
				else {
					eliminar(i);
				}
			}
		}
		if (tipo == CEPABRITANICA)//En la CepaBritanica se quiere que si el jugador se acerca a una cierta distancia del enemigo este se pare y a los 2 segundos explote. Si el jugador se encuentra en una distancia algo mayor que la anterior, el jugador muere por la explosi�n, sino sobrevive.
		{
			CepaBritanica* brit = (CepaBritanica*)lista[i];
			static time_t horaInicio = time(NULL); //Se coge hora de inicio 
			const int SEGUNDOS = 2; //Tiempo que tarda en explotar
			time_t horaActual = time(NULL); //Se coge todo el rato la hora actual
			if (Interaccion::ratio(*brit, j)) //El juagdor entra en el ratio de explosi�n
			{
		
				if (brit->getInicializarHora() == false) //Si el temporizador ya ha sido usado
				{
					brit->setInicializarHora(true);
					horaInicio = time(NULL); //Se actualiza hora de inicio para todos los enemigos CepaBritanica
				}
				brit->setVel(0, 0); //El enemigo se para
				
				if (Interaccion::colision(*brit, j) || Interaccion::colisionEncima(*brit, j)) //Si se tocan tambi�n afecta al jugador
				{
					play("sonidos/caida.mp3");
					j.setNumBonus(j.getNumBonus() - 1);//disminuir el bonus
					if (j.getNumBonus() < 0) 
					{
						j.morir();
					}
					eliminar(i);
				}
				else if ((horaActual - horaInicio) >= SEGUNDOS) //Momento de explosi�n
				{
	
					if (Interaccion::ratioExplosion(*brit, j)) //Si el jugador est� dentro de la explosi�n
					{
						play("sonidos/caida.mp3");
						j.setNumBonus(j.getNumBonus() - 1);//Disminuir el bonus
						if (j.getNumBonus() < 0)
						{
							j.morir();
						}
					}
					else {
						play("sonidos/muerte_enemigo.mp3");
						j.setPuntuacion(30); // +30 puntos
					}
					eliminar(i);
						
				}
			}
			else
			{
				if (brit->getInicializarHora() == true) //El temporizador se ha usado
				{

					if ((horaActual - horaInicio) >= SEGUNDOS)
					{
						play("sonidos/explosion.mp3");
						if (Interaccion::ratioExplosion(*brit, j))
						{
							play("sonidos/caida.mp3");
							j.setNumBonus(j.getNumBonus() - 1);//Disminuir el bonus
							if (j.getNumBonus() < 0)
							{
								j.morir();
							}
						}
						else
						{
							play("sonidos/muerte_enemigo.mp3");
							j.setPuntuacion(30); // +30 puntos
						}
							
						
						eliminar(i); //Se elimina el enemigo tras la explosion					
						brit->setInicializarHora(false); //Se marca que se ha usado el temporizador
					}
				}
			}
		}
		if (tipo == CEPABRASILE�A) //En la CepaBrasile�a se quiere que si el jugador salta por encima del enemigo se elimine este y si choca de frente que muera el jugador
		{
			CepaBrasile�a* bra = (CepaBrasile�a*)lista[i];
			if (Interaccion::colisionEncima(*bra, j))
			{
				play("sonidos/muerte_enemigo.mp3");
				j.setPuntuacion(25); // +25 puntos
				eliminar(i);
			}
			else if (Interaccion::colision(*bra, j)) 
			{
				play("sonidos/caida.mp3");
				j.setNumBonus(j.getNumBonus() - 1);
				if (j.getNumBonus() < 0) 
				{
					j.morir();
				}
				else {
					eliminar(i);
				}
			}
		}
		if (tipo == CEPACHINA)//En la CepaChina se quiere que si el jugador toca el enemigo los 2 mueran
		{
			CepaChina* chin = (CepaChina*)lista[i];
		    if (Interaccion::colision(*chin, j) || Interaccion::colisionEncima(*chin, j)) //Si hay colisi�n sea cual sea los dos mueren (si el jugador no tiene bonus obviamente)
		    {
				play("sonidos/caida.mp3");
			    eliminar(i);
			    j.setNumBonus(j.getNumBonus() - 1);//disminuir el bonus
			     if (j.getNumBonus() < 0) 
			     {
				     j.morir();
			     }
		    }
		}
		if (tipo == MURCIELAGOPEQUE�O) //En el MurcielagoPEque�o se quiere que si el jugador salta por encima del enemigo se elimine este y si choca de frente que muera el jugador. Adem�s, el Murcielago le disparar� una CepaChina cada vez que esten uno encima de otro.
		{
			MurcielagoPeque�o* murpeq = (MurcielagoPeque�o*)lista[i];
			Vector2D pos= murpeq->getPos();
			if ((pos.x > 7.95f && pos.x < 8.00f) || (pos.x > 4.95f && pos.x < 5.00f) || (pos.x < -7.95f && pos.x > -8.00f) || (pos.x < -4.95f && pos.x > -5.00f)) //Le disparan cuando est�n en el mismo eje X //j.getPos().x >= (murpeq->getPos().x - 0.05f) && j.getPos().x <= (murpeq->getPos().x + 0.05f)
			{
				CepaChina* c = new CepaChina();
				c->setPos(murpeq->getPos().x, murpeq->getPos().y); //Se dispara desde la posicion del murcielago
				c->setVel(0.0f, murpeq->getVelChina()); //Se coge una velocidad que apunta al jugador dentro de las leyes de la f�sica //murpeq->getVelChina()
				agregar(c);
			}
			//(pos.x > 7.45f && pos.x < 7.50f) || (pos.x > 3.95f && pos.x < 4.00f) || (pos.x > -1.05f && pos.x < 1.00f)|| (pos.x < -6.95f && pos.x > -7.00f) || (pos.x < -3.95f && pos.x > -4.00f)
			if (Interaccion::colisionEncima(*murpeq, j))
			{
				play("sonidos/muerte_enemigo.mp3");
				j.setPuntuacion(35); // +35 puntos
				eliminar(i);
			}
			else if (Interaccion::colision(*murpeq, j))
			{
				play("sonidos/caida.mp3");
				j.setNumBonus(j.getNumBonus() - 1);
				if (j.getNumBonus() < 0) 
				{
					j.morir();
				}
				else 
				{
					eliminar(i);
				}
			}
		}
	}
}
void ListaEnemigos::reboteBoss(Escenario e, Jugador& j) // Interaccion del boss con escenario y jugador;;
{
	for (int i = numero - 1; i >= 0; i--)
	{
		int tipo = lista[i]->getTipo();
		if (tipo == MURCIELAGOBOSS)//En el MurcielagoPEque�o se quiere que si el jugador salta por encima del enemigo se elimine este (siempre que no le queden vidas, ya que tiene 3) y si choca de frente que muera el jugador. Adem�s, el Murcielago le disparar� una CepaChina cada vez que esten uno encima de otro.
		{
			MurcielagoBoss* murboss = (MurcielagoBoss*)lista[i];
			Interaccion::rebote(*murboss, e, j); // patron de movimiento****
			float pos_mur = murboss->getPos().x;

			if (((pos_mur > 7.97f && pos_mur < 8.00f) || (pos_mur > 5.97f && pos_mur < 6.00f) || (pos_mur > 3.97f && pos_mur < 4.00f) ||
				(pos_mur > 1.97f && pos_mur < 2.00f) || (pos_mur > -0.03f && pos_mur < 0.00f) || (pos_mur < -1.97f && pos_mur > -2.00f) ||
				(pos_mur < -3.97f && pos_mur > -4.00f) || (pos_mur < -5.97f && pos_mur > -6.00f) || (pos_mur < -7.97f && pos_mur > -8.00f)) &&
				murboss->getDisparoRecibido() == false)
			{
				CepaChina* c = new CepaChina();
				c->setPos(murboss->getPos().x, murboss->getPos().y);
				c->setVel(0.0f, murboss->getVelChina());
				agregar(c);
			}
			if (Interaccion::colisionEncima(*murboss, j))
			{
				j.setPos(j.getPos().x, murboss->getPos().y + murboss->getAltura());
				j.setVel(j.getVel().x, j.getVelocidadRebote()); // el jugador rebota al pisar el boss
				if (murboss->getVidas() > 1) // Le queda al menos una vida
				{
					murboss->setPisoton(true); // murcielago pisado
					murboss->setVidas(-1); // Resto una vida
				}
				else
				{
					play("sonidos/muerte_enemigo.mp3");
					j.setPuntuacion(50); // +50 puntos
					eliminar(i);// Si no le quedan vidas muere
				}
			}
			else if (Interaccion::colision(*murboss, j))
			{
				play("sonidos/caida.mp3");
				j.setNumBonus(j.getNumBonus() - 1);
				if (j.getNumBonus() < 0) {
					j.morir();
				}
				else {
					eliminar(i);
				}
			}
		}
	}
}
Enemigo* ListaEnemigos:: operator[] (int i) //Funcion que ajusta el simbolo [] para nuestro caso
{
	if (i >= numero)//Si me paso, devuelvo la ultima
		i = numero - 1;
	if (i < 0) //Si el indice es negativo, devuelvo la primera
		i = 0;
	return lista[i];
}
void ListaEnemigos::destruirContenido() //Funcion para eliminar enemigos correctamente
{
	for (int i = 0; i < numero; i++) // destrucci�n de esferas contenidas
		delete lista[i];
	numero = 0; // inicializa lista
}
void ListaEnemigos::eliminar(int index)//Funcion para eliminar enemigos correctamente del vector de enemigos
{
	if ((index < 0) || (index >= numero))
		return;
	delete lista[index];
	numero--;
	for (int i = index; i < numero; i++)
		lista[i] = lista[i + 1];
}
void ListaEnemigos::eliminar(Enemigo* enem) // Funcion para eliminar cualquier enemigo correctamente
{
	for (int i = 0; i < numero; i++)
		if (lista[i] == enem)
		{
			eliminar(i);
			return;
		}
}
ListaEnemigos :: ~ListaEnemigos()
{

}

