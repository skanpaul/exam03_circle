#define MAX_H 300
#define MAX_W 300

/* ************************************************************************** */
#define NO_ERROR 0
#define ERROR 1
#define ERROR_FILE 2

/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/* ************************************************************************** */
typedef struct s_zone
{
	int width;
	int height;
	char back;
	int total;
} t_zone;
/* ************************************************************************** */
typedef struct s_circle
{
	char	type;
	float	ctr_x;
	float	ctr_y;
	float	radius;
	char	char_drawn;
} t_circle;

/* ************************************************************************** */
int ft_strlen(char *str)
{
	int i;

	if (str == NULL)
		return 0;

	i = 0;
	while (str[i] != '\0')
		i++;

	return i;
}

/* ************************************************************************** */
void ft_free_null(char **str)
{
	if (*str != NULL)
		free(*str);
	*str = NULL;
}

/* ************************************************************************** */
void print_err_arg(void)
{
	char *str_err_arg = "Error: argument\n";

	write(1, str_err_arg, ft_strlen(str_err_arg));
}

/* ************************************************************************** */
void print_err_file(void)
{
	char *str_err_file = "Error: Operation file corrupted\n";

	write(1, str_err_file, ft_strlen(str_err_file));
}

/* ************************************************************************** */
void clean_all(char **map, FILE *ptr_file)
{
	ft_free_null(map);
	fclose(ptr_file);
}

/* ************************************************************************** */
void print_map(char *map, t_zone *z)
{
	int i;
	
	i = 0;
	while (i < z->height)
	{
		write(1, (map + i * z->width), z->width);
		write(1, "\n", 1);
		i++;
	}
}
/* ************************************************************************** */
float get_distance_p_to_c(int x, int y, t_circle *c)
{
	float distance;
	float delta_x;
	float delta_y;

	delta_x = (float)x - c->ctr_x;
	delta_y = (float)y - c->ctr_y;	

	distance = sqrtf(powf(delta_x, 2) + powf(delta_y, 2));

	return (distance);
}
/* ************************************************************************** */
bool is_in_disc(int x, int y, t_circle *c)
{
	float	distance;

	distance = get_distance_p_to_c(x, y, c);	

	if (distance <= c->radius)
		return (true);

	return (false);
}

/* ************************************************************************** */
bool is_on_edge(int x, int y, t_circle *c)
{
	float	delta_p_to_center;
	float	delta_p_to_edge;

	delta_p_to_center = get_distance_p_to_c(x, y, c);

	delta_p_to_edge = c->radius - delta_p_to_center;

	if ( delta_p_to_edge < 1)
		return (true);

	return (false);
}

/* ************************************************************************** */
// bool is_out(int x, int y, t_circle *c)
// {
// 	float	distance;

// 	distance = get_distance_p_to_c(x, y, c);

// 	if ((distance - c->radius) >= 1)
// 		return (true);

// 	return (false);
// }

/* ************************************************************************** */
void fill_map_with_circle(t_circle *c, char *map, t_zone *z)
{
    int x;
    int y;
	bool edge;
	bool disc;

	y = 0;
    while (y < z->height)
    {
		x = 0;
        while (x < z->width)
        {
			edge = is_on_edge(x, y, c);
			disc = is_in_disc(x, y, c);
			
			if (is_in_disc(x, y, c))
			{
				if ((c->type == 'c') && edge)
					map[x + y * z->width] = c->char_drawn;						
				
				if ((c->type == 'C') && disc)
					map[x + y * z->width] = c->char_drawn;		
				// print_map(map, z);
			}

            x++;
        }
        y++;
    }
}

/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
int main(int argc, char **argv)
{
	char *filename;
	FILE *ptr_file;
	char *map;
	t_zone z;
	t_circle c;
	int result;

	// check ARG -------------------------------------------
	if (argc == 1 || argc > 2)
	{
		print_err_arg();
		return (ERROR);
	}
	// open file -------------------------------------------
	filename = argv[1];
	if ((ptr_file = fopen(filename, "r")) == NULL)
	{
		print_err_file();
		return (ERROR);
	}
	// get zone information --------------------------------
	if (fscanf(ptr_file, "%d %d %c\n", &z.width, &z.height, &z.back) != 3)
		return (ERROR);
	// check zone information ------------------------------
	if ((z.width <= 0) || (z.width > MAX_W)
    || (z.height <= 0) || (z.height > MAX_H))
	{
		return (ERROR);
	}
	// create map ------------------------------------------
	z.total = z.width * z.height;
	if ((map = (char *)malloc(z.total * sizeof(char))) == NULL)
	{
		ft_free_null(&map);
		return (ERROR);
	}
	// fill back of map ------------------------------------
	memset(map, (int)z.back, z.total);

	// get circle information ------------------------------
	result = fscanf(ptr_file, "%c %f %f %f %c\n", &c.type, &c.ctr_x, &c.ctr_y, &c.radius, &c.char_drawn);
	if ((result != 5) || ((c.type != 'c') && (c.type != 'C')))
	{
		ft_free_null(&map);
		return (ERROR);
	}
	// fill map with circle --------------------------------
	fill_map_with_circle(&c, map, &z);

	// print map -------------------------------------------
	print_map(map, &z);

	// close file ------------------------------------------
	fclose(ptr_file);
	ft_free_null(&map);

	// -----------------------------------------------------
	return (NO_ERROR);
}

/* ************************************************************************** */