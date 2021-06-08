#include "ListaDisparosGel.h"
ListaDisparosGel::ListaDisparosGel()
{
	numero = 0;
	for (int i = 0; i < MAX_DISPAROS; i++)
		lista[i] = 0;
}
bool ListaDisparosGel::agregar(DisparoGel* d)
{
	for (int i = 0; i < numero; i++)
	{
		if (d == lista[i])
			return false;
	}
	if (numero < MAX_DISPAROS)
		lista[numero++] = d; // último puesto sin rellenar
	else
		return false; // capacidad máxima alcanzada
	return true;
}
void ListaDisparosGel::dibuja()
{
	for (int i = 0; i < numero; i++)
	{
		lista[i]->dibuja();
	}
}
void ListaDisparosGel::mueve(float t)
{
	for (int i = 0; i < numero; i++)
		lista[i]->mueve(t);
}
void ListaDisparosGel::colision(Plataforma p)
{
	for (int i = 0; i < numero; i++)
		if (Interaccion::colision(*(lista[i]), p))
		{
			//eliminamos el disparo al impactar con la plataforma
			//delete lista[i];
			eliminar(i);
		}
}
void ListaDisparosGel::colision(Escenario e)
{
	for (int i = 0; i < numero; i++)
		if (Interaccion::colision(*(lista[i]), e))
		{
			//eliminamos el disparo cuando se impacta con la pared
			//delete lista[i];
			eliminar(i);
			numero--;
		}
}
DisparoGel* ListaDisparosGel:: operator[] (int i)
{
	if (i >= numero)//si me paso, devuelvo la ultima
		i = numero - 1;
	if (i < 0) //si el indice es negativo, devuelvo la primera
		i = 0;
	return lista[i];
}
void ListaDisparosGel::destruirContenido()
{
	for (int i = 0; i < numero; i++) // destrucción de esferas contenidas
		delete lista[i];
	numero = 0; // inicializa lista
}
void ListaDisparosGel::eliminar(int index)
{
	if ((index < 0) || (index >= numero))
		return;
	delete lista[index];
	numero--;
	for (int i = index; i < numero; i++)
		lista[i] = lista[i + 1];
}
void ListaDisparosGel::eliminar(DisparoGel* d)
{
	for (int i = 0; i < numero; i++)
		if (lista[i] == d)
		{
			eliminar(i);
			return;
		}
}
ListaDisparosGel :: ~ListaDisparosGel()
{

}