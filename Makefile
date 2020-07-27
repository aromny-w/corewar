# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aromny-w <aromny-w@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/15 22:19:12 by aromny-w          #+#    #+#              #
#    Updated: 2020/03/27 23:35:32 by aromny-w         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = asm.c init.c read.c lexer.c parser.c content.c type.c check.c strip.c \
	   line.c label.c write.c print.c destroy.c terminate.c error.c
SRCS := $(addprefix asm/, $(SRCS))
SRCS += op.c
SRCS := $(addprefix srcs/, $(SRCS))

OBJS = $(SRCS:.c=.o)

LIB = libft.a
LIBDIR = libft

INC = -I includes -I $(LIBDIR)/includes

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L $(LIBDIR) -lft

$(LIB):
	@make -C $(LIBDIR)

clean:
	@make clean -C libft
	@/bin/rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	@/bin/rm -f $(NAME)

re: fclean all
