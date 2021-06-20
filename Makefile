NAME = $(MINITALK)
BONUSNAME = $(BONUSMINITALK)

MINITALK = $(SERVER) $(CLIENT)
SERVER := server
CLIENT := client

BONUSMINITALK = $(BONUSSERVER) $(BONUSCLIENT)
BONUSSERVER := server_bonus
BONUSCLIENT := client_bonus

CC := gcc
CFLAGS := -Wall -Wextra -Werror

LIBFT_DIR := ./libft
LIBFT_LIB := $(LIBFT_DIR)/libft.a

SERVER_DIR := ./server_srcs
CLIENT_DIR := ./client_srcs

INCLUDE := ./includes

RM := rm -f

all: $(NAME)

bonus: $(BONUSNAME)

$(SERVER):
	$(MAKE) -C $(SERVER_DIR)
	cp $(SERVER_DIR)/$(SERVER) ./

$(CLIENT):
	$(MAKE) -C $(CLIENT_DIR)
	cp $(CLIENT_DIR)/$(CLIENT) ./

$(BONUSSERVER):
	$(MAKE) -C $(SERVER_DIR) bonus
	cp $(SERVER_DIR)/$(BONUSSERVER) ./

$(BONUSCLIENT):
	$(MAKE) -C $(CLIENT_DIR) bonus
	cp $(CLIENT_DIR)/$(BONUSCLIENT) ./

clean:
	$(MAKE) -C $(SERVER_DIR) clean
	$(MAKE) -C $(CLIENT_DIR) clean

fclean:
	$(MAKE) -C $(SERVER_DIR) fclean
	$(MAKE) -C $(CLIENT_DIR) fclean
	$(RM) $(MINITALK) $(BONUSMINITALK)

re: fclean all

.PHONY: all clean fclean bonus re
