#include "Vector2D.h"
#include "freeglut.h" 
#include <math.h>
Vector2D::Vector2D(float xv, float yv)
{
	x = xv;
	y = yv;
}

float Vector2D::modulo()
{
	return (float)sqrt(x * x + y * y);
}

float Vector2D::argumento()
{
	return (float)atan2(y, x);
}

Vector2D Vector2D::unitario()
{
	Vector2D retorno(x, y);
	float mod = modulo();
	if (mod > 0.00001)
	{
		retorno.x /= mod;
		retorno.y /= mod;
	}
	return retorno;
}

Vector2D Vector2D::operator- (Vector2D v)
{
	Vector2D res;
	res.x = x - v.x;
	res.y = y - v.y;
	return res;
}
Vector2D Vector2D::operator+ (Vector2D v)
{
	Vector2D res;
	res.x = x + v.x;
	res.y = y + v.y;
	return res;
}

float Vector2D:: operator* (Vector2D v)
{
	float escalar = x * v.x + y * v.y;
	return (float)escalar;
}

Vector2D Vector2D:: operator* (float k)
{
	Vector2D esc;
	esc.x = x * k;
	esc.y = y * k;
	return esc;
}
/*Vector2D :: ~Vector2D()
{

}*/