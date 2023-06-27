# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/27 18:40:12 by kyacini           #+#    #+#              #
#    Updated: 2023/06/27 21:28:08 by kyacini          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	srcs/destroyer.c\
		srcs/ft_split.c\
		srcs/ft_strrejoin.c\
		srcs/philo_function.c\
		srcs/philo_action.c\
		srcs/utils.c\
		srcs/main.c \
		srcs/norme.c\
		srcs/ft_atoi.c\
		srcs/ft_itoa.c\

OBJS =	objs/main.o \
		objs/destroyer.o\
		objs/ft_split.o\
		objs/ft_strrejoin.o\
		objs/philo_function.o\
		objs/philo_action.o\
		objs/norme.o\
		objs/ft_atoi.o\
		objs/utils.o\
		objs/ft_itoa.o\

NAME = philo

CC = gcc

INC = include/

RM = rm -rf

CFLAGS = -Wall -Werror -Wextra  -pthread #-fsanitize=thread

all : ${NAME}

bonus : ${NAME_BONUS}

objs/%.o : srcs/%.c
	mkdir -p ./objs
	$(CC) $(CFLAGS) -I${INC} -c $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) -I${INC} -c $< -o $@

${NAME} : ${OBJS}
	$(CC) $(CFLAGS) ${OBJS} -o ${NAME}

clean:
		$(RM) ${OBJS}
		$(RM) ./objs

fclean: clean
		$(RM) $(NAME)

re:	fclean all