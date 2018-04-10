# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/09 23:21:55 by psprawka          #+#    #+#              #
#    Updated: 2018/03/08 07:14:00 by psprawka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
SRCS_DIR = srcs/

SRCS =	$(SRCS_DIR)connection.c	\
			$(SRCS_DIR)free.c \
			$(SRCS_DIR)main.c \
			$(SRCS_DIR)parse.c \
			$(SRCS_DIR)print.c \
			$(SRCS_DIR)read.c \
			$(SRCS_DIR)solve.c \
			$(SRCS_DIR)tools.c \
			$(SRCS_DIR)utilities.c \
			$(SRCS_DIR)rooms.c \


CFLAGS = -g -Wall -Wextra -Werror
INCLUDES = includes/
HEADERS = $(INCLUDES)*
OBJS = $(SRCS:.c=.o)

LIBFT = libftprintf.a \
			libft.a

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJS) $(HEADERS)
	@printf "\r\033[K\033[1;33m[COREWAR] \033[0;32mLinking...\033[0m\n"
	@gcc $(CFLAGS) -I$(INCLUDES) $(OBJS) $(LIBFT) -lncurses -o $(NAME)
	@printf "\r\033[K\033[1;33m[COREWAR] \033[0;32mDone!\033[0m\n"

$(LIBFT):
	@make -C libs/libft
	@make -C libs/ft_printf
	@cp libs/libft/libft.a .
	@cp libs/ft_printf/libftprintf.a .

%.o: %.c
	@printf "\r\033[K\033[1;33m[COREWAR] \033[0;32mBuilding $<\033[0m\n"
	@gcc $(CFLAGS) -I $(INCLUDES) -c $< -o $@
	@printf "done!\n"

clean:
	@$(MAKE) -C libs/ clean
	@rm -f $(OBJS)
	@printf "\033[1;32m[COREWAR] \033[1;31mCleaned .o!\033[0m\n"

fclean: clean
	@$(MAKE) -C libs/ fclean
	@rm -f $(NAME)
	@rm -f libftprintf.a
	@rm -f libft.a
	@printf "\033[1;32m[COREWAR] \033[1;31mCleaned all!\033[0m\n"

re: fclean all
