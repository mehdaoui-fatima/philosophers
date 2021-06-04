# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/04 14:26:09 by fmehdaou          #+#    #+#              #
#    Updated: 2021/06/04 15:03:46 by fmehdaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo_one 

SRCS			= main.c

OBJS			= $(SRCS:.c=.o)

FLAGS			= -Wall -Wextra -Werror 

LIBS			= -lpthread

RM				= rm -rf 

.PHONY: clean bonus fclean all re

all:			$(NAME)

$(NAME):		$(OBJS)
				gcc ${FLAGS} -o ${NAME} ${OBJS} ${LIBS}

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re