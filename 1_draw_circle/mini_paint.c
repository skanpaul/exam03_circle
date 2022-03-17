#include <stdio.h>
#include <unistd.h>

/* ************************************************************************** */
int ft_strlen(char *str);
/* ************************************************************************** */
int main(int argc, char **argv)
{
	int	bidon1;
	char **bidon2;


	char *str_err_arg 	= "Error: argument\n";
	char *str_err_file 	= "Error: Operation file corrupted\n";

	if (argc == 1 || argc > 2)
		write(1, str_err_arg, ft_strlen(str_err_arg));

	// open file





	//close file



	bidon1 = argc;
	bidon2 = argv;
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