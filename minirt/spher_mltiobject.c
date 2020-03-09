
#include <mlx.h>
#include <stdio.h>
#include "minirt.h"
#define PI 3.1415926535897932
double rgbconvert(int ir, int ig, int ib)
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

double hit_sphere(t_ray ray,t_sphere *s)
{
	// a*t^2 + b*t +c = 0;
	t_vector oc = vectorsSub(&ray.origin , &s->origin);
	double a = vectorsDot(&ray.direction,&ray.direction);
	double b = 2.0 * vectorsDot(&oc,&ray.direction);
	double c = vectorsDot(&oc,&oc) - s->radius * s->radius;

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
t_vector ft_specular(t_light *light,t_ray ray,double t,t_object *object)
{
	t_vector scale_direction_to_p = vectorscal(&ray.direction,t);
	t_vector p = vectorsadd(&ray.origin,&scale_direction_to_p);
	t_vector n = vectorsSub(&p,&object->origin);
	n = normalize(&n);

	t_vector from_camera_to_p = vectorscal(&p,-1);
	from_camera_to_p = normalize(&from_camera_to_p);

 	t_vector l_p = vectorsSub(&p, &light->origin);

	l_p = normalize(&l_p);
	double dot = vectorsDot(&l_p,&n);
	t_vector r = vectorscal(&n,dot * 2);
	t_vector reflection = vectorsSub(&r,&l_p);
	reflection = normalize(&reflection);
	dot = vectorsDot(&from_camera_to_p,&reflection);
	printf(" %f \n",dot);
	double i_specular = pow(dot,10e5);
	t_vector color = {light->color.x /255 * i_specular ,  i_specular  * light->color.y /255, light->color.z  * i_specular /255};

	return color;
}
t_vector ft_diffuse(t_light *light,t_ray ray,double t,t_object *object)
{
	t_vector scale_direction_to_P = vectorscal(&ray.direction,t);
	t_vector p = vectorsadd(&ray.origin,&scale_direction_to_P); 
	t_vector n = vectorsSub(&p,&object->origin);
	n = normalize(&n);
	t_vector l_p;
	// l_p.x =  light->origin.x -  p.x /* - light->origin.x */;
	// l_p.y = light->origin.y - p.y /* - light->origin.y */;
	// l_p.z = light->origin.z - p.z /* - light->origin.y */;
	l_p = vectorsSub(&p, &light->origin);
	l_p = normalize(&l_p);
	// printf(" {%f}",vectorsDot(&n,&l_p));
	double i_diffuse = vectorsDot(&l_p,&n);
	i_diffuse = max(0,i_diffuse);
	//i_diffuse =  i_diffuse /* / lenght(&cp) */;
	//printf("  %f %f %f   \n", l_p.x , l_p.z ,l_p.z);
	t_vector color = { object->color->x / 255 *light->color.x /255 * light->intensity * i_diffuse,
	object->color->y  /255* light->intensity * i_diffuse  * light->color.y /255,object->color->z /255 * light->color.z /225 * light->intensity * i_diffuse};
	return color;
}
t_vector ft_ambient(t_ambient *ambient,t_vector *color)
{
	//double i_total; //i_total = i_ambient + i_diffuse + i_specular
	t_vector i_ambient = {ambient->intensity * color->x /255,
	ambient->intensity * color->y /255 , ambient->intensity * color->z /255};
	i_ambient.x = min(1, i_ambient.x);
	i_ambient.y = min(1, i_ambient.y);
	i_ambient.z = min(1, i_ambient.z);
	return i_ambient;
}
int ft_color_of_pixel(t_ray ray,t_object *object,t_ambient *ambient,t_light *light)
{
	double amcolor = 0;
	int check = 0;
	t_vector color = {0,0,0};
	double closet_object = MAXFLOAT;
	double closet_object1 = 0;
	t_object *temp;
	while(object != NULL)
	{
		//printf("k %d %f",object->id,ray.origin.x);
		closet_object1 = hit_sphere(ray,object->object);
		if (closet_object1 > 0)
		{
			if (closet_object1 <= closet_object)
				{
					check = 1;
					closet_object = closet_object1;
					color = *object->color;
				//	printf("%f\n",object->color->x);
				}
		}
		temp = object;
		object = object->next;
	}
	/************************************/
	if (check == 1){ // to dont color the other pixels 
	t_vector i_ambient = ft_ambient(ambient,&color);
	t_vector i_diffuse = ft_diffuse(light,ray,closet_object,temp);
	t_vector i_specular = ft_specular(light,ray,closet_object,temp);
	/************************************/


	t_vector colors;

	colors.x =  255 * i_ambient.x +   i_diffuse.x * 255 +   i_specular.x * 255 ;
	colors.y =  255 * i_ambient.y +  i_diffuse.y * 255 +  i_specular.y * 255 ;
	colors.z =  255 * i_ambient.z  +  i_diffuse.z * 255 + i_specular.z * 255 ;
	colors.x = min(255,colors.x);
	colors.y = min(255,colors.y);
	colors.z = min(255,colors.z);
		// printf("|x ===> %f|\t|y ==> %f|\t| z ==> %f|\n",colors.x,colors.y,colors.z);

	amcolor = rgbconvert(colors.x,colors.y,colors.z);
/*	amcolor = rgbconvert( min(255, 255 * i_ambient.x) , min(255, 255 * i_ambient.y),min (255,255 *i_ambient.z));
	 amcolor = amcolor + rgbconvert(min(255,i_diffuse.x * 255),min(255,i_diffuse.y * 255 ),min(255,i_diffuse.z * 255));
	 amcolor = amcolor + rgbconvert(min(255,i_specular.x * 255),min(255,i_specular.y * 255),min(255,i_specular.z * 255));*/
	}
	return amcolor;
}

int main(){
	int H = 1080;
	int W = 1080;
	int i,j;
	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr,W,H,"test");

	/***********************/
	t_sphere sphere;
	sphere.origin.x = 0;
	sphere.origin.y = 0;
	sphere.origin.z = 0;
	sphere.radius = 10;
	t_vector color ={255,0,0};
	sphere.color = color;

	// t_sphere s1;
	// s1.origin.x = 0;
	// s1.origin.y = 0;
	// s1.origin.z = -100;
	// s1.radius = 50;
	// t_vector color2 ={0,0,255};
	// s1.color = color2;

	// t_sphere s2;
	// s2.origin.x = 10;
	// s2.origin.y = 0;
	// s2.origin.z = -30;
	// s2.radius = 5;
	// t_vector color1 ={255,0,0};
	// s2.color = color1;


	/***********************/


	/***********************/
	t_camera camera;
	camera.lookfrom.x = 0;
	camera.lookfrom.y = 0;
	camera.lookfrom.z = 50;
	camera.fov = 80;
	camera.orientaion.x = 0;
	camera.orientaion.y = 0;
	camera.orientaion.z = -1;
	/***********************/
    i = 0;

/**********************************************/

	t_object object2;
	object2.object = &sphere;
	object2.color = &sphere.color;
	object2.id = 3;
	object2.object_type = 's';
	object2.origin = sphere.origin;
	object2.next = NULL;

	// t_object object1;
	// object1.object = &s2;
	// object1.color = &s2.color;
	// object1.id = 2;
	// object1.object_type = 's';
	// object1.origin = s2.origin;
	// object1.next = &object2;

	// t_object object;
	// object.object = &s1;
	// object.color = &s1.color;
	// object.id = 1;
	// object.object_type = 's';
	// object.origin = s1.origin;
	// object.next = &object1;
/***********************************************/

	t_ambient ambient;
	//t_vector ambcolor = {255,255,255};
	//ambient.color = ambcolor;
	ambient.intensity =0.2;

	t_light light;
	t_vector lightcolor = {255,255,255};
	t_vector coord = {0,-30000000,500};
	light.color = lightcolor;
	light.intensity = 1;
	light.origin = coord;

/***********************************************/
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
			//t_vector color = {255,255,255};
			int colors = ft_color_of_pixel(ray,&object2,&ambient,&light);
			/*int ir = 1 * color.x;
			int ig = 1 * color.y; 
			int ib = 1 * color.z;*/
			mlx_pixel_put(mlx_ptr,win_ptr,i,j,colors);
			j++;
		}
		i++;
	}
mlx_loop(mlx_ptr);
}