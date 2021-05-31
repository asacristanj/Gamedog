#include "ListaBonus.h"
#include <time.h>
ListaBonus::ListaBonus()
{
	numero = 0;
	for (int i = 0; i < MAX_BONUS; i++)
		lista[i] = 0;
}
bool ListaBonus::agregar(Bonus* b)
{
	for (int i = 0; i < numero; i++)
	{
		if (b == lista[i])
			return false;
	}
	if (numero < MAX_BONUS)
		lista[numero++] = b; // último puesto sin rellenar
	else
		return false; // capacidad máxima alcanzada
	return true;
}
void ListaBonus::dibuja()
{
	for (int i = 0; i < numero; i++)
		lista[i]->dibuja();
}
void ListaBonus::mueve(float t)
{
	for (int i = 0; i < numero; i++)
		lista[i]->mueve(t);
}
void ListaBonus::rebote(Plataforma p)
{
	for (int i = numero - 1; i >= 0; i--)
	{
		Bonus* bon = lista[i];
		Interaccion::rebote(*bon, p);
	}
}

void ListaBonus::rebote(Escenario e)
{
	for (int i = 0; i < numero; i++)
		Interaccion::rebote(*(lista[i]), e);
}
void ListaBonus::rebote(Jugador& j)
{
	for (int i = numero - 1; i >= 0; i--)
	{
		int tipo = lista[i]->getTipo();
		Bonus* bon = lista[i];
		if (Interaccion::colision(*bon, j)) {
			eliminar(i);
		}
		if (tipo==QUIRURGICA) {
			Factoria::CogerQuirurgica(j);
		}
		if (tipo == MATOCHA) {
			Factoria::CogerMascarillaTocha(j);
		}
	
	}
 }
void ListaBonus::accionbonus(Jugador j, Bonus b) {//accion que recoge lo que pasa con el jugador al interactuar con los diferentes bonus
	static time_t horaInicioBonus = time(NULL);
	const int SEGUNDOS = 10; //Tiempo que dura el bonus
	time_t horaActualBonus = time(NULL);
	for (int i = numero - 1; i >= 0; i--) {
		int tipo = lista[i]->getTipo();
		if (tipo == ASTRAZENECA && Interaccion::colision(b,j)){//salto el doble
			j.salto(38.0f);
		}
		if (tipo == JANSSEN && Interaccion::colision(b, j)) {//25% mitad velocidad , 25% nada y 50% doble velocidad
			int azar = rand() / (float)RAND_MAX;
			if (azar <=25) {
				j.setVelx(j.getVel().x / 2);
			}
			if (azar >=50) {
				j.setVelx(j.getVel().x * 2);
			}
		}
		if (tipo == SPUTNIK && Interaccion::colision(b, j)) {//eres invencible y pegas con un baston

		}
		if (tipo == PFIZER && Interaccion::colision(b, j)) {//aumenta el doble de la velocidad del jugador y eres invencible x tiempo
			j.setVelx(j.getVel().x*2);
		}
	}
}

Bonus* ListaBonus::colision(Jugador& j)
{
	for (int i = 0; i < numero; i++)
	{
		if (Interaccion::colision(*(lista[i]), j))
			return lista[i];
	}
	return 0; //no hay colisión
}
void ListaBonus::destruirContenido()
{
	for (int i = 0; i < numero; i++) // destrucción de bonus contenidas
		delete lista[i];
	numero = 0; // inicializa lista
}
Bonus* ListaBonus:: operator[] (int i)
{
	if (i >= numero)//si me paso, devuelvo la ultima
		i = numero - 1;
	if (i < 0) //si el indice es negativo, devuelvo la primera
		i = 0;
	return lista[i];
}
void ListaBonus::eliminar(int index)
{
	if ((index < 0) || (index >= numero))
		return;
	delete lista[index];
	numero--;
	for (int i = index; i < numero; i++)
		lista[i] = lista[i + 1];
}
void ListaBonus::eliminar(Bonus* b)
{
	for (int i = 0; i < numero; i++)
		if (lista[i] == b)
		{
			eliminar(i);
			return;
		}
}
ListaBonus:: ~ListaBonus()
{

}