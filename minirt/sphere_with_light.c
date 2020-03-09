
#include <mlx.h>
#include <stdio.h>
#include <stdbool.h> /* Needed for boolean datatype */
#include "minirt.h"
#define PI 3.1415926535897932
int _3ti_lbabaha(int ir, int ig, int ib)
{
	    return (ir * 65536 + ig * 256+ ib);
}

int intersact_sphere(t_ray ray,t_sphere s,t_vector *p,t_vector *n)
{
	// a*t^2 + b*t +c = 0;
	t_vector oc = vectorsSub(&ray.origin , &s.pos);
	double a = vectorsDot(&ray.direction,&ray.direction);
	double b = 2.0 * vectorsDot(&oc,&ray.direction);
	double c = vectorsDot(&oc,&oc) - s.radius * s.radius;

	double delta = b*b - 4 * a*c;

	if (delta < 0)
		return (0);
	double t1 = (-b - sqrt(delta) / (2 * a));
	double t2 = (-b + sqrt(delta) / (2 * a));

	if (t2 < 0)
		return (0);
	double t;;
	if (t1 > 0)
		t = t1;
	else
	{
		t =  t2;
	}
	t_vector scale_direction_to_P = vectorscal(&ray.direction,t);
	*p = vectorsadd(&ray.origin,&scale_direction_to_P);
	*n = vectorsSub(p,&s.origin);
	*n = normalize(n);
	return 1;
}


int main(){
	int H = 1024;
	int W = 1024;

	double fov = 60 * PI / 100; // field of view 
	int i,j;
	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr,W,H,"test");

	t_sphere sphere;
	sphere.pos.x = 0;
	sphere.pos.y = 0;
	sphere.pos.z = -20;
	sphere.radius = 30;
/*********** dwiw ************/

t_vector light_porstion = {0,0,-100};
double light_diffuse = 100000000000000;

t_vector p;
t_vector n;
t_vector cp;

/*******************************/
    i = 0;
	double I;
	int inter;
	while(i < W)
	{
		j = 0;
		while( j < H)
		{
			t_vector direction= {j - W / 2,i - H / 2, - W/(2 * tan(fov/2))};
		//	printf("  %f,%f,%f  ",direction.x,direction.y,direction.z);
			direction = normalize(&direction);
			t_ray ray;
			ray.origin.x = 0;
			ray.origin.y = 0;
			ray.origin.z = 0;
			ray.direction = direction;
			inter = intersact_sphere(ray,sphere,&p,&n);
			I = 0;
			if (inter)
			{
				t_vector l_p;
				l_p.x = light_porstion.x - p.x;
				l_p.y = light_porstion.y - p.y;
				l_p.z = light_porstion.z - p.z;
				cp = l_p;
				//  = vectorsSub(&light_porstion,&p);
				l_p = normalize(&l_p);
				// light_porstion = normalize(&light_porstion);
				double dot = vectorsDot(&l_p,&n);
				if(dot < 0)
					{
					dot = 0;
					}

				I =  light_diffuse * dot /lenght(&cp);
			}
			// printf("|I === >%f|\n",I);
			if (I > 255)
			{
				I = 255;
			}
			int ir = I;
			int ig = I; 
			int ib = I;
			mlx_pixel_put(mlx_ptr,win_ptr,i,j,_3ti_lbabaha(ir,ig,ib));
			j++;
		}
		i++;
	}
mlx_loop(mlx_ptr);
}