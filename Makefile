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

CC=gcc -Wall -Werror -Wextra $(INCLUDES)
NAME = packer

PATH_SRC = ./srcs/
PATH_INC = ./includes/


INCLUDES = -I $(PATH_INC)


SRC =	$(PATH_SRC)main.c \
		$(PATH_SRC)debug.c \
		$(PATH_SRC)file_tools.c

OBJ = $(SRC:.c=.o)

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
	@echo "\033[36m◉ \033[33mmake is done\033[0m"


clean:
	rm -f $(OBJ)
	@echo "\033[36m◉ \033[33mclean done\033[0m"

fclean: clean
	rm -f $(NAME)
	@echo "\033[36m◉ \033[33mfclean done\033[0m"


re: fclean all