SRC= main.c
OBJ= $(SRC:.c=.o)
NAME= minishell
CC= cc
CFLAGS= -Wall -Wextra -Werror
LDFLAG = -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAG)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all