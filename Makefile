LEX= lexer/lexer.c lexer/token_list.c lexer/tokenizer.c lexer/expand_dollar.c \
lexer/lexer2.c lexer/fdprintf/fdprintf.c lexer/fdprintf/helpers.c lexer/expander.c
LEX_O= $(LEX:.c=.o)

PARS= parser/parser.c parser/helper_funs.c
PARS_O= $(PARS:.c=.o)

SRC= main.c ft_malloc/ft_malloc.c
OBJ= $(SRC:.c=.o)
NAME= minishell
CC= cc
CFLAGS= -Wall -Wextra -Werror
RDLINE = -lreadline
LIBFT= libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LEX_O) $(PARS_O) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LEX_O) $(PARS_O) $(LIBFT) $(RDLINE) -o $(NAME)

$(LIBFT) :
	@$(MAKE) -C libft

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(LEX_O) $(PARS_O)
# @$(MAKE) -C libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: clean