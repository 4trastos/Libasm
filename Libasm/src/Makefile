NAME = libasm.a

GCC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

LIB = ar rsc

SRC = ft_strlen.s 

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(GCC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)
		$(RM) $(OBJS)

re: fclean all

.PHONY: all clean fclean re

