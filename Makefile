LEX= lexer/lexer.c lexer/checker.c lexer/helpers.c lexer/syntax_analysis.c lexer/tokenizer.c \
lexer/syntax_error.c
LEX_O= $(LEX:.c=.o)

PARS= parser/parser.c parser/helper_funs.c
PARS_O= $(PARS:.c=.o)

SRC= main.c ft_malloc/ft_malloc.c fdprintf/fdprintf.c fdprintf/helpers.c print_tree.c
OBJ= $(SRC:.c=.o)
NAME= minishell
CC= cc
CFLAGS= -g -Wall -Wextra #-Werror
RDLINE = -lreadline
LIBFT= Libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LEX_O) $(PARS_O) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LEX_O) $(PARS_O) $(LIBFT) $(RDLINE) -o $(NAME)

# $(NAME): $(OBJ) $(PARS_O) $(LIBFT)
# 	@$(CC) $(CFLAGS) $(OBJ) $(PARS_O) $(LIBFT) $(RDLINE) -o $(NAME)

$(LIBFT) :
	@$(MAKE) -C Libft

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
# @rm -f $(OBJ) $(PARS_O)
	@rm -f $(OBJ) $(PARS_O) $(LEX_O)
# @$(MAKE) -C libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C Libft fclean

re: fclean all

.PHONY: clean