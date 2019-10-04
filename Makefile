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

LIBS = -L srcs/libft/ -lft -lm

INCLUDES = -I ./includes/ -I srcs/libft/includes/

SOURCES_ASM = 	./srcs/asm/print.s\
				./srcs/asm/crypt.s\
				./srcs/asm/decrypt.s

SOURCES = 		./srcs/main.c \
				./srcs/debug.c \
				./srcs/file_tools.c \
				./srcs/packer.c

OBJ = $(SOURCES:.c=.o) $(SOURCES_ASM:.s=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C srcs/libft/
	$(CC) $(FLAGS) $(OBJ) -o $@ $(LIBS)
	@echo "\033[36m◉ \033[33mmake woody_woodpacker is done\033[0m"


clean:
	make clean -C srcs/libft/
	@rm -f $(OBJ)
	@echo "\033[36m◉ \033[33mclean woody_woodpacker done\033[0m"

fclean: clean
	make fclean -C srcs/libft/
	@rm -f $(NAME)
	@echo "\033[36m◉ \033[33mfclean woody_woodpacker done\033[0m"


re: fclean all

.PHONY: clean fclean re