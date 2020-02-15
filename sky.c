#include <mlx.h>
#include <stdio.h>
#include "minirt.h"

int _3ti_lbabaha(int ir, int ig, int ib)
{
	    return (ir * 65536 + ig * 256+ ib);
}
t_vector color(t_ray r)
{
	t_vector v3 ;
	v3.x = 1.0;
	v3.y = 1.0;
	v3.z = 1.0;
	t_vector v31;
	v31.x = 0.5;
	v31.y = 0.7;
	v31.z = 1.0;
	t_vector unit_direction = normalize(&r.direction);
	double t = 0.5 * (unit_direction.y + 1.0);
	t_vector v3s = vectorscal(&v3,(10-t));
	t_vector v32s = vectorscal(&v31,t);
 	t_vector result = vectorsadd(&v3s,&v32s);
	return result;
}

int main(){
	int H = 1080;
	int W = 1080;
	int i,j,x,y;
	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr,W,H,"test");
	t_vector lower_left_corner = {-2.0, -1.0, -1.0}; //lower left cornaer of the raster image
    t_vector horizontal = {5.0, 0.0, 0.0};
    t_vector vertical = {0.0, 2.0, 0.0};
    t_vector origin = {0.0, 0.0, 0.0};

    i = 0;
    x = W -1;
	while(i < W)
	{
		j = 0;
		y = H - 1;
		while( j < H)
		{
			double u =(double)i / H;
            double v = (double)j / W;
			t_vector v3;
			v3.x = (double)i / H ;
			v3.y = (double)j / W ;
			v3.z = 0.2;
			t_vector v3s = vectorscal(&horizontal, u);
			t_vector v32s = vectorscal(&vertical, v);
			t_vector vv = vectorsadd(&v3s, &v32s);
			t_ray ray ={origin, vectorsadd(&lower_left_corner ,  &vv)};
            t_vector col = color(ray);
			int ir = 255.99 * col.x;
			int ig = 255.99 * col.y; 
			int ib = 255.99 * col.z;
			//printf("%d,%d ",i,j);
			mlx_pixel_put(mlx_ptr,win_ptr,x,y,_3ti_lbabaha(ir,ig,ib));
			j++;
			y--;
		}
		i++;
		x--;
	}
mlx_loop(mlx_ptr);
}