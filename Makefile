NAME = $(MINITALK)

MINITALK = $(SERVER) $(CLIENT)
SERVER := server
CLIENT := client

CC := gcc
CFLAGS := -Wall -Wextra -Werror

LIBFT_DIR := ./libft
LIBFT_LIB := $(LIBFT_DIR)/libft.a

SERVER_DIR := ./server_srcs
CLIENT_DIR := ./client_srcs

INCLUDE := ./includes

RM := rm -f

all: $(NAME)

$(SERVER):
	$(MAKE) -C $(SERVER_DIR)
	cp $(SERVER_DIR)/$(SERVER) ./

$(CLIENT):
	$(MAKE) -C $(CLIENT_DIR)
	cp $(CLIENT_DIR)/$(CLIENT) ./

clean:
	$(MAKE) -C $(SERVER_DIR) clean
	$(MAKE) -C $(CLIENT_DIR) clean

fclean:
	$(MAKE) -C $(SERVER_DIR) fclean
	$(MAKE) -C $(CLIENT_DIR) fclean
	$(RM) $(MINITALK)

bonus: all

re: fclean all

.PHONY: all clean fclean bonus re
