
#include <mlx.h>
#include <stdio.h>
#include <stdbool.h> /* Needed for boolean datatype */
#include "minirt.h"
#define PI 3.1415926535897932

t_vector ft_camera(t_camera camera,double H,double W,double field_of_view)
{
	double fov = field_of_view * PI / 100; // field of view 
	//direction = {j - W / 2,i - H / 2, -W/(2 * tan(fov/2))};
	//double aspect = W / H;
	t_vector canvas;
	canvas.x = W / 2  /*+ camera.lookat.x*/;
	canvas.y = H /2  /* + camera.lookat.y*/;
	if (camera.orientaion.z < 0)
		canvas.z = -W/(2 * tan(fov/2)   /*+ camera.lookat.z*/); 
	else
		canvas.z = W/(2 * tan(fov/2)   /*+ camera.lookat.z*/);
	return canvas;
}

int _3ti_lbabaha(int ir, int ig, int ib)
{
	    return (ir * 65536 + ig * 256+ ib);
}

int intersact_sphere(t_ray ray,t_sphere s,t_vector *p,t_vector *n ,double *faceratio)
{
	// a*t^2 + b*t +c = 0;
	t_vector oc = vectorsSub(&ray.origin , &s.origin);
	double a = vectorsDot(&ray.direction,&ray.direction);
	double b = 2.0 * vectorsDot(&oc,&ray.direction);
	double c = vectorsDot(&oc,&oc) - s.radius * s.radius;

	double delta = b*b - 4 * a*c;
	double t1 = (-b - sqrt(delta) / (2 * a));
	double t2 = (-b + sqrt(delta) / (2 * a));
//	printf("{%f,%f}",t1,t2);
	if (t2 < 0)
		return (0);
	double t = 0;
	if (t1 > 0)
		t = t1;
	else
	{
		t =  t2;
	}
//	printf("[%f]",t1);

//	n = vectorsSub(p)
	
	t_vector scale_direction_to_P = vectorscal(&ray.direction,t);
	*p = vectorsadd(&ray.origin,&scale_direction_to_P);
	*n = vectorsSub(p,&s.origin);
	*n = normalize(n);
	t_vector v = ray.direction;
	*faceratio = vectorsDot(n,&v);
	if (t != 0)
		t = 1;
	return (int)t;
}

t_vector vec_create(float x, float y, float z)
{
	t_vector cor;

	cor.x = x;
	cor.y = y;
	cor.z = z;
	return (cor);
}
/*
t_vector ft_inter(t_ray ray)
{
	t_ray col;

	col = BLACK;
	t = 10000;
	while ()
	if((t = hit_sphere) && t < t_old)
	{
		t_old = t;
		col = col.sp;
	}

return (col);
}*/
int main(){
	int H = 1080;
	int W = 1080;
/********** cwaymira ************/
t_camera camera;
camera.lookfrom.x = 0;
camera.lookfrom.y = 0;
camera.lookfrom.z = 0;

camera.orientaion.x = 0;
camera.orientaion.y = 0;
camera.orientaion.z = -30;


/*********** dwiw ************/

t_vector light_porstion = { 15,60,-30};
double light_diffuse = 10000;

t_vector p;
t_vector n;

/*******************************/
	double fov =60;
	//double fov = 60 * PI / 100; // field of view 
	int i,j;
	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr,W,H,"test");

	t_sphere sphere;
	sphere.origin.x = 0;
	sphere.origin.y = 0;
	sphere.origin.z = -55;
	sphere.radius = 20;
/*
	t_sphere s1;
	s1.pos.x = 0;
	s1.pos.y = -20;
	s1.pos.z = -30;
	s1.radius = 20;
	
	t_sphere s2;
	s2.pos.x = 0;
	s2.pos.y = 0;
	s2.pos.z = -10;
	s2.radius = 5;
	*/
    i = 0;
	//double aspect_ratio = W /H;
	double faceratio = 0;
	while(i < W)
	{
		j = 0;
		while( j < H)
		{

			t_vector canvas = ft_camera(camera,H,W,fov);
			t_ray ray;
			ray.origin = camera.lookfrom; // oringin = lookfrom
			//t_vector direction ={j - canvas.x,i - canvas.y, canvas.z};
			t_vector direction ={(j - canvas.x +camera.orientaion.x),(i - canvas.y + camera.orientaion.y), (canvas.z + camera.orientaion.x)};
			//ray.direction = direction;
			ray.direction = normalize(&direction);
			//printf("\t\t|%f,%f,%f",ray.direction.x,ray.direction.z,ray.direction.z);
		//	t_vector col = ft_inter(ray);
			int inter = intersact_sphere(ray,sphere,&p,&n,&faceratio);
			//printf(" |%d| ",inter);
			double I = 0;
		//t_vector color ={1,1,1};
			if (inter)
			{
				
				t_vector l_p = vectorsSub(&light_porstion,&p);
				light_porstion = normalize(&light_porstion);
				l_p = normalize(&l_p);
				double dot = vectorsDot(&l_p,&n);
				I =  light_diffuse * dot /lenght(&l_p)*lenght(&n);
				if (I < 0)
				{
					I = 0;
				}
				/*I = I / 1000;
				if (I > 2147483646)
					I = 2147483646;*/
				
			}
			//int d;
			//d = I;
		//	printf(" ||%f|| ",faceratio);
	//		double r = I * color.x * 255 ;
		//	int ir = r;
		//	printf(" [[%d]][[%f]] ",ir,r);
		printf(" ||%f| ",I);
			double r = I;
			int ir =r ;
			if (ir > 255)
				ir = 255;
			int ig = 0 ;
				if (ig > 255)
					ig = 255;
			int ib = 0 ;
			if (ib > 255)
					ib = 255;
		//	int colors = I;
		//	printf("g = %d |r =%d |b = %d",ir,ig,ib);
			//printf(" ||%f| ",I);
			mlx_pixel_put(mlx_ptr,win_ptr,i,j,/*_3ti_lbabaha(ir,ig,ib)*/ r);
			j++;
		}
		i++;
	}
mlx_loop(mlx_ptr);
}