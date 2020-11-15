
#include "minirt.h"


void    ft_check_element(char *line)
{
    char **split;
    split = ft_split(line, ' ');
    if (split[0][0] != 'R' && split[0][0] != 'A' && split[0][0] != 'l'
        && ft_strncmp(split[0],"c",2) && ft_strncmp(split[0],"pl",2) && 
        ft_strncmp(split[0],"sp",2) && ft_strncmp(split[0],"sq",2) &&
        ft_strncmp(split[0],"tr",2) && ft_strncmp(split[0],"cy",2) &&
        ft_strncmp(split[0],"rot",3) && ft_strncmp(split[0],"tra",3))
            ft_print_error("unknown element in the scene.");
}

int    ft_check_line(char *line)
{
    int i;
    i =  0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == '\0')
        return 0;
    ft_check_element(line);

    while (line[i] != '\0')
    {
        if (line[i] != ' ' && line[i] != '\t' && line [i] != ',' && 
        line[i] != '.' && (line[i] < '0' && line[i] > '9'))
            ft_print_error("undifined symbole in the scene file");
        i++;
    }
    return (1);
}

void    ft_check_scene(t_scene *scene)
{
    int height;
    int width;
    /// imac size 5120 x 2880
    width = 5120;
    height = 2880;
    //mlx_get_screen_size(scene->mlx_ptr,&width,&height);
    if (scene->camera == NULL)
        ft_print_error("No camera in the scene,you need at least one camera in the scene.");
    if (scene->resolution.height == 0 && scene->resolution.width == 0)
        ft_print_error("you have to specify the resolution.");
    if (scene->resolution.height > height)
        scene->resolution.height = height;
    if (scene->resolution.width > width)
        scene->resolution.width = width;
}
