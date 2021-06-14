#include "ListaBloques.h"
ListaBloques::ListaBloques() {
	numero = 0;
	for (int i = 0; i < MAXNUMBER; i++) {
		lista[i] = 0;
	}
}
ListaBloques::~ListaBloques() {

}
void ListaBloques::dibuja() {
	for (int i = 0; i < numero; i++)
		lista[i]->dibuja();
}
bool ListaBloques::agregar(BloqueSorpresa *b){
	for (int i = 0; i < numero; i++) {
		if (b == lista[i])
			return false;
	}
	if (numero < MAXNUMBER)
		lista[numero++] = b;
	else
		return false;
	return true;
}
void ListaBloques::eliminar(int index)//funcion que reordena correctamente el array tras eliminar el bonus de la lista
{
	if ((index < 0) || (index >= numero))
		return;
	delete lista[index];
	numero--;
	for (int i = index; i < numero; i++)
		lista[i] = lista[i + 1];
}
void ListaBloques::eliminar(BloqueSorpresa* b)
{
	for (int i = 0; i < numero; i++)
		if (lista[i] == b)
		{
			eliminar(i);
			return;
		}
}
void ListaBloques::destruirContenido() {
	for (int i = 0; i < numero; i++)
		//delete lista[i];
		delete lista[i];
	numero = 0;
}
void ListaBloques::rebote(Jugador& j) {
	for (int i = 0; i <numero; i++) {
		Interaccion::rebote(j, *(lista[i]));
	}
}
void ListaBloques::CrearBonus(ListaBonus& b,Jugador j) {
	for (int i = 0; i < numero; i++) {
		bool uso = lista[i]->getuso();
		if (Interaccion::colisionDebajo(j, *(lista[i]))&&uso==false) {
			//Generacion de un numero aleatorio para poder generar uno de los distintos tipos de bonus
			lista[i]->setUsotrue();
			int bonus = rand() % 5;
			Vector2D posbloque = lista[i]->getPos();
				switch (bonus) {
				case 0: //Para el caso de que sea cero creamos una nueva mascarilla
					b.agregar(new Quirurgica(2.0f, posbloque.x, posbloque.y, 0.0f, 5.0f));
					break;
				case 1: //Para el caso de que sea uno añadimos una mascarilla tocha
					b.agregar(new MascarillaTocha(1.5f, posbloque.x, posbloque.y, 0.0f, 5.0f));
					break;
				case 2: //Para el caso de que sea dos añadimos una vacuna Pfizer
					b.agregar(new Pfizer(1.5f, posbloque.x, posbloque.y, 0.0f, 5.0f));
					break;
				case 3:	//Para el caso de que sea cuatro añadimos una vacuna Janssen
					b.agregar(new Janssen(1.5f, posbloque.x, posbloque.y, 0.0f, 5.0f));
					break;
				case 4: //Para el caso de que sea cinco añadimos una vacuna Astrazeneca
					b.agregar(new Astrazeneca(1.5f, posbloque.x, posbloque.y, 0.0f, 5.0f));
					break;
				}
		}
	}
}
BloqueSorpresa* ListaBloques:: operator[] (int i) //Funcion que ajusta el simbolo [] para nuestro caso
{
	if (i >= numero)//Si me paso, devuelvo la ultima
		i = numero - 1;
	if (i < 0) //Si el indice es negativo, devuelvo la primera
		i = 0;
	return lista[i];
}