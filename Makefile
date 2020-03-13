# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/09 19:21:11 by zjamali           #+#    #+#              #
#    Updated: 2020/03/13 18:21:06 by zjamali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = minirt

MLX = -lmlx -framework OpenGL -framework AppKit

CFLAGE =  -Wall -Wextra -Werror

INC = minirt.h

SRCS = main.c minirt.c  vector.c pixel_color.c intersection.c \
        camera.c light.c \

OBJ = $(SRCS:.c=.o)

$(NAME): $(OBJ)
		@rm -rf minirt
		@gcc $(CFLAGE) -I /usr/local/include $(OBJ) -L /usr/local/lib $(MLX)
	    @echo "         Made by : \033[1;91mzjamali\033[m"
		@echo "          _       _______ _____    "
		@echo "         (_)     (_) ___ \_   _|    "
		@echo "  _ __ ___  _ _ __  _| |_/ / | |   "
		@echo " | '_ ' _ \| | '_ \| |    /  | |   "
		@echo " | | | | | | | | | | | |\ \  | |   "
		@echo " |_| |_| |_|_|_| |_|_\_| \_| \_/   "
		@echo "Compilation of miniRT:  \033[1;32mOK\033[m"
all: $(NAME)

clean:
		@rm -rf $(OBJ)
		@echo "miniRT : Removing Objs"
		
fclean: clean
		@rm -rf $(NAME)
		@echo "miniRT : Removing miniRT"
		
re: fclean all