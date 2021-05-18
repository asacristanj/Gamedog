#include "ListaEnemigos.h"
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
	for (int i = 0; i < numero; i++)
		Interaccion::rebote(*(lista[i]), p);
}
void ListaEnemigos::rebote(Escenario e)
{
	for (int i = 0; i < numero; i++)
		Interaccion::rebote(*(lista[i]), e);
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
/*Enemigo* ListaEnemigos::colision(DisparoGel& d){
	for (int i=0;i < numero; i++) {
		if (Interaccion::colision(d, (*(lista[i])))) {
			return lista[i];
		}
	}
	return 0;
}
*/
void ListaEnemigos::colision(ListaDisparosGel d) {
	//Funcion que recorre la listas de disparos y enemigos y borra los enemigos cuando detecta una colision
	for (int i = 0; i < numero; i++) {
		for (int j = 0; j < d.numero; j++) {
			if (Interaccion::colision(*(d.lista[i]), *(lista[j]))) {
				//al detectar colision entre la bola y el enemigo eliminamos el enemigo
				delete lista[i];
				numero--;
			}
		}
	}
}
Enemigo* ListaEnemigos::operator [](int i)
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

