NAME = my_ls
CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -g3 -fsanitize=address
SRC = my_ls.c utils.c
OBJ = $(SRC:.c=.o)
HEADER = my_ls.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

debug: clean
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(NAME) $(SRC)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
