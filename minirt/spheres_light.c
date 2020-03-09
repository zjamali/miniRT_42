
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
	double t; 
	if (t1 > 0)
		t = t1;
	else
		t =  t2;
	t_vector scale_direction_to_P = vectorscal(&ray.direction,t);
	*p = vectorsadd(&ray.origin,&scale_direction_to_P); 
	*n = vectorsSub(&s.pos,p);
	*n = normalize(n);
	return 1;
}


int main(){
	int H = 1080;
	int W = 1080;

	double fov = 60 * PI / 180; // field of view 

	int i,j;
	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr,W,H,"test");

/*********** dwiw ************/

t_vector light_porstion = {-100,200,-30};
double light_diffuse = 8000000;

t_vector p;
t_vector n;
t_vector cp;

/*******************************/
	t_sphere sphere;
	sphere.pos.x = 0;
	sphere.pos.y = 0;
	sphere.pos.z = -55;
	sphere.radius = 20;
	/*t_sphere s1;
	s1.pos.x = 0;
	s1.pos.y = 50;
	s1.pos.z = -20;
	s1.radius = 10;
	t_sphere s2;
	s2.pos.x = 0;
	s2.pos.y = 0;
	s2.pos.z = -10;
	s2.radius = 5;*/
    i = 0;
	double intesity_pixel; 
	
	while(i < W)
	{
		j = 0;
		while( j < H)
		{
			intesity_pixel = 0;
			t_vector direction= {i - W / 2  + 0.5 ,j - H / 2, - W/(2 * tan(fov/2))};
			direction = normalize(&direction);
			t_ray ray;
			ray.origin.x = 0;
			ray.origin.y = 0;
			ray.origin.z = 0;
			ray.direction = direction;
			//printf(" %f,%f,%f ",direction.x,direction.y,direction.z);
			int inter = intersact_sphere(ray,sphere,&p,&n);
			if (inter)
			{
				t_vector l_p;
				l_p.x = light_porstion.x - p.x;
				l_p.y = light_porstion.y - p.y;
				l_p.z = light_porstion.z - p.z;
				cp = l_p;
				l_p = normalize(&l_p);
				double dot = vectorsDot(&l_p,&n);
				if(dot < 0)
					dot = 0;
				intesity_pixel =  light_diffuse * dot /lenght(&cp);
			}
			if (intesity_pixel > 255)
				intesity_pixel = 255;
			int ir = intesity_pixel;
			int ig = intesity_pixel; 
			int ib = intesity_pixel;
			//printf("  %f  ",intesity_pixel);
			mlx_pixel_put(mlx_ptr,win_ptr,i,j,_3ti_lbabaha(ir,ig*0,ib*0));
			j++;
		}
		i++;
	}
mlx_loop(mlx_ptr);
}