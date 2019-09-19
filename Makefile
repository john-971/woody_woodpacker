#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jandreu <jandreu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/06 17:45:06 by jandreu           #+#    #+#              #
#    Updated: 2015/09/06 17:49:41 by jandreu          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc
FLAGS = -Wall -Werror -Wextra $(INCLUDES)
AS=nasm -f elf64

NAME = woody_woodpacker

PATH_INC = ./includes/


INCLUDES = -I $(PATH_INC)

SOURCES_ASM = 	./srcs/asm/print.s\
				./srcs/asm/crypt.s

SOURCES = 		./srcs/main.c \
				./srcs/debug.c \
				./srcs/file_tools.c \
				./srcs/rc4.c

OBJ = $(SOURCES:.c=.o) $(SOURCES_ASM:.s=.o)

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@
	@echo "\033[36m◉ \033[33mmake is done\033[0m"


clean:
	rm -f $(OBJ)
	@echo "\033[36m◉ \033[33mclean done\033[0m"

fclean: clean
	rm -f $(NAME)
	@echo "\033[36m◉ \033[33mfclean done\033[0m"


re: fclean all