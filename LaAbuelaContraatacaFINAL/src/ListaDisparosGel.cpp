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
			delete lista[i];
		}
}
void ListaDisparosGel::colision(Escenario e)
{
	for (int i = 0; i < numero; i++)
		if (Interaccion::colision(*(lista[i]), e))
		{
			//eliminamos el disparo cuando se impacta con la pared
			delete lista[i];
			numero--;
		}
}
/*DisparoGel* ListaDisparosGel::colision(Enemigo& e) {
	for (int i = 0; i < numero; i++) {
		if (Interaccion::colision(e, (*(lista[i])))) {
			return lista[i];
		}
	}
	return 0;
}
*/
void ListaDisparosGel::destruirContenido()
{
	for (int i = 0; i < numero; i++) // destrucción de esferas contenidas
		delete lista[i];
	numero = 0; // inicializa lista
}

ListaDisparosGel :: ~ListaDisparosGel()
{

}