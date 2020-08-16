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

NAME1 = corewar
NAME2 = asm
NAME3 = disasm

CC = gcc
CFLAGS = -Wall -Wextra -Werror $(INC)

SRCS1 = main.c parse_args.c sort_players.c validate.c \
		init.c free.c error.c stuff.c arena.c carriage_list.c \
		create_carriage.c carriage.c exit.c game.c players.c \
		printing.c exec_op.c
SRCS1 := $(addprefix corewar/, $(SRCS1))
SRCS1 += op.c
SRCS_OPS = add.c aff.c and.c fork.c ld.c ldi.c lfork.c \
		   live.c lld.c lldi.c or.c st.c sti.c sub.c xor.c zjmp.c \
		   op_args.c
SRCS_OPS := $(addprefix corewar/operations/, $(SRCS_OPS))
SRCS1 += $(SRCS_OPS)
SRCS1 := $(addprefix srcs/, $(SRCS1))

SRCS2 = asm.c init.c read.c lexer.c parser.c content.c type.c check.c strip.c \
	   line.c label.c write.c print.c destroy.c terminate.c error.c
SRCS2 := $(addprefix asm/, $(SRCS2))
SRCS2 += op.c
SRCS2 := $(addprefix srcs/, $(SRCS2))

SRCS3 = main.c parser.c disasm.c write_asm.c init.c free.c error.c stuff.c
SRCS3 := $(addprefix disasm/, $(SRCS3))
SRCS3 += op.c
SRCS3 := $(addprefix srcs/, $(SRCS3))


OBJS1 = $(SRCS1:.c=.o)
OBJS2 = $(SRCS2:.c=.o)
OBJS3 = $(SRCS3:.c=.o)

LIB = libft.a
LIBDIR = libft

INC = -I includes -I $(LIBDIR)/includes

all: $(NAME1) $(NAME2) $(NAME3)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME1): $(LIB) $(OBJS1)
	@$(CC) $(CFLAGS) $(OBJS1) -o $(NAME1) -L $(LIBDIR) -lft
	@echo "$(NAME1) done!"

$(NAME2): $(LIB) $(OBJS2)
	@$(CC) $(CFLAGS) $(OBJS2) -o $(NAME2) -L $(LIBDIR) -lft
	@echo "$(NAME2) done!"

$(NAME3): $(LIB) $(OBJS3)
	@$(CC) $(CFLAGS) $(OBJS3) -o $(NAME3) -L $(LIBDIR) -lft
	@echo "$(NAME3) done!"

$(LIB):
	@make -C $(LIBDIR)

clean:
	@make clean -C libft
	@/bin/rm -f $(OBJS1)
	@/bin/rm -f $(OBJS2)
	@/bin/rm -f $(OBJS3)

fclean: clean
	@make fclean -C libft
	@/bin/rm -f $(NAME1)
	@/bin/rm -f $(NAME2)
	@/bin/rm -f $(NAME3)

re: fclean all
