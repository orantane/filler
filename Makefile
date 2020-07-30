# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/17 16:20:24 by orantane          #+#    #+#              #
#    Updated: 2020/07/30 17:42:09 by orantane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = orantane.filler

SRC = srcs/*.c

OBJ = *.o

HEADER = includes/filler.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	gcc $(FLAGS) -c $(SRC) -I $(HEADER)

re: fclean all

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

.PHONY = all re clean fclean
