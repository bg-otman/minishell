LEX= lexer/lexer.c lexer/token_list.c lexer/tokenizer.c lexer/expand_dollar.c \
lexer/lexer2.c lexer/expander.c
LEX_O= $(LEX:.c=.o)

SRC= main.c ft_malloc/ft_malloc.c fdprintf/fdprintf.c fdprintf/helpers.c
OBJ= $(SRC:.c=.o)
NAME= minishell
CC= cc
CFLAGS= -Wall -Wextra -Werror
RDLINE = -lreadline
LIBFT= Libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LEX_O) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LEX_O) $(LIBFT) $(RDLINE) -o $(NAME)

$(LIBFT) :
	@$(MAKE) -C Libft

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(LEX_O)
# @$(MAKE) -C libft clean

fclean: clean
	@rm -f $(NAME)
# @$(MAKE) -C Libft fclean

re: fclean all

.PHONY: clean