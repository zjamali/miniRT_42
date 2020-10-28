#include "minirt.h"

/*
size_t		ft_strlen(const char *s)
{
	size_t counter;

	counter = 0;
	while (*s != '\0')
	{
		counter++;
		s++;
	}
	return (counter);
}

static int		check(int s, int counter, int result)
{
	if (counter > 19)
	{
		if (s > 0)
			return (-1);
		else
			return (0);
	}
	return (s * result);
}

int				ft_atoi(const char *str)
{
	int		i;
	int		s;
	int		result;
	int		counter;

	counter = 0;
	i = 0;
	s = 1;
	result = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == ' '
			|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
		counter++;
	}
	return (check(s, counter, result));
}
*/
double	ft_atof(const char *str)
{
	double	res;
	double	res2;
	char	*c;
	int		len;
	int 	s;

	s = 1;
	c = (char *)str;
	if (*c == '-')
		s = -1;
	res = (double)ft_atoi(c);
	///printf("%f",res);
	while (*c && *c != '.')
		c++;
	if (*c == '.')
		c++;
	res2 = (double)ft_atoi(c);
	len = ft_strlen(c);

	while (len--)
		res2 /= 10;
    
   // return res + res2;

    if (res >= 0 && s > 0)
        return res + res2;
    else
        return res - res2;

}
/*
int main()
{
    char *str = "-0.75859";

    double d = ft_atof(str);
    printf("%f",d);
    return 0;
}
*/