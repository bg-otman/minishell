LEX= lexer/lexer.c lexer/checker.c lexer/helpers.c lexer/syntax_analysis.c lexer/tokenizer.c \
lexer/syntax_error.c
LEX_O= $(LEX:.c=.o)

EXP= expander/expander.c expander/expand_dollar.c expander/expand_wildcard.c expander/add_env.c expander/helpers.c
EXP_O= $(EXP:.c=.o)

PARS= parser/parser.c
PARS_O= $(PARS:.c=.o)

SRC= minishell.c execution/helper_funs.c execution/execution.c execution/utils.c execution/mini_helpers.c \
execution/get_next_line/get_next_line.c execution/get_next_line/get_next_line_utils.c execution/builtins/cd.c execution/builtins/pwd.c execution/builtins/echo.c \
execution/builtins/env.c execution/builtins/export.c execution/builtins/unset.c execution/builtins/exit.c
OBJ= $(SRC:.c=.o)
NAME= minishell
CC= cc
CFLAGS= -g -Wall -Wextra -Werror
RDLINE = -lreadline
LIBFT= Libft/libft.a
INCLUDES= minishell.h lexer/lexer.h expander/expander.h

all: $(NAME)
	@echo "\
	███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
	████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
	██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
	██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"

$(NAME): $(OBJ) $(LEX_O) $(EXP_O) $(PARS_O) $(LIBFT) $(INCLUDES)
	@$(CC) $(CFLAGS) $(OBJ) $(LEX_O) $(EXP_O) $(PARS_O) $(LIBFT) $(RDLINE) -o $(NAME)

$(LIBFT) :
	@$(MAKE) --no-print-directory -C Libft

%.o: %.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(PARS_O) $(LEX_O) $(EXP_O)
	@$(MAKE) --no-print-directory -C Libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C Libft fclean

re: fclean all

.PHONY: clean
