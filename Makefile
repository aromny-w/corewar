
# Project executable
NAME := disasm

# Paths
SRCDIR := ./srcs/
OBJDIR := ./objs/
INCDIR := ./includes/

# Srcs, objs
SRCNAMES := main.c op.c parser.c disasm.c write_asm.c \
			init.c free.c error.c stuff.c
SRC := $(addprefix $(SRCDIR), $(SRCNAMES))
OBJ := $(addprefix $(OBJDIR), $(SRCNAMES:.c=.o))

# Libft
LIBDIR := ./libft/
LIBINCDIR := $(LIBDIR)
LIB := $(LIBDIR)/libft.a

# Compilatiom commands and flags
CC := gcc
CFLAGS := -Wall -Wextra -Werror

.PHONY: all clean fclean debug

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJ): $(OBJDIR)%.o: $(SRCDIR)%.c $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBINCDIR) -c $< -o $@

$(LIB):
	make -C $(LIBDIR)

debug:
	$(CC) -g $(CFLAGS) $(SRC) -I$(INCDIR) -I$(LIBINCDIR) $(LIB) -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(LIBDIR) clean

fclean: clean
	rm -rf $(OBJDIR)
	make -C $(LIBDIR) fclean

re: fclean all