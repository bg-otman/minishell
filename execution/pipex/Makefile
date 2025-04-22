SRCS = pipex.c verify_cmds.c helper_functions.c clean_and_exit.c \
	process_cmds.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c get_execs_path.c
CFLAGS = -Wall -Wextra -Werror
LIBFT = ../../Libft/libft.a
INC = mandatory/pipex.h
INC_BNS = pipex.h get_next_line/get_next_line.h
OBJS = $(SRCS:.c=.o)
OBJS_BNS = $(SRCS_BNS:.c=.o)
NAME = pipex

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

bonus: .bonus

.bonus : $(OBJS_BNS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_BNS) $(LIBFT) -o $(NAME)
	@touch .bonus

$(LIBFT) :
	@$(MAKE) -C ../../Libft

%.o: %.c $(INC) $(INC_BNS)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(OBJS_BNS) .bonus
	@$(MAKE) -C ../../Libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C ../../Libft fclean

re: fclean all

.PHONY: all clean bonus