NAME = libasm.a
GCC = gcc
CFLAGS = -Wall -Wextra -Werror -g

NA  = nasm
NA_FLAGS = -f elf64

SRC_MANDATORY = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s
OBJS_MANDATORY = $(SRC_MANDATORY:.s=.o)

RM = rm -f
AR = ar rcs

all: $(NAME)

%.o: %.s
	$(NA) $(NA_FLAGS) $< -o $@

$(NAME): $(OBJS_MANDATORY)
		$(AR) $(NAME) $(OBJS_MANDATORY)

clean:
	$(RM) $(OBJS_MANDATORY) $(OBJS_BONUS) 

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
