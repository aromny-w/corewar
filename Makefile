# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/15 22:19:12 by aromny-w          #+#    #+#              #
#    Updated: 2020/02/03 19:02:56 by aromny-w         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = asm
NAME2 = corewar
LIBFT = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
FWS = -framework OpenGL -framework AppKit

SRCS1 = asm.c op.c init.c destroy.c read.c name.c comment.c operation.c \
		skip.c terminate.c
SRCS2 = corewar.c

OBJS1 = $(SRCS1:.c=.o)
OBJS2 = $(SRCS2:.c=.o)

INC = libft

all: $(NAME1) $(NAME2)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(NAME1): $(LIBFT) $(OBJS1)
	@$(CC) $(CFLAGS) $(OBJS1) -o $(NAME1) -L $(INC) -lft
$(NAME2): $(LIBFT) $(OBJS2)
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
