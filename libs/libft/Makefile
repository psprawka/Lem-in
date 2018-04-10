# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/24 11:51:37 by psprawka          #+#    #+#              #
#    Updated: 2017/10/07 20:04:53 by psprawka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = libft.a
SRC_DIR = srcs/
FILES =	ft_atoi.c \
			ft_itoa.c \
			ft_strjoin.c \
			ft_strdup.c \
			ft_strlen.c \
			ft_bzero.c \
			ft_strnew.c \
			ft_memset.c \
			ft_strncmp.c \
			ft_strcmp.c \
			ft_strlen_chr.c \
			ft_strncpy.c \
			ft_strstr.c \

CFLAGS = -Wall -Wextra -Werror
HEAD = ./includes
SRC	:=	$(addprefix $(SRC_DIR), $(FILES))
OBJ = $(SRC:.c=.o)

BUILD_PRINT = @printf "\r\033[38;5;214m[LIBFT] \x1B[33mBuilding $<\n"
DONE = @echo "\033[K\033[1;38;5;200mLIBFT ready to use!"
CLEAN_O = @echo "\033[38;5;246mObject files removed! [LIBFT]"
CLEAN_A = @echo "\033[38;5;246mExecutable removed! [LIBFT]"


all: $(NAME)

$(OBJ): %.o: %.c
	$(BUILD_PRINT)
	@gcc $(CFLAGS) -I $(HEAD) -c $< -o $@

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	$(DONE)

clean:
	@/bin/rm -rf $(OBJ)
	$(CLEAN_O)

fclean: clean
	@/bin/rm -rf $(NAME)
	$(CLEAN_A)

re: fclean all

.PHONY: all clean fclean re
