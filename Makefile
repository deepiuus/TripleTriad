##
## EPITECH PROJECT, 2025
## TripleTriad [WSL: Debian]
## File description:
## Makefile
##

CC = g++

NAME = triad

SRC = $(wildcard src/*.cpp) \
	$(wildcard src/utils/*.cpp) \
	$(wildcard src/states/*.cpp)

OBJ = $(SRC:.cpp=.o)

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

all: build

build: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
