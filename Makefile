NAME = ft_ls
OBJ = main.o sort.o parseflags.o parsefiles.o print.o mainhelper.o parsefileshelper.o printhelper.o
INC = inc/ls.h
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
LIBH = libft/libft.h

all: $(NAME)

%.o: $(addprefix ./src/,%.c)
	@gcc $(CFLAGS) $(INC) -c $< $(LIBH)

$(NAME): $(OBJ)
	@gcc -g $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all
