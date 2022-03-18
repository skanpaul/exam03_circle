

#define NO_ERROR 0
#define ERROR 1
#define ERROR_FILE 2

#include <stdio.h>
#include <unistd.h>

/* ************************************************************************** */
int		ft_strlen(char *str);
void	print_err_arg(void);
void	print_err_file(void);

/* ************************************************************************** */
int main(int argc, char **argv)
{
	char *filename;
	FILE *ptr_file;

	// -----------------------------------------------------
	if (argc == 1 || argc > 2)
	{
		print_err_arg();
		return (ERROR);
	}

	// -----------------------------------------------------
	// open file
	filename = argv[1];
	if((ptr_file = fopen(filename, "r")) == NULL)
	{
		print_err_file();
		return (ERROR);
	}

	// -----------------------------------------------------
	//close file
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