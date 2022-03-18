#define MAX_H 300
#define MAX_W 300

/* ************************************************************************** */
#define NO_ERROR	0
#define ERROR		1
#define ERROR_FILE	2

/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* ************************************************************************** */
typedef struct s_zone
{
	int w;
	int h;
	char background;
    int total;
}	t_zone;

/* ************************************************************************** */
int		ft_strlen(char *str);
void	print_err_arg(void);
void	print_err_file(void);

/* ************************************************************************** */
int main(int argc, char **argv)
{
	char	*filename;
	FILE	*ptr_file;
	char	*map;
	t_zone	z;

	// check ARG -------------------------------------------
	if (argc == 1 || argc > 2)
	{
		print_err_arg();
		return (ERROR);
	}
	// open file -------------------------------------------
	filename = argv[1];
	if((ptr_file = fopen(filename, "r")) == NULL)
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
    map = (char *)malloc(z.total * sizeof(char));





	// close file ------------------------------------------
	fclose(ptr_file);
	// -----------------------------------------------------
	return (NO_ERROR);
}


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
void print_err_arg(void)
{
	char *str_err_arg = "Error: argument\n";

	write(1, str_err_arg, ft_strlen(str_err_arg));
}

/* ************************************************************************** */
void print_err_file(void)
{
	char *str_err_file 	= "Error: Operation file corrupted\n";

	write(1, str_err_file, ft_strlen(str_err_file));
}