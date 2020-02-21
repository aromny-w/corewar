# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/15 22:19:12 by aromny-w          #+#    #+#              #
#    Updated: 2020/02/21 22:50:28 by aromny-w         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = asm
NAME2 = corewar
LIB = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRCS1 = asm.c init.c destroy.c read.c name.c comment.c operation.c opcode.c \
		arguments.c argcode.c size.c write.c print.c skip.c terminate.c status.c
SRCS1 := $(addprefix asm/, $(SRCS1))
SRCS1 += op.c
SRCS1 := $(addprefix srcs/, $(SRCS1))
OBJS1 = $(SRCS1:.c=.o)

SRCS2 = corewar.c
SRCS2 := $(addprefix corewar/, $(SRCS2))
SRCS2 += op.c
SRCS2 := $(addprefix srcs/, $(SRCS2))
OBJS2 = $(SRCS2:.c=.o)

INC = includes
LIBDIR = libft

all: $(NAME1) $(NAME2)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC) -I $(LIBDIR)

$(NAME1): $(LIB) $(OBJS1)
	@$(CC) $(CFLAGS) $(OBJS1) -o $(NAME1) -L $(LIBDIR) -lft
$(NAME2): $(LIB) $(OBJS2)
	@$(CC) $(CFLAGS) $(OBJS2) -o $(NAME2) -L $(LIBDIR) -lft
$(LIB):
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
