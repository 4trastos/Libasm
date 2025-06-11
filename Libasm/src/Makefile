# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 14:54:43 by davgalle          #+#    #+#              #
#    Updated: 2019/11/17 21:22:43 by davgalle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libasm.a
GCC = gcc
CFLAGS = -Wall -Wextra -Werror

NA	= nasm
NA_FLAGS = -f macho64

TEST = main.c
TEST_EXEC = my_test_program
TEST_BONUS = test_bonus

RM = rm -f
AR = ar rcs

SRC = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s

OBJS = $(SRC:.s=.o)

all: $(NAME)

%.o: %.s
	$(NA) $(NA_FLAGS) $< -o $@

$(NAME):	$(OBJS)
			$(AR) $(NAME) -o $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)
		$(RM) $(OBJS)
		$(RM) $(TEST_EXEC)

re: fclean all

test:	$(NAME) $(TEST)
		$(GCC) $(CFLAGS) $(TEST) -L. -lasm -o $(TEST_EXEC)

		@echo "\n--- Runnig Test $(TEST_EXEC) ---\n"
		./$(TEST_EXEC)
		@echo "\n--- Test run finished ---\n"

.PHONY: all clean fclean re test

