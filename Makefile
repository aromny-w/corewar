# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/15 22:19:12 by aromny-w          #+#    #+#              #
#    Updated: 2020/01/31 12:53:26 by aromny-w         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = asm
NAME2 = corewar
LIBFT = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
FWS = -framework OpenGL -framework AppKit

SRCS1 = asm.c init.c read.c name.c comment.c instruction.c terminate.c
SRCS2 = corewar.c

OBJS1 = $(SRCS1:.c=.o)
OBJS2 = $(SRCS2:.c=.o)

INC = libft

all: $(LIBFT) $(NAME1) $(NAME2)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(NAME1): $(OBJS1)
	@$(CC) $(CFLAGS) $(OBJS1) -o $(NAME1) -L $(INC) -lft
$(NAME2): $(OBJS2)
	@$(CC) $(CFLAGS) $(OBJS2) -o $(NAME2) -L $(INC) -lft -lmlx $(FWS)
$(LIBFT):
	@make -C libft

clean:
	@make clean -C libft
	@/bin/rm -f $(OBJS1)
	@/bin/rm -f $(OBJS2)

fclean: clean
	@make fclean -C libft
	@/bin/rm -f $(NAME1)
	@/bin/rm -f $(NAME2)

re: fclean all
