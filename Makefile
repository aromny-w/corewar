# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/15 22:19:12 by aromny-w          #+#    #+#              #
#    Updated: 2020/07/14 21:24:59 by malannys         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project executable

NAME = disasm

# Paths
INC = -I includes -I $(LIBDIR)/includes

# Srcs, objs
SRCS = main.c parser.c disasm.c write_asm.c \
			init.c free.c error.c stuff.c
SRCS := $(addprefix disasm/, $(SRCS))
SRCS += op.c
NAME = corewar

# Paths
INC := -I includes -I libft/includes

# Srcs, objs
SRCS = main.c parse_args.c sort_players.c validate.c \
	init.c free.c error.c stuff.c arena.c carriage_list.c \
	create_carriage.c carriage.c exit.c game.c players.c \
	printing.c exec_op.c
SRCS := $(addprefix corewar/, $(SRCS))
SRCS_OPS = add.c aff.c and.c fork.c ld.c ldi.c lfork.c \
live.c lld.c lldi.c or.c st.c sti.c sub.c xor.c zjmp.c \
op_args.c
SRCS_OPS := $(addprefix corewar/operations/, $(SRCS_OPS))
SRCS += $(SRCS_OPS)
SRCS := $(addprefix srcs/, $(SRCS))
OBJS = $(SRCS:.c=.o)

# Libft
LIBDIR = libft
LIB = libft.a

# Compilatiom commands and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror $(INC) -g
LIBDIR := libft
LIB := libft.a

# Compilatiom commands and flags
CC := gcc
CFLAGS := -Wall -Wextra -Werror $(INC) -g

.PHONY: all clean fclean debug

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L $(LIBDIR) -lft

$(LIB):
	@make -C $(LIBDIR)

debug:
	$(CC) $(CFLAGS) $(SRCS) $(INC) $(LIBDIR)/$(LIB) -o $(NAME)

clean:
	@make clean -C libft
	@/bin/rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	@/bin/rm -f $(NAME)

re: fclean all
