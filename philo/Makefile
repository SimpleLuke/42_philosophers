BIN = bin
NAME = philo
CC = cc
CFLAG = -Wall -Werror -Wextra -pthread -g3
SRC = src/main.c \
	  src/error.c \
	  src/time.c \
	  src/init.c \
	  src/utils.c \
	  src/free.c \
	  src/simulation.c
OBJ = $(SRC:src/%c=$(BIN)/%o)
INCS = ./includes
IFLAGS = -I $(INCS)
UNAME := $(shell uname)
RM = rm -rf

all: $(NAME)

$(BIN)/%.o: src/%.c
	$(CC) -c $< $(CFLAG) $(IFLAGS) -o $@

$(NAME): $(BIN) $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(BIN):
	mkdir -p $(BIN)

clean:
	$(RM) $(BIN)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(NAME)

show:
	@printf "UNAME		: $(UNAME)\n"
	@printf "NAME		: $(NAME)\n"
	@printf "CC			: $(CC)\n"
	@printf "CFLAG		: $(CFLAG)\n"
	@printf "IFLAGS		: $(IFLAGS)\n"
	@printf "SRC		: $(SRC)\n"
	@printf "OBJS		: $(OBJS)\n"

.PHONY: all clean fclean re
