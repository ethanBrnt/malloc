# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 12:48:48 by eburnet           #+#    #+#              #
#    Updated: 2025/09/16 14:55:15 by eburnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HOSTTYPE ?= $(shell uname -m)-$(shell uname -s)

NAME     = libft_malloc_$(HOSTTYPE).so
ALIAS    = libft_malloc.so
SRC      = malloc.c free.c realloc.c show_alloc_mem.c
OBJS     = $(SRC:.c=.o)
HEADERS  = malloc.h

CC       = cc
CFLAGS   = -Wall -Wextra -Werror -fPIC -g3
LIBFT_DIR = ./libft
LIBFT     = $(LIBFT_DIR)/libft.a

all: $(NAME) $(ALIAS)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -shared $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $@

$(ALIAS): $(NAME)
	ln -sf $(NAME) $(ALIAS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(ALIAS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re