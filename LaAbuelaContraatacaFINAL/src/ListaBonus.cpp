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
	for (int i = numero - 1; i >= 0; i--) {
		int tipo = lista[i]->getTipo();
		if (tipo == QUIRURGICA) {
			Quirurgica* qui = (Quirurgica*)lista[i];
			Interaccion::rebote(*qui, p);
		}
		if (tipo == MATOCHA) {
			MascarillaTocha* mato = (MascarillaTocha*)lista[i];
			Interaccion::rebote(*mato, p);
		}
		if (tipo == ASTRAZENECA) {
			Astrazeneca* ast = (Astrazeneca*)lista[i];
			Interaccion::rebote(*ast, p);
		}
		if (tipo == JANSSEN) {
			Janssen* jans = (Janssen*)lista[i];
			Interaccion::rebote(*jans, p);
		}
		if (tipo == PFIZER) {
			Pfizer* pfi = (Pfizer*)lista[i];
			Interaccion::rebote(*pfi, p);
		}
		/*if (tipo == SPUTNIK) {
			Sputnik* spu = (Sputnik*)lista[i];
			Interaccion::rebote(*spu, p);
		}*/

	}
}

void ListaBonus::rebote(Escenario e)//elimino los bonuses si tocan el suelo
{
	for (int i = numero-1; i >=0; i--) {
		int tipo = lista[i]->getTipo();
		if (tipo == QUIRURGICA) {
			Quirurgica* qui = (Quirurgica*)lista[i];
			if (Interaccion::colision(*qui, e)) {
				eliminar(i);
			}
		}
		if (tipo == MATOCHA) {
			MascarillaTocha* mato = (MascarillaTocha*)lista[i];
			if (Interaccion::colision(*mato, e)) {
				eliminar(i);
			}
		}
		if (tipo == ASTRAZENECA) {
			Astrazeneca* ast = (Astrazeneca*)lista[i];
			if (Interaccion::colision(*ast, e)) { 
				eliminar(i); 
			}
		}
		if (tipo == JANSSEN) {
			Janssen* jans = (Janssen*)lista[i];
			if (Interaccion::colision(*jans, e)) {
				eliminar(i);
			}
		}
		if (tipo == PFIZER) {
			Pfizer* pfi = (Pfizer*)lista[i];
			if (Interaccion::colision(*pfi, e)) {
				eliminar(i);
			}
		}
		/*if (tipo == SPUTNIK) {
			Sputnik* spu = (Sputnik*)lista[i];
			if (Interaccion::colision(*spu, e)) {
				eliminar(i);
			}
		}*/
		
	}
}
void ListaBonus::rebote(Jugador& j)
{
	
	for (int i = numero - 1; i >= 0; i--)
	{
		int tipo = lista[i]->getTipo();
		static time_t horaInicio = time(NULL);
		const int SEGUNDOS = 10; //Tiempo que dura el bonus
		time_t horaActual = time(NULL);
		//Bonus* bon = lista[i];
		//if (Interaccion::colision(*bon, j)) {
			//eliminar(i);
		//}	
		if (tipo == QUIRURGICA) {
			Quirurgica* q = (Quirurgica*)lista[i];
			if (Interaccion::colision(*q, j)) {
				Factoria::CogerQuirurgica(j);
				eliminar(i);
			}
		}
		if (tipo == MATOCHA) {
			MascarillaTocha* m = (MascarillaTocha*)lista[i];
			if (Interaccion::colision(*m, j)) {
				Factoria::CogerMascarillaTocha(j);
				eliminar(i);
			}
		}
		if (tipo == ASTRAZENECA) {
			Astrazeneca* a = (Astrazeneca*)lista[i];
			if (Interaccion::colision(*a, j)) {
				Factoria::CogerAstrazeneca(j);
				eliminar(i);
				if (inicializar_hora_inicio == false)
				{
					inicializar_hora_inicio = true;
					horaInicio = time(NULL);
				}
				if((horaActual - horaInicio) >= SEGUNDOS)
				{
				j.setImpulso(10.0f);
				}
			}
			else
			{
				if (inicializar_hora_inicio == true)
				{
					if ((horaActual - horaInicio) >= SEGUNDOS)
					{
						inicializar_hora_inicio = false;
					}
				}
			}
		}
		
		if (tipo == JANSSEN) {
			Janssen* jan = (Janssen*)lista[i];
			if (Interaccion::colision(*jan, j)) {
				Factoria::CogerJanssen(j);
				eliminar(i);
				if (inicializar_hora_inicio == false)
				{
					inicializar_hora_inicio = true;
					horaInicio = time(NULL);
				}
			}
		}
		if (tipo == PFIZER) {
			Pfizer* p = (Pfizer*)lista[i];
			if(Interaccion::colision(*p,j)){
				Factoria::CogerPfizer(j);
				eliminar(i);
				if (inicializar_hora_inicio == false)
				{
					inicializar_hora_inicio = true;
					horaInicio = time(NULL);
				}
			}
		}
	}
 }
/*void ListaBonus::rebote(ListaEnemigos& e, Jugador& j) {
	for (int i = numero - 1; i >= 0; i--) {
		int tipo = lista[i]->getTipo();
		if (tipo == SPUTNIK) {
			Sputnik* s = (Sputnik*)lista[i];
			if (Interaccion::colision(*s, j)) {
				Factoria::CogerSputnik(e, j);
				eliminar(i);
			}
		}
	}
}*/

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