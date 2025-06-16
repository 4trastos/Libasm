NAME = libasm.a
GCC = gcc
CFLAGS = -Wall -Wextra -Werror -g

NA  = nasm
NA_FLAGS = -f macho64

SRC_MANDATORY = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s
OBJS_MANDATORY = $(SRC_MANDATORY:.s=.o)

SRC_BONUS = ft_atoi_base_bonus.s
OBJS_BONUS = $(SRC_BONUS:.s=.o)

TEST_MANDATORY_C = main.c
TEST_MANDATORY_EXEC = my_test_mandatory

TEST_BONUS_C = main_bonus.c
TEST_BONUS_EXEC = my_test_bonus

RM = rm -f
AR = ar rcs

%.o: %.s
	$(NA) $(NA_FLAGS) $< -o $@

$(NAME): $(OBJS_MANDATORY)
	$(AR) $(NAME) $(OBJS_MANDATORY)

clean:
	$(RM) $(OBJS_MANDATORY) $(OBJS_BONUS) 

fclean: clean
	$(RM) $(NAME) $(TEST_MANDATORY_EXEC) $(TEST_BONUS_EXEC)

re: fclean all

test: $(NAME) $(TEST_MANDATORY_C)
	$(GCC) $(CFLAGS) $(TEST_MANDATORY_C) -L. -lasm -o $(TEST_MANDATORY_EXEC)
	@echo "\n--- Running Mandatory Tests ($(TEST_MANDATORY_EXEC)) ---\n"
	./$(TEST_MANDATORY_EXEC)
	@echo "\n--- Mandatory Tests finished ---\n"

test_bonus: $(NAME) $(OBJS_BONUS) $(TEST_BONUS_C)
	$(GCC) $(CFLAGS) $(TEST_BONUS_C) -L. -lasm $(OBJS_BONUS) -o $(TEST_BONUS_EXEC)
	@echo "\n--- Running Bonus Tests ($(TEST_BONUS_EXEC) - ft_atoi_base) ---\n"
	./$(TEST_BONUS_EXEC)
	@echo "\n--- Bonus Tests finished ---\n"

.PHONY: all clean fclean re test test_bonus