# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: veronika <veronika@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/15 22:19:12 by aromny-w          #+#    #+#              #
#    Updated: 2020/07/04 19:06:50 by veronika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project executable
NAME = corewar

# Paths
INC := includes

# Srcs, objs
SRCS = main.c parse_args.c sort_players.c validate.c \
	   init.c free.c error.c stuff.c
# SRCS_COREWAR = arena.c carriage_list.c carriage.c exit.c game.c players.c \
#			   printing.c
SRCS := $(addprefix vm/, $(SRCS))
SRCS += op.c
SRCS := $(addprefix srcs/, $(SRCS))
OBJS = $(SRCS:.c=.o)

# Libft
LIBDIR := libft
LIB := libft.a

# Compilatiom commands and flags
CC := gcc
CFLAGS := -Wall -Wextra -Werror

.PHONY: all clean fclean debug

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC) -I $(LIBDIR)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L $(LIBDIR) -lft

$(LIB):
	@make -C libft

debug:
	$(CC) -g $(CFLAGS) $(SRCS) -I$(INC) -I$(LIBDIR) $(LIBDIR)/$(LIB) -o $(NAME)

clean:
	@make clean -C libft
	@/bin/rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	@/bin/rm -f $(NAME)

re: fclean all
