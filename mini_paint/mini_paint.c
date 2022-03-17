#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

/* ************************************************************************** */
typedef struct	s_zone_info
{
	int		width;
	int		height;
	char	background;
}	t_zone_info;

/* ************************************************************************** */
typedef struct	s_shape_info
{
	char	type;
	float	x;
	float	y;
	float	radius;
	char	color;
}	t_shape_info;

/* ************************************************************************** */
int ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/* ************************************************************************** */
char *get_zone_info(FILE *file, t_zone_info *zi)
{
	int		i;
	char	*map;

    // GET ZONE DATA -----------------------------------------------------
	if (fscanf(file, "%d %d %c\n", &zi->width, &zi->height, &zi->background) != 3)
		return (NULL);

    // CHECK ZONE LIMITE AND ERROR ---------------------------------------
	if (zi->width <= 0 || zi->width > 300 || zi->height <= 0 || zi->height > 300)
		return (NULL);

    // CREATE WORKING ZONE -----------------------------------------------
	if (!(map = (char*)malloc(sizeof(*map) * (zi->width * zi->height))))
		return (NULL);

    // INIT BACKGROUND ZONE -----------------------------------------------
	i = 0;
	while (i < zi->width * zi->height)
		map[i++] = zi->background;

    // --------------------------------------------------------------------
	return (map);
}

/* ************************************************************************** */
int in_circle(float x, float y, t_shape_info *shape)
{
	float	distance;

	distance = sqrtf(powf(x - shape->x, 2.) + powf(y - shape->y, 2.));
	if (distance <= shape->radius)
	{
		if ((shape->radius - distance) < 1.00000000)
			return (2); // à étudier
		return (1); // à étudier
	}
	return (0);
}

/* ************************************************************************** */
void draw_shape(t_zone_info *zi, char *map, t_shape_info *shape)
{
	int	y;
	int	x;
	int	is_it;

	y = 0;
	while (y < zi->height)
	{
		x = 0;
		while (x < zi->width)
		{
			is_it = in_circle((float)x, (float)y, shape);
			if (	(shape->type == 'c' && is_it == 2)	|| (shape->type == 'C' && is_it)) // à étudier
				map[(y * zi->width) + x] = shape->color;
			x++;
		}
		y++;
	}
}

/* ************************************************************************** */
int draw_shapes(FILE *file, t_zone_info *zi, char *map)
{
	t_shape_info	tmp;
	int		ret;

	while ((ret = fscanf(file, "%c %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.radius, &tmp.color)) == 5)
	{
		if (tmp.radius <= 0.00000000 || (tmp.type != 'c' && tmp.type != 'C'))
			return (0);
		draw_shape(zi, map, &tmp);
	}
	if (ret != -1)
		return (0);
	return (1);
}

/* ************************************************************************** */
void rendering(t_zone_info *zi, char *map)
{
	int	i;

	i = 0;
	while (i < zi->height)
	{
		write(1, map + (i * zi->width), zi->width);
		write(1, "\n", 1);
		i++;
	}
}

/* ************************************************************************** */
int str_error(char const *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

/* ************************************************************************** */
int clear_all(FILE *file, char *map, char const *str)
{
	if (file)
		fclose(file);
	if (map)
		free(map);
	if (str)
		str_error(str);
	return (1);
}

/* ************************************************************************** */
int main(int argc, char **argv)
{
	FILE	*file;
	t_zone_info	zi;
	char	*map;

	zi.width = 0;
	zi.height = 0;
	zi.background = 0;
	map = NULL;
	if (argc != 2)
		return (str_error("Error: argument\n"));

	if (!(file = fopen(argv[1], "r")))
		return (str_error("Error: Operation file corrupted\n"));

	if (!(map = get_zone_info(file, &zi)))
		return (clear_all(file, NULL, "Error: Operation file corrupted\n"));

	if (!(draw_shapes(file, &zi, map)))
		return (clear_all(file, map, "Error: Operation file corrupted\n"));

	rendering(&zi, map);
	clear_all(file, map, NULL);
	return (0);
}

/* ************************************************************************** */