
#include <mlx.h>
#include <stdio.h>
#include "minirt.h"
#define PI 3.1415926535897932
int _3ti_lbabaha(int ir, int ig, int ib)
{
	    return (ir * 65536 + ig * 256+ ib);
}
t_vector ft_camera(t_camera camera,double H,double W,double x,double y)
{
	t_vector up = {0,1,0};
	t_vector u = vecttorscross(&camera.orientaion,&up);
	t_vector v = vecttorscross(&camera.orientaion,&u);
	u = normalize(&u);
	v = normalize(&v);
	double theta = camera.fov*PI/180;
	double viewPlaneHalfWidth = tan(theta/2);
	double aspectRatio = W/H;
	double viewPlaneHalfHeight= aspectRatio*viewPlaneHalfWidth;

	t_vector lookAtPoint = vectorsadd(&camera.orientaion,&camera.lookfrom);
	t_vector A = vectorscal(&v,viewPlaneHalfHeight);
	t_vector B = vectorscal(&u,viewPlaneHalfWidth);
	t_vector C =  vectorsSub(&lookAtPoint,&A);

	t_vector viewPlaneBottomLeftPoint = vectorsSub(&C,&B);
	t_vector xIncVector = vectorscal(&u,2*viewPlaneHalfWidth/W);
	t_vector yIncVector = vectorscal(&v,2*viewPlaneHalfHeight/H);
	C = vectorscal(&xIncVector,x);
	B = vectorscal(&yIncVector,y);
	A = vectorsadd(&C,&B);

	t_vector viewPlanePoint = vectorsadd(&viewPlaneBottomLeftPoint,&A);
	t_vector castRay;
	castRay = vectorsSub(&viewPlanePoint,&camera.lookfrom);
	return castRay;
}

double hit_sphere(t_ray ray,t_sphere s)
{
	// a*t^2 + b*t +c = 0;
	t_vector oc = vectorsSub(&ray.origin , &s.origin);
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
	{
		t =  t2;
	}
	return t;
}


int main(){
	int H = 1080;
	int W = 1080;
	int i,j;
	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr,W,H,"test");

	t_sphere sphere;
	sphere.origin.x = 0;
	sphere.origin.y = 0;
	sphere.origin.z = -30;
	sphere.radius = 10;

	t_camera camera;
	camera.lookfrom.x = 10;
	camera.lookfrom.y = 10;
	camera.lookfrom.z = 10;
	camera.fov = 90;
	camera.orientaion.x = 0;
	camera.orientaion.y = 0;
	camera.orientaion.z = -1;
    i = 0;
	while(i < W)
	{
		j = 0;
		while( j < H)
		{
			t_ray ray;
			ray.origin.x = camera.lookfrom.x;
			ray.origin.y = camera.lookfrom.y;
			ray.origin.z = camera.lookfrom.z;

			ray.direction = ft_camera(camera,H,W,i,j);
			ray.direction = normalize(&ray.direction);
			double t = hit_sphere(ray,sphere);
			if (t > 0)
				printf("  %f   ",t);			
			int ir = 1 * t;
			int ig = 1 * t; 
			int ib = 1 * t;
			mlx_pixel_put(mlx_ptr,win_ptr,i,j,_3ti_lbabaha(ir,ig,ib));
			j++;
		}
		i++;
	}
mlx_loop(mlx_ptr);
}