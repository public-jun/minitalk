NAME = $(SERVER) $(CLIENT)
SERVER := server
CLIENT := client

CC := gcc
CFLAGS := -Wall -Wextra -Werror

LIBFT_DIR := ./libft
LIBFT_LIB := $(LIBFT_DIR)/libft.a

SERVER_DIR := ./server_srcs
CLIENT_DIR := ./client_srcs

