# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/15 22:19:12 by aromny-w          #+#    #+#              #
#    Updated: 2020/07/10 00:38:59 by bgilwood         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project executable
NAME = corewar

# Paths
INC := includes

# Srcs, objs
SRCS = main.c parse_args.c sort_players.c validate.c \
	init.c free.c error.c stuff.c arena.c carriage_list.c \
	create_carriage.c carriage.c exit.c game.c players.c \
			   printing.c
SRCS := $(addprefix vm/, $(SRCS))
SRCS += op.c
SRCS_OPS = add.c aff.c and.c fork.c ld.c ldi.c lfork.c \
live.c lld.c lldi.c or.c st.c sti.c sub.c xor.c zjmp.c
SRCS_OPS := $(addprefix operations/, $(SRCS_OPS))
SRCS += $(SRCS_OPS)
SRCS := $(addprefix srcs/, $(SRCS))
OBJS = $(SRCS:.c=.o)

# Libft
LIBDIR := libft
LIB := libft.a

# Compilatiom commands and flags
CC := gcc
CFLAGS := -Wall -Wextra -Werror -g

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
