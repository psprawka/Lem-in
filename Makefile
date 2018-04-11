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
FLAGS = -g -Wall -Wextra -Werror

HEADERS = includes/
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

OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a

BUILD_PRINT = @echo "\r\033[K\033[0;38;5;27m[LEM-IN] \033[38;5;45mBuilding $<"
DONE = @echo "\033[K\033[1;38;5;200mLEM-IN ready to use!"
CLEAN_O = @echo "\033[38;5;246mObject files removed! [LEM-IN]"
CLEAN_A = @echo "\033[38;5;246mExecutable removed! [LEM-IN]"

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJS) $(HEADERS)
	@gcc $(FLAGS) -I $(HEADERS) $(OBJS) $(LIBFT) -lncurses -o $(NAME)
	$(DONE)

$(LIBFT):
	@make -C libft

%.o: %.c
	$(BUILD_PRINT)
	@gcc $(CFLAGS) -I $(HEADERS) -c $< -o $@

clean:
	@$(MAKE) -C libft/ clean
	@rm -f $(OBJS)
	$(CLEAN_O)

fclean: clean
	@$(MAKE) -C libft/ fclean
	@rm -f $(NAME)
	$(CLEAN_A)

re: fclean all
