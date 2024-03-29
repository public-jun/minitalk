NAME := server
BONUSNAME := server_bonus

CC := gcc
#CFLAGS := -Wall -Wextra -Werror

LIBFT_DIR := ../libft
LIBFT_LIB := $(LIBFT_DIR)/libft.a

SRCS := ./main.c \
		./init.c \
		./print_string.c \
		./receive_bit.c \
		./ack.c
OBJS := $(SRCS:%.c=%.o)

BONUSSRCS := ./main.c \
		./init.c \
		./bonus/print_string_bonus.c \
		./bonus/receive_bit_bonus.c \
		./ack.c
BONUSOBJS := $(BONUSSRCS:%.c=%.o)
INCLUDE := ../includes

RM := rm -f

all: $(NAME)


$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -I $(INCLUDE) $(OBJS) $(LIBFT_LIB) -o $@

$(BONUSNAME): $(BONUSOBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(BONUSOBJS) $(LIBFT_LIB) -o $@

.c.o:
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(LIBFT_LIB): $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) bonus

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS) $(BONUSOBJS)

fclean:
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(OBJS) $(BONUSOBJS) $(BONUSNAME) $(NAME)

re: fclean all

bonus: $(BONUSNAME)

test:
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) -g $(CFLAGS) $(SRCS) $(LIBFT_LIB) -I $(INCLUDE) -o $(NAME)


test_valgrind: test
	valgrind  --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=666 ./$(NAME)

test_sanitize:
	$(MAKE) -C $(LIBFT_DIR)
	$(CC)  -fsanitize=address -fno-omit-frame-pointer -g $(SRCS) $(LIBFT_LIB) -I $(INCLUDE) -o $(NAME)
	./$(NAME)

.PHONY: all clean fclean re bonus test test_valgrind test_sanitize
