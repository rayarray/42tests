#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleskine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/02 10:06:11 by rleskine          #+#    #+#              #
#    Updated: 2023/01/03 17:31:57 by rleskine         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	=	simpletest stdintest multitest gentester
INC		=	../get_next_line.o ./itoa.c
HDR		=	../get_next_line.h
CFLAGS	=	-Wall -Wextra -Werror

SRC		=	$(addsuffix .c, $(NAME))

OBJ		=	$(SRC:.c=.o)

CC		=	cc

all: $(NAME)

$(NAME): %: %.c
	$(CC) $(CFLAGS) -I $(HDR) $(INC) -o $@ $<

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all