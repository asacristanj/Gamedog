#include "Plataforma.h"
#include "freeglut.h" 
#include "Plataforma.h"


Plataforma::Plataforma()
{
	color.r = color.g = color.b = 255; //blanco 
	sprite.setCenter((limite2.x - limite1.x) / 2.0f,  0.25f);
	sprite.setSize(limite2.x - limite1.x, 0.5f);
}
Plataforma::Plataforma(float x1, float y1, float x2, float y2) {
	limite1.x = x1;
	limite1.y = y1;
	limite2.x = x2;
	limite2.y = y2;
	sprite.setCenter((x2-x1) / 2.0f,  0.25f);
	sprite.setSize(limite2.x - limite1.x, 0.5f);
}
void Plataforma::dibuja()
{
	/*
	glDisable(GL_LIGHTING);
	glColor3ub(color.r, color.g, color.b);
	glBegin(GL_POLYGON);
	glVertex3d(limite1.x, limite1.y, 5);
	glVertex3d(limite2.x, limite2.y, 5);
	glVertex3d(limite2.x, limite2.y, -5);
	glVertex3d(limite1.x, limite1.y, -5);
	glEnd();
	glEnable(GL_LIGHTING);
	*/
	/*/*
	


	glEnable(GL_BLEND);     
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
/*
	if (n==1)	
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/plataforma.png").id);
	if (n==0)
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/plataforma2.png").id);

	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	/*
	glTexCoord2d(0, 0); glVertex3d(limite1.x, limite1.y, 5);
	glTexCoord2d(1, 0); glVertex3d(limite2.x, limite1.y, 5);
	glTexCoord2d(1, 1); glVertex3d(limite2.x, limite2.y, -5);
	glTexCoord2d(0, 1); glVertex3d(limite1.x, limite2.y, -5);

	glVertex3d(limite1.x, limite1.y, 5);
	glVertex3d(limite2.x, limite2.y, 5);
	glVertex3d(limite2.x, limite2.y, -5);
	glVertex3d(limite1.x, limite1.y, -5);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	*/
	glPushMatrix();
	glTranslatef(((limite2.x - limite1.x) / 2.0f) + limite1.x, limite2.y - 0.25f, 0);
	glColor3f(0.0f, 0.0f, 250.0f);
	sprite.draw();
	glPopMatrix();
}
void Plataforma::setColor(Byte r, Byte v, Byte a)
{
	color.r = r;
	color.g = v;
	color.b = a;
}
void Plataforma::setPos(float x1, float y1, float x2, float y2)
{
	limite1.x = x1;
	limite1.y = y1;
	limite2.x = x2;
	limite2.y = y2;
}

//Calculo de distancia de una pared a un punto, adicionalmente 
//se modifica el valor de un vector direccion opcional que contendrá 
//el vector unitario saliente que indica la direccion de la 
//recta más corta entre el punto y la pared. 
float Plataforma::distancia(Vector2D punto, Vector2D* direccion)
{
	Vector2D u = (punto - limite1);
	Vector2D v = (limite2 - limite1).unitario();
	float longitud = (limite1 - limite2).modulo();
	Vector2D dir;
	float valor = u * v;
	float distancia = 0;
	if (valor < 0)
		dir = u;
	else if (valor > longitud)
		dir = (punto - limite2);
	else
		dir = u - v * valor;
	distancia = dir.modulo();
	if (direccion != 0) //si nos dan un vector… 
		*direccion = dir.unitario();
	return distancia;
}
Plataforma :: ~Plataforma()
{

}