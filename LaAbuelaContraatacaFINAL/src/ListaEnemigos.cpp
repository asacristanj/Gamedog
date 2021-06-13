#include "ListaEnemigos.h"
#include <time.h>
using namespace std;
ListaEnemigos::ListaEnemigos() //Constructor de ListaEnemigos
{
	numero = 0;
	for (int i = 0; i < MAX_ENEMIGOS; i++)
		lista[i] = 0;
}
bool ListaEnemigos::agregar(Enemigo* enem) //Método para agregar enemigos de manera correcta y ordenada
{
	for (int i = 0; i < numero; i++)
	{
		if (enem == lista[i]) //Si se introduce un enemigo ya hecho no se mete
			return false;
	}
	if (numero < MAX_ENEMIGOS)
		lista[numero++] = enem; // Último puesto sin rellenar
	else
		return false; // Capacidad máxima alcanzada
	return true;
}
void ListaEnemigos::dibuja() //Método para dibujar todos los enemigos
{
	for (int i = 0; i < numero; i++)
		lista[i]->dibuja();
}
void ListaEnemigos::mueve(float t) // Método para mover todos los enemigos
{
	for (int i = 0; i < numero; i++)
		lista[i]->mueve(t);
}
void ListaEnemigos::rebote(Plataforma p) // Método para gestionar la interacción de todos los enemigos con las plataformas
{
	for (int i = numero - 1; i >= 0; i--)
	{
		int tipo = lista[i]->getTipo();
		if (tipo == CEPAINDIA)
		{
			CepaIndia* ind = (CepaIndia*)lista[i];
			Interaccion::rebote(*ind, p); //Se llama al método que gestiona la interacción de la cepa con la plataforma
		}
		if (tipo == CEPABRITANICA)
		{
			CepaBritanica* brit = (CepaBritanica*)lista[i];
			Interaccion::rebote(*brit, p);
		}
		if (tipo == CEPABRASILEÑA)
		{
			CepaBrasileña* bra = (CepaBrasileña*)lista[i];
			Interaccion::rebote(*bra, p);
		}
		if (tipo == CEPACHINA)
		{
			CepaChina* chin = (CepaChina*)lista[i];
			if (Interaccion::colision(*chin, p))
				eliminar(i); //En este caso se quiere que si esta cepa toca la plataforma se elimine
		}
		//No están los murcielagos ya que nunca va a haber colisión entre ellos
	}
}
void ListaEnemigos::rebote(Escenario e) // Método para gestionar la interacción de todos los enemigos con el escenario
{
	for (int i = numero - 1; i >= 0; i--)
	{
		int tipo = lista[i]->getTipo();
		if (tipo == CEPAINDIA)
		{
			CepaIndia* ind = (CepaIndia*)lista[i];
			Interaccion::rebote(*ind, e); //Se llama al método que gestiona la interacción de la cepa con el escenario
		}
		if (tipo == CEPABRITANICA)
		{
			CepaBritanica* brit = (CepaBritanica*)lista[i];
			Interaccion::rebote(*brit, e);
		}
		if (tipo == CEPABRASILEÑA)
		{
			CepaBrasileña* bra = (CepaBrasileña*)lista[i];
			Interaccion::rebote(*bra, e);
			if(Interaccion::colision(*bra, e))
				eliminar(i);
		}
		if (tipo == CEPACHINA)
		{
			CepaChina* chin = (CepaChina*)lista[i];
			if (Interaccion::colision(*chin, e))
				eliminar(i);		
		}
		if (tipo ==  MURCIELAGOPEQUEÑO)
		{
			MurcielagoPequeño* murpeq = (MurcielagoPequeño*)lista[i];
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
void ListaEnemigos::rebote(Jugador& j) // Método para gestionar la interacción de todos los enemigos con el jugador
{
	for (int i = numero - 1; i >= 0; i--)
	{
		int tipo = lista[i]->getTipo();
		if (tipo == CEPAINDIA) //En la CepaIndia se quiere que si el jugador salta por encima del enemigo se elimine este y si choca de frente que muera el jugador
		{
			CepaIndia* ind = (CepaIndia*)lista[i];
			if (Interaccion::colisionEncima(*ind, j))
			{
				int punt = ind->getPunt();
				punt += 20;
				ind->setPunt(punt);
				eliminar(i);
			}
			else if (Interaccion::colision(*ind, j))
			{
				j.setNumBonus(j.getNumBonus() - 1); //si tiene algún bonus se lo quitamos
				if (j.getNumBonus() < 0) {
					j.morir(); //cuando no tenga bonus muere
				}
				else {
					eliminar(i);
				}
			}
		}
		if (tipo == CEPABRITANICA)//En la CepaBritanica se quiere que si el jugador se acerca a una cierta distancia del enemigo este se pare y a los 2 segundos explote. Si el jugador se encuentra en una distancia algo mayor que la anterior, el jugador muere por la explosión, sino sobrevive.
		{
			CepaBritanica* brit = (CepaBritanica*)lista[i];
			static time_t horaInicio = time(NULL); //Se coge hora de inicio 
			const int SEGUNDOS = 2; //Tiempo que tarda en explotar
			time_t horaActual = time(NULL); //Se coge todo el rato la hora actual
			if (Interaccion::ratio(*brit, j)) //El juagdor entra en el ratio de explosión
			{
				if (inicializar_hora_inicio == false) //Si el temporizador ya ha sido usado
				{
					inicializar_hora_inicio = true;
					horaInicio = time(NULL); //Se actualiza hora de inicio para todos los enemigos CepaBritanica
				}
				brit->setVel(0, 0); //El enemigo se para
				if (Interaccion::colision(*brit, j) || Interaccion::colisionEncima(*brit, j)) //Si se tocan también afecta al jugador
				{
					eliminar(i);
					j.setNumBonus(j.getNumBonus() - 1);//disminuir el bonus
					if (j.getNumBonus() < 0) {
						j.morir();
					}
					else {
						eliminar(i);
					}
				}
				else if ((horaActual - horaInicio) >= SEGUNDOS) //Momento de explosión
				{
					if (Interaccion::ratioExplosion(*brit, j)) //Si el jugador está dentro de la explosión
					{
						j.setNumBonus(j.getNumBonus() - 1);//Disminuir el bonus
						if (j.getNumBonus() < 0)
						{
							j.morir();
						}
						else {
							eliminar(i);
						}
					}
				}
			}
			else
			{
				if (inicializar_hora_inicio == true) //El temporizador se ha usado
				{
					if ((horaActual - horaInicio) >= SEGUNDOS)
					{
						int punt = brit->getPunt();
						punt += 30;
						brit->setPunt(punt);
						eliminar(i); //Se elimina el enemigo tras la explosion
						inicializar_hora_inicio = false; //Se marca que se ha usado el temporizador
					}
				}
			}
		}
		if (tipo == CEPABRASILEÑA) //En la CepaBrasileña se quiere que si el jugador salta por encima del enemigo se elimine este y si choca de frente que muera el jugador
		{
			CepaBrasileña* bra = (CepaBrasileña*)lista[i];
			if (Interaccion::colisionEncima(*bra, j))
			{
				int punt = bra->getPunt();
				punt += 25;
				bra->setPunt(punt);
				eliminar(i);
			}
			else if (Interaccion::colision(*bra, j)) 
			{
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
		 if (Interaccion::colision(*chin, j) || Interaccion::colisionEncima(*chin, j)) //Si hay colisión sea cual sea los dos mueren (si el jugador no tiene bonus obviamente)
		 {
			 eliminar(i);
			 j.setNumBonus(j.getNumBonus() - 1);//disminuir el bonus
			 if (j.getNumBonus() < 0) 
			 {
				 j.morir();
			 }
		 }
		}
		if (tipo == MURCIELAGOPEQUEÑO) //En el MurcielagoPEqueño se quiere que si el jugador salta por encima del enemigo se elimine este y si choca de frente que muera el jugador. Además, el Murcielago le disparará una CepaChina cada vez que esten uno encima de otro.
		{
			MurcielagoPequeño* murpeq = (MurcielagoPequeño*)lista[i];
			if (j.getPos().x >= (murpeq->getPos().x - 0.05f) && j.getPos().x <= (murpeq->getPos().x + 0.05f)) //Le disparan cuando estén en el mismo eje X
			{
				CepaChina* c = new CepaChina();
				c->setPos(murpeq->getPos().x, murpeq->getPos().y); //Se dispara desde la posicion del murcielago
				c->setVel(0.0f, murpeq->getVelChina()); //Se coge una velocidad que apunta al jugador dentro de las leyes de la física
				agregar(c);
			}
			if (Interaccion::colisionEncima(*murpeq, j))
			{
				int punt = murpeq->getPunt();
				punt += 35;
				murpeq->setPunt(punt);
				eliminar(i);
			}
			else if (Interaccion::colision(*murpeq, j))
			{
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
	}
}
void ListaEnemigos::reboteBoss(Escenario e, Jugador& j) // Interaccion del boss con escenario y jugador
{
	for (int i = numero - 1; i >= 0; i--)
	{
		int tipo = lista[i]->getTipo();
		if (tipo == MURCIELAGOBOSS)//En el MurcielagoPEqueño se quiere que si el jugador salta por encima del enemigo se elimine este (siempre que no le queden vidas, ya que tiene 3) y si choca de frente que muera el jugador. Además, el Murcielago le disparará una CepaChina cada vez que esten uno encima de otro.
		{
			MurcielagoBoss* murboss = (MurcielagoBoss*)lista[i];
			Interaccion::rebote(*murboss, e, j); // patron de movimiento****

			if (j.getPos().x > (murboss->getPos().x - 0.02f) && j.getPos().x < (murboss->getPos().x + 0.02f)) //Le disparan cuando estén en el mismo eje X
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
					int punt = murboss->getPunt();
					punt += 50;
					murboss->setPunt(punt);
					eliminar(i);// Si no le quedan vidas muere
				}
			}
			else if (Interaccion::colision(*murboss, j))
			{
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
	for (int i = 0; i < numero; i++) // destrucción de esferas contenidas
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

