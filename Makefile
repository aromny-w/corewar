# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: student <student@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/15 22:19:12 by aromny-w          #+#    #+#              #
#    Updated: 2020/03/27 23:35:32 by student          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
LIB = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = corewar.c init.c destroy.c terminate.c error.c
SRCS := $(addprefix corewar/, $(SRCS))
SRCS += op.c
SRCS := $(addprefix srcs/, $(SRCS))
OBJS = $(SRCS:.c=.o)

INC = includes
LIBDIR = libft

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC) -I $(LIBDIR)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L $(LIBDIR) -lft
$(LIB):
	@make -C libft

clean:
	@make clean -C libft
	@/bin/rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	@/bin/rm -f $(NAME)

re: fclean all
