#include "ListaEnemigos.h"
#include <time.h>
ListaEnemigos::ListaEnemigos()
{
	numero = 0;
	for (int i = 0; i < MAX_ENEMIGOS; i++)
		lista[i] = 0;
}
bool ListaEnemigos::agregar(Enemigo* enem)
{
	for (int i = 0; i < numero; i++)
	{
		if (enem == lista[i])
			return false;
	}
	if (numero < MAX_ENEMIGOS)
		lista[numero++] = enem; // último puesto sin rellenar
	else
		return false; // capacidad máxima alcanzada
	return true;
}
void ListaEnemigos::dibuja()
{
	for (int i = 0; i < numero; i++)
		lista[i]->dibuja();
}
void ListaEnemigos::mueve(float t)
{
	for (int i = 0; i < numero; i++)
		lista[i]->mueve(t);
}
void ListaEnemigos::rebote(Plataforma p)
{
	for (int i = numero - 1; i >= 0; i--)
	{
		int tipo = lista[i]->getTipo();
		if (tipo == CEPAINDIA)
		{
			CepaIndia* ind = (CepaIndia*)lista[i];
			Interaccion::rebote(*ind, p);
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
			if (Interaccion::rebote(*chin, p))
				eliminar(i);
		}
	}
}
void ListaEnemigos::rebote(Escenario e)
{
	for (int i = numero - 1; i >= 0; i--)
	{
		int tipo = lista[i]->getTipo();
		if (tipo == CEPAINDIA)
		{
			CepaIndia* ind = (CepaIndia*)lista[i];
			Interaccion::rebote(*ind, e);
		}
		if (tipo == CEPABRITANICA)
		{
			CepaBritanica* brit = (CepaBritanica*)lista[i];
			Interaccion::rebote(*brit, e);
		}
		if (tipo == CEPABRASILEÑA)
		{
			CepaBrasileña* bra = (CepaBrasileña*)lista[i];
			if (Interaccion::rebote(*bra, e))
				eliminar(i);
		}
		if (tipo == CEPACHINA)
		{
			CepaChina* chin = (CepaChina*)lista[i];
			if (Interaccion::rebote(*chin, e))
				eliminar(i);
		}
	}
}
void ListaEnemigos::rebote(Jugador& j)
{
	for (int i = numero - 1; i >= 0; i--)
	{
		int tipo = lista[i]->getTipo();
		if (tipo == CEPAINDIA)
		{
			CepaIndia* ind = (CepaIndia*)lista[i];
			if (Interaccion::colisionEncima(*ind, j))
				eliminar(i);
			else if (Interaccion::colision(*ind, j))
				j.morir();
		}
		if (tipo == CEPABRITANICA)
		{
			CepaBritanica* brit = (CepaBritanica*)lista[i];
			static time_t horaInicio = time(NULL);
			const int SEGUNDOS = 2; //Tiempo que tarda en explotar
			time_t horaActual = time(NULL);
			if (Interaccion::ratio(*brit, j))
			{
				if (inicializar_hora_inicio == false)
				{
					inicializar_hora_inicio = true;
					horaInicio = time(NULL);
				}
				brit->setVel(0, 0);
				if (Interaccion::colision(*brit, j) || Interaccion::colisionEncima(*brit, j))
				{
					eliminar(i);
					j.morir();
				}
				else if ((horaActual - horaInicio) >= SEGUNDOS)
				{
					if (Interaccion::ratioExplosion(*brit, j))
						j.morir();
				}
			}
			else
			{
				if (inicializar_hora_inicio == true)
				{
					if ((horaActual - horaInicio) >= SEGUNDOS)
					{
						eliminar(i);
						inicializar_hora_inicio = false;
					}
				}
			}
		}
		if (tipo == CEPABRASILEÑA)
		{
			CepaBrasileña* bra = (CepaBrasileña*)lista[i];
			if (Interaccion::colisionEncima(*bra, j))
				eliminar(i);
			else if (Interaccion::colision(*bra, j))
				j.morir();
		}
		if (tipo == CEPACHINA)
		{
			CepaChina* chin = (CepaChina*)lista[i];
		 if (Interaccion::colision(*chin, j) || Interaccion::colisionEncima(*chin, j))
			j.morir();
		}
	}
}
Enemigo* ListaEnemigos::colision(Jugador& j)
{
	for (int i = 0; i < numero; i++)
	{
		if (Interaccion::colision(*(lista[i]), j))
		return lista[i];
	}
	return 0; //no hay colisión
}
Enemigo* ListaEnemigos::colisionEncima(Jugador& j)
{
	for (int i = 0; i < numero; i++)
	{
		if (Interaccion::colisionEncima(*(lista[i]), j))
			return lista[i];
	}
	return 0; //no hay colisión
}
Enemigo* ListaEnemigos:: operator[] (int i)
{
	if (i >= numero)//si me paso, devuelvo la ultima
		i = numero - 1;
	if (i < 0) //si el indice es negativo, devuelvo la primera
		i = 0;
	return lista[i];
}
void ListaEnemigos::destruirContenido()
{
	for (int i = 0; i < numero; i++) // destrucción de esferas contenidas
		delete lista[i];
	numero = 0; // inicializa lista
}
void ListaEnemigos::eliminar(int index)
{
	if ((index < 0) || (index >= numero))
		return;
	delete lista[index];
	numero--;
	for (int i = index; i < numero; i++)
		lista[i] = lista[i + 1];
}
void ListaEnemigos::eliminar(Enemigo* enem)
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

