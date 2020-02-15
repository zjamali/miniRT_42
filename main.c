#include <mlx.h>
#include <stdio.h>
int _3ti_lbabaha(int ir, int ig, int ib)
{
	return (ir * 65536 + ig * 256+ ib);
}
int main()
{
	double nx = 1000;
	double ny = 1000;
	double r,g,b;
	int ir, ig, ib;
	int k = 0;
	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr, nx, ny, "test");
	int i = 0;
	int j = ny - 1;
	while (k < 1000)
	{
		i = 0;
		while (i < nx)
		{
			r = i / nx;
			g = j / ny;
			b = 0.3;	
			ir = 255.99 * r;
			ig = 255.99 * g;
			ib = 255.99 * b;
			printf("%d ",_3ti_lbabaha(ir,ig,ib));
			mlx_pixel_put(mlx_ptr,win_ptr,i,k,_3ti_lbabaha(ir,ig,ib));
			i++;
		}
		k++;
		j--;
	}
	mlx_loop(mlx_ptr);
	return (0);
}
