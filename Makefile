LEX= lexer/lexer.c lexer/token_list.c lexer/tokenizer.c lexer/expand_dollar.c \
lexer/lexer2.c main.c lexer/fdprintf/fdprintf.c lexer/fdprintf/helpers.c lexer/expander.c
LEX_O= $(LEX:.c=.o)
CC= cc
CFLAGS= -Wall -Wextra -Werror
LDFLAGS= -lreadline
NAME= minishell
LIBFT= LIBFT/libft.a

all: $(NAME)

$(NAME): $(LEX_O)
	@$(CC) -o $@ $(LEX_O) $(LDFLAGS) $(LIBFT)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -f $(LEX_O)

fclean: clean
	@rm -f $(NAME)

re: fclean all