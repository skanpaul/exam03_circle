NAME = mini_paint

CC	= gcc
CFLAG = -Wall -Wextra -Werror

RM	= rm -f

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

# *****************************************************

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -lm -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

