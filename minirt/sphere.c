
#include <mlx.h>
#include <stdio.h>
#include <stdbool.h> /* Needed for boolean datatype */
#include "minirt.h"
#define PI 3.1415926535897932
int _3ti_lbabaha(int ir, int ig, int ib)
{
	    return (ir * 65536 + ig * 256+ ib);
}

int hit_sphere(t_ray ray,t_sphere s)
{
	// a*t^2 + b*t +c = 0;
	t_vector oc = vectorsSub(&ray.origin , &s.pos);
	double a = vectorsDot(&ray.direction,&ray.direction);
	double b = 2.0 * vectorsDot(&oc,&ray.direction);
	double c = vectorsDot(&oc,&oc) - s.radius * s.radius;

	double delta = b*b - 4 * a*c;

	double t = (-b - sqrt(delta) / (2 * a));
	if (t > 0)
		return 1;
	return 0;
}


int main(){
	int H = 1080;
	int W = 1080;

	double fov = 60 * PI / 180; // field of view 

	int i,j;
	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr,W,H,"test");

	t_sphere sphere;
	sphere.origin.x = 0;
	sphere.origin.y = 0;
	sphere.origin.z = -55;
	sphere.radius = 20;

	/*t_sphere s1;
	s1.pos.x = 0;
	s1.pos.y = 0;
	s1.pos.z = -20;
	s1.radius = 10;
	t_sphere s2;
	s2.pos.x = 0;
	s2.pos.y = 0;
	s2.pos.z = -10;
	s2.radius = 5;*/
    i = 0;
	while(i < W)
	{
		j = 0;
		while( j < H)
		{
			t_vector direction= {j - W / 2  + 0.5 ,i - H / 2, - W/(2 * tan(fov/2))};
			direction = normalize(&direction);
			t_ray ray;
			ray.origin.x = 0;
			ray.origin.y = 0;
			ray.origin.z = 0;
			ray.direction = direction;
			printf(" %f,%f,%f ",direction.x,direction.y,direction.z);
			int ir = 255.99 * hit_sphere(ray,sphere);
			int ig = 255.99 * 0; 
			int ib = 255.99 * 0;
			mlx_pixel_put(mlx_ptr,win_ptr,i,j,_3ti_lbabaha(ir,ig,ib));
			j++;
		}
		i++;
	}
mlx_loop(mlx_ptr);
}