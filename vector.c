#include "minirt.h"

/* additin of two vectors and return the resulting vector */
t_vector  vectorsadd(t_vector *v1,t_vector *v2)
{
	t_vector result = {v1->x + v2->x, v1->y + v2->y, v1->z + v2->z };
	return result;
}
/* maltiply a vector by a scaler and return the resulting vector */
t_vector vectorscal(t_vector *v ,double s)
{
	t_vector result = {v->x *s, v->y *s, v->z * s};
	return result;
}
/* divide a vector by a number and return the resulting vector */
t_vector vectordiv(t_vector *v, double d)
{
	t_vector result = {v->x / d, v->y / d, v->z / d};
	return result;
}
/* Subtract two vectors and return the resulting vector */
t_vector vectorsSub(t_vector *v1, t_vector *v2)
{
	t_vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
	return result;
}

/* Multiply two vectors and return the resulting scalar (dot product) */
double vectorsDot(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}
/* the lenght of a vector */

double lenght(t_vector *v)
{
	return (v->x * v->x + v->y * v->y + v->z * v->z);
}

t_vector normalize(t_vector *v)
{
	double norme = sqrt(lenght(v));
	t_vector result = {v->x /= norme,v->y /= norme,v->z /= norme} ;
	return result;
}
t_vector vectorsproduit(t_vector *v1,t_vector *v2)
{
	t_vector result = {v1->x * v2->x, v1->y * v2->y, v1->z * v2->z};
	return result;
};
