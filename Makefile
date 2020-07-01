# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/15 22:19:12 by aromny-w          #+#    #+#              #
#    Updated: 2020/07/01 20:40:39 by bgilwood         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
LIB = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS_COREWAR = arena.c carriage_list.c carriage.c exit.c game.c players.c \
printing.c
SRCS = $(addprefix vm/, $(SRCS_COREWAR))
SRCS += op.c
SRCS := $(addprefix srcs/, $(SRCS))
OBJS = $(SRCS_COREWAR:.c=.o)
OBJS := $(addprefix obj/, $(OBJS))

INC = includes
LIBDIR = libft

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC) -I $(LIBDIR)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L $(LIBDIR) -lft
$(LIB):
	@make -C libft

clean:
	@make clean -C libft
	@/bin/rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	@/bin/rm -f $(NAME)

re: fclean all
