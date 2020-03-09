
#include <mlx.h>
#include <stdio.h>
#include <stdbool.h> /* Needed for boolean datatype */
#include "minirt.h"
#define PI 3.1415926535897932
int _3ti_lbabaha(int ir, int ig, int ib)
{
	    return (ir * 65536 + ig * 256+ ib);
}
int hit_sphere(t_ray ray,t_sphere *s)
{
	// a*t^2 + b*t +c = 0;
	t_vector oc = vectorsSub(&ray.origin , &s->pos);
	double a = vectorsDot(&ray.direction,&ray.direction);
	double b = 2.0 * vectorsDot(&oc,&ray.direction);
	double c = vectorsDot(&oc,&oc) - s->radius * s->radius;

	double delta = b*b - 4 * a*c;
	if (delta <0)
		return 0;
	else                                 
	{
	double t1 = (-b - sqrt(delta) / (2 * a));
	double t2 = (-b - sqrt(delta) / (2 * a));
	if (t1 > t2)
		return t2;
	else
		return t1;
	}
}

t_vector ft_camera(t_camera camera,int H,int W/*,int i,int j*/)
{
	t_vector lookatpoint;
	lookatpoint = vectorsadd(&camera.lookfrom,&camera.orientaion);

	t_vector up = {0,1,0};
	t_vector u = vecttorscross(&camera.orientaion,&up);
	t_vector v = vecttorscross(&u,&camera.orientaion);
	v = normalize(&v);
	u = normalize(&u);

	double viewPlaneHalfWidth= tan(camera.fov/2); //////z 
	int aspectRatio = W/H; 
	double viewPlaneHalfHeight = aspectRatio*viewPlaneHalfWidth;
	t_vector x = vectorscal(&v,viewPlaneHalfHeight);
	t_vector y = vectorscal(&u,viewPlaneHalfWidth);
	t_vector s = vectorsSub(&x,&y);
	t_vector viewPlaneBottomLeftPoint = vectorsSub(&lookatpoint,&s);
	/*x = vectorscal(&u,W);
	y = vectorscal(&v,H);
	t_vector xIncVector = vectordiv(&x,W);
	t_vector yIncVector = vectordiv(&y,H);
	x = vectorscal(&u,W);
	//t_vector viewPlanePoint = viewPlaneBottomLeftPoint + i*xIncVector + j*yIncVector;

	t_vector direction = {viewPlaneBottomLeftPoint.x + i*xIncVector.x + j*yIncVector.x ,
	viewPlaneBottomLeftPoint.y + i*xIncVector.y + j*yIncVector.y ,
	viewPlaneBottomLeftPoint.z + i*xIncVector.z + j*yIncVector.z};*/

	t_vector direction = {viewPlaneBottomLeftPoint.x,viewPlaneHalfHeight,viewPlaneHalfWidth};
	return direction;
}

int raytrace(t_ray ray,t_scene scene)
{
	int old_t;
	int col = 0;
	old_t = 1000000;

	if ( (hit_sphere(ray,scene.sphere)) != 0)
	{
		old_t = hit_sphere(ray,scene.sphere);
	}
	if (old_t != 1000000)
		col = scene.sphere->color;
	return col;
}
int main(){

	/****	sphere	***/
	t_sphere sphere;
	sphere.pos.x = 0;
	sphere.pos.y = 0;
	sphere.pos.z = -20;
	sphere.radius = 15;
	sphere.color = 0xff0000;
	/****	camera	***/
	t_vector orientation= {0,0,-1};
	t_vector origin = {0,0,0};
	t_camera camera;
	camera.fov = 60;
	camera.lookfrom = origin;
	camera.orientaion = orientation;
	double fov = 60 * PI / 100; // field of view 
	/****	resolution	*****/
	int H = 1080;
	int W = 1080;
	int i,j;
	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr,W,H,"test");

    i = 0;
	int col = 0;
	t_ray ray;
	ray.origin = camera.lookfrom;
	i = 0;
	while(i < W)
	{
		j = 0;
		while( j < H)
		{
			t_vector direction= {j - W / 2,i - H / 2, -W/(2 * tan(fov/2))};
			direction = normalize(&direction);
			ray.direction = ft_camera(camera,H,W);
			printf("%f,%f,%f ",ray.direction.x,ray.direction.y,ray.direction.z);
			if (hit_sphere(ray,&sphere) > 0)
			{
				col = sphere.color;
			}
			else 
				col = 0;
			mlx_pixel_put(mlx_ptr,win_ptr,i,j,col);
			j++;
		}
		i++;
	}
mlx_loop(mlx_ptr);
}