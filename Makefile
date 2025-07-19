CC = cc
# CFLAGS = -Wall -Wextra -Werror -I.


NAME = pipex

SRCS = main.c helper.c

.SECONDARY: $(OBJS)

OBJS = $(SRCS:.c=.o)


all: $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) libft/libft.a -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
