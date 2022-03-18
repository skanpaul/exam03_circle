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

/* ************************************************************************** */
typedef struct s_zone
{
	int w;
	int h;
	char background;
	int total;
} t_zone;

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
void fill_background(char *map, t_zone *z)
{
	int i;
	
	i = 0;
	while (i < z->total)
	{
		map[i] = z->background;
		i++;
	}
}

/* ************************************************************************** */
void print_map(char *map, t_zone *z)
{
	int i;
	
	i = 0;
	while (i < z->h)
	{
		write(1, (map + i * z->w), z->w);
		write(1, "\n", 1);
		i++;
	}
}

/* ************************************************************************** */
int main(int argc, char **argv)
{
	char *filename;
	FILE *ptr_file;
	char *map;
	t_zone z;

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
	if (fscanf(ptr_file, "%d %d %c", &z.w, &z.h, &z.background) != 3)
		return (ERROR);
	// check zone information ------------------------------
	if ((z.w <= 0) || (z.w > MAX_W) || (z.h <= 0) || (z.h > MAX_H))
	{
		return (ERROR);
	}
	// create map -------------------------------------------
	z.total = z.w * z.h;
	if ((map = (char *)malloc(z.total * sizeof(char))) == NULL)
	{
		ft_free_null(&map);
		return (ERROR);
	}
	// fill background of map ------------------------------
	fill_background(map, &z);
	print_map(map, &z);

	// get circle information ------------------------------
	if ((fscanf(ptr_file, "%c %f %f %f %c")) != 5)
	{
		ft_free_null(&map);
		return (ERROR);
	}




	

end:
	// close file ------------------------------------------
	fclose(ptr_file);
	ft_free_null(&map);
	// -----------------------------------------------------




	return (NO_ERROR);
}

/* ************************************************************************** */