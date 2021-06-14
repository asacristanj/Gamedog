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
void ListaBonus::rebote(Plataforma p)//gestiono los rebotes de los diferentes bonus con las plataformas 
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
	}
}

void ListaBonus::rebote(Escenario e)//gestiono el rebote con el escenario de los bonus, que en esta caso es eliminarse si toca con el suelo
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
	}
}
void ListaBonus::rebote(Jugador& j)//gestiono lo que pasa cuando el jugador entra en contacto con el bonus
{
	
	for (int i = numero - 1; i >= 0; i--)
	{
		int tipo = lista[i]->getTipo();
		if (tipo == QUIRURGICA) {
			Quirurgica* q = (Quirurgica*)lista[i];
			if (Interaccion::colision(*q, j)) {
				Factoria::CogerQuirurgica(j);//funcion que gobierna lo que pasa al coger la quirurgica
				j.setPuntuacion(5); // +5 puntos
				play("sonidos/bonus.wav");
				eliminar(i);
			}
		}
		if (tipo == MATOCHA) {
			MascarillaTocha* m = (MascarillaTocha*)lista[i];
			if (Interaccion::colision(*m, j)) {
				Factoria::CogerMascarillaTocha(j);//funcion que gobierna lo que pasa al coger la mascarilla tocha
				j.setPuntuacion(10); // +10 puntos
				play("sonidos/bonus.wav");
				eliminar(i);
			}
		}
		if (tipo == ASTRAZENECA) 
		{
			Astrazeneca* a = (Astrazeneca*)lista[i];
			if (Interaccion::colision(*a, j))
			{
				Factoria::CogerAstrazeneca(j);//funcion que gobierna lo que pasa al coger la astrazeneca
				j.setPuntuacion(15); // +15 puntos
				play("sonidos/bonus.wav");
				eliminar(i);
				if (j.getAstraActivo() == false)//incorporacion del temporizador al bonus correspondiente
				{
					j.setAstraActivo(true);
					j.sethInicioAstra(time(NULL));
				}
			}
		}
		if (tipo == JANSSEN) 
		{
			Janssen* jan = (Janssen*)lista[i];
			if (Interaccion::colision(*jan, j)) {
				Factoria::CogerJanssen(j);//funcion que gobierna lo que pasa al coger la janssen
				j.setPuntuacion(15); // +15 puntos
				eliminar(i);
				play("sonidos/bonus.wav");
				if (j.getJanssenActivo() == false)//incorporacion del temporizador al bonus correspondiente
				{
					j.setJanssenActivo(true);
					j.sethInicioJanssen(time(NULL));
				}
			}
		}
		if (tipo == PFIZER) 
		{
			Pfizer* p = (Pfizer*)lista[i];
			if(Interaccion::colision(*p,j)){
				Factoria::CogerPfizer(j);//funcion que gobierna lo que pasa al coger la pfizer
				j.setPuntuacion(15); // +15 puntos
				eliminar(i);
				play("sonidos/bonus.wav");
				if (j.getPfizerActivo() == false)//incorporacion del temporizador al bonus correspondiente
				{
					j.setPfizerActivo(true);
					j.sethInicioPfizer(time(NULL));
				}
			}
		}
	}
 }
Bonus* ListaBonus::colision(Jugador& j)//funcion que controla si el jugador colisiona con el bonus
{
	for (int i = 0; i < numero; i++)
	{
		if (Interaccion::colision(*(lista[i]), j))
			return lista[i];
	}
	return 0; //no hay colisión
}
void ListaBonus::destruirContenido()//destruir correctamente los bonus del juego
{
	for (int i = 0; i < numero; i++) // destrucción de bonus contenidas
		delete lista[i];
	numero = 0; // inicializa lista
}
Bonus* ListaBonus:: operator[] (int i) //gestion del operador corchete
{
	if (i >= numero)//si me paso, devuelvo la ultima
		i = numero - 1;
	if (i < 0) //si el indice es negativo, devuelvo la primera
		i = 0;
	return lista[i];
}
void ListaBonus::eliminar(int index)//funcion que reordena correctamente el array tras eliminar el bonus de la lista
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